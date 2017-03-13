////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGWidgetBackgroundShader.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

HookGui::HGWidgetBackgroundShader::HGWidgetBackgroundShader()
{
	// Set the initial data
	// ...
}

HookGui::HGWidgetBackgroundShader::~HGWidgetBackgroundShader()
{
}

bool HookGui::HGWidgetBackgroundShader::Initialize(VulkanWrapper::VWContext* _graphicContext)
{
	// Create our render pass
	CreateRenderPass(_graphicContext);

	// Create the descriptor layout
	CreateDescriptorSetLayout(_graphicContext);

	// Create the graphic pipeline
	CreateGraphicsPipeline(_graphicContext);

	// Create the frame buffers
	CreateFramebuffers(_graphicContext->GetGraphicInstance(), _graphicContext->GetSwapChain(), framebuffers, renderPass);

	// Create the uniform buffers
	CreateUniformBuffer(_graphicContext);

	// Create the instance buffer
	CreateInstanceBuffer(_graphicContext);

	// Create the descriptor pool
	CreateDescriptorPool(_graphicContext);

	// Create the descriptor set
	CreateDescriptorSet(_graphicContext);

	// Create the command buffer
	m_CommandBuffer = VWShaderBase::CreateCommandBuffer(_graphicContext, VK_COMMAND_BUFFER_LEVEL_PRIMARY, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

	return true;
}

void HookGui::HGWidgetBackgroundShader::CreateDescriptorSetLayout(VulkanWrapper::VWContext* _graphicContext)
{
	// Add our layout descriptors
	VWShaderBase::AddDescriptorSetLayoutBinding(1,	VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,			1,	VK_SHADER_STAGE_VERTEX_BIT);

	// Create the set layout
	descriptorSetLayout = VWShaderBase::CreateDescriptorSetLayout(_graphicContext->GetGraphicInstance());
}

void HookGui::HGWidgetBackgroundShader::CreateGraphicsPipeline(VulkanWrapper::VWContext* _graphicContext)
{
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = VWShaderBase::CreateShardStage(_graphicContext->GetGraphicInstance(), "shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT, "main");
	VkPipelineShaderStageCreateInfo fragShaderStageInfo = VWShaderBase::CreateShardStage(_graphicContext->GetGraphicInstance(), "shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT, "main");
	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	// Set our vertex input binding description
	VWShaderBase::AddVertexInputBindingDescription(0, sizeof(Vertex),		VK_VERTEX_INPUT_RATE_VERTEX);
	VWShaderBase::AddVertexInputBindingDescription(1, sizeof(InstanceData), VK_VERTEX_INPUT_RATE_INSTANCE);
	
	// Set our vertex input attribute description
	VWShaderBase::AddVertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32_SFLOAT,		offsetof(Vertex, pos));
	VWShaderBase::AddVertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT,	offsetof(Vertex, color));
	VWShaderBase::AddVertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32_SFLOAT,		offsetof(Vertex, texCoord));
	VWShaderBase::AddVertexInputAttributeDescription(1, 3, VK_FORMAT_R32G32B32_SFLOAT,	offsetof(InstanceData, model1));
	VWShaderBase::AddVertexInputAttributeDescription(1, 4, VK_FORMAT_R32G32B32_SFLOAT,	offsetof(InstanceData, model2));
	VWShaderBase::AddVertexInputAttributeDescription(1, 5, VK_FORMAT_R32G32B32_SFLOAT,	offsetof(InstanceData, model3));

	// Create our input state
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = VWShaderBase::CreateVertexInputState();

	// Create the input assembly
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = VWShaderBase::CreateInputAssemblyState(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE);

	// Add a viewport and the scissor
	VWShaderBase::AddViewport(0, 0, (float)_graphicContext->GetSwapChain()->GetExtent().width, (float)_graphicContext->GetSwapChain()->GetExtent().height, 0.0f, 1.0f);
	VWShaderBase::AddScissor({ 0, 0 }, _graphicContext->GetSwapChain()->GetExtent());

	// Create the pipeline viewport using all viewportes and scissors
	VkPipelineViewportStateCreateInfo viewportState = VWShaderBase::CreatePipelineViewport();

	// Create the rasterizer and the multisample state
	VkPipelineRasterizationStateCreateInfo rasterizer = VWShaderBase::CreateRasterizer(VK_POLYGON_MODE_FILL);
	VkPipelineMultisampleStateCreateInfo multisampling = VWShaderBase::CreateMultisampleState(VK_SAMPLE_COUNT_1_BIT);

	// Add a color blend attachment
	VWShaderBase::AddColorBlendAttachment(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);

	// Create our color blend state
	VkPipelineColorBlendStateCreateInfo colorBlending = VWShaderBase::CreateColorBlendState();

	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	pushConstantRange.size = sizeof(int32_t);
	pushConstantRange.offset = 0;
	
	// Create a new pipeline layout using the descriptor set
	VkDescriptorSetLayout descriptorSetLayouts[] = { _graphicContext->GetTextureGroupManager()->GetDescriptorSetLayout(), descriptorSetLayout };
	pipelineLayout = VWShaderBase::CreatePipelineLayout(_graphicContext->GetGraphicInstance(), descriptorSetLayouts, 2, &pushConstantRange, 0);
	
	// Set the graphics pipeline data
	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	// Create our pipeline
	if (vkCreateGraphicsPipelines(_graphicContext->GetGraphicInstance()->GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}
}

void HookGui::HGWidgetBackgroundShader::CreateRenderPass(VulkanWrapper::VWContext* _graphicContext)
{
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = _graphicContext->GetSwapChain()->GetFormat();
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(_graphicContext->GetGraphicInstance()->GetDevice(), &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create render pass!");
	}
}

void HookGui::HGWidgetBackgroundShader::CreateUniformBuffer(VulkanWrapper::VWContext* _graphicContext)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	UniformBufferObject bufferData = {};

	bufferData.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	bufferData.proj = glm::perspective(glm::radians(45.0f), _graphicContext->GetSwapChain()->GetExtent().width / (float)_graphicContext->GetSwapChain()->GetExtent().height, 0.1f, 10.0f);
	bufferData.model = glm::mat4();

	// Create the index buffer
	m_UniformBuffer.Create(_graphicContext, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &bufferData, bufferSize);
}

void HookGui::HGWidgetBackgroundShader::CreateInstanceBuffer(VulkanWrapper::VWContext* _context)
{
	// Create the vertex position buffer
	VkDeviceSize bufferSize = sizeof(InstanceData) * MaximumInstances;

	InstanceData* tempData = new InstanceData[MaximumInstances];

	m_InstanceBuffer.Create(_context, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, tempData, bufferSize);

	delete [] tempData;
}

void HookGui::HGWidgetBackgroundShader::CreateDescriptorPool(VulkanWrapper::VWContext* _graphicContext)
{
	std::array<VkDescriptorPoolSize, 1> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = 1;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = poolSizes.size();
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = 1;

	if (vkCreateDescriptorPool(_graphicContext->GetGraphicInstance()->GetDevice(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void HookGui::HGWidgetBackgroundShader::CreateDescriptorSet(VulkanWrapper::VWContext* _graphicContext)
{
	VkDescriptorSetLayout layouts[] = { descriptorSetLayout };
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = layouts;

	if (vkAllocateDescriptorSets(_graphicContext->GetGraphicInstance()->GetDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to allocate descriptor set!");
	}

	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = m_UniformBuffer.GetRawBuffer();
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(UniformBufferObject);

	std::array<VkWriteDescriptorSet, 1> descriptorWrites = {};

	descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[0].dstSet = descriptorSet;
	descriptorWrites[0].dstBinding = 1;
	descriptorWrites[0].dstArrayElement = 0;
	descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrites[0].descriptorCount = 1;
	descriptorWrites[0].pBufferInfo = &bufferInfo;

	vkUpdateDescriptorSets(_graphicContext->GetGraphicInstance()->GetDevice(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}

void HookGui::HGWidgetBackgroundShader::UpdateUniformBuffer(VulkanWrapper::VWContext* _graphicContext, VulkanWrapper::VWRenderable* _renderable)
{
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), _graphicContext->GetSwapChain()->GetExtent().width / (float)_graphicContext->GetSwapChain()->GetExtent().height, 0.1f, 10.0f);

	UniformBufferObject ubo[1] = {};

	// For each ubo
	for (int i = 0; i < 1; i++)
	{
		glm::vec3 position = _renderable->GetPosition();
		position.x *= (i % 2) == 0 ? 1 : -1;

		ubo[i].model = glm::translate(glm::mat4(), position);
		ubo[i].view = viewMatrix;
		ubo[i].proj = projMatrix;
		ubo[i].proj[1][1] *= -1;
	}

	m_UniformBuffer.Update(_graphicContext, &ubo);
}

void HookGui::HGWidgetBackgroundShader::BeginRender(VulkanWrapper::VWContext* _graphicContext, int _swapchainImageIndex)
{
	// Set the command buffer begin indo
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	// Begin the command buffer
	vkBeginCommandBuffer(m_CommandBuffer, &beginInfo);

	// Set the render pass info
	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = framebuffers[_swapchainImageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = _graphicContext->GetSwapChain()->GetExtent();

	// Set the clear color
	VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	renderPassInfo.clearValueCount = 0;
	renderPassInfo.pClearValues = &clearColor;

	// Begin the render pass
	vkCmdBeginRenderPass(m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	// Set our pipeline
	vkCmdBindPipeline(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
}

void HookGui::HGWidgetBackgroundShader::EndRender()
{
	// End the render pass
	vkCmdEndRenderPass(m_CommandBuffer);

	// End the command buffer record
	if (vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to record command buffer!");
	}
}

void HookGui::HGWidgetBackgroundShader::UpdateInstanceData(VulkanWrapper::VWContext* _context, std::vector<VulkanWrapper::VWRenderable*>& _renderables)
{
	// Create the vertex position buffer
	VkDeviceSize bufferSize = sizeof(InstanceData) * MaximumInstances;

	InstanceData* tempData = new InstanceData[MaximumInstances];

	// For each renderable
	for (int i = 0; i < _renderables.size(); i++)
	{
		// Set the data
		InstanceData& instanceData = tempData[i];

		instanceData.model1 = glm::vec4(_renderables[i]->GetPosition(), 0);
	}

	m_InstanceBuffer.Update(_context, tempData);

	delete[] tempData;
}

void HookGui::HGWidgetBackgroundShader::UpdateTextures(VulkanWrapper::VWRenderable* _instance)
{
	VkDescriptorSet descriptorSets[] = { _instance->GetTextureGroup()->GetDescriptorSet(),  descriptorSet };
	vkCmdBindDescriptorSets(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 2, descriptorSets, 0, nullptr);
}

void HookGui::HGWidgetBackgroundShader::UpdateVertices(VulkanWrapper::VWRenderable* _instance, uint32_t& _indexCount)
{
	// Get the vertex buffers
	VulkanWrapper::VWBuffer* vertexBuffer = _instance->GetVertexObject()->GetVertexBuffer();
	VulkanWrapper::VWBuffer* indexBuffer = _instance->GetVertexObject()->GetIndexBuffer();

	// Set the buffers and offsets
	VkBuffer vertexBuffers[] = { vertexBuffer->GetRawBuffer() };
	VkBuffer instanceBuffers[] = { m_InstanceBuffer.GetRawBuffer() };
	VkDeviceSize vertexOffsets[] = { 0 };
	VkDeviceSize instaceOffsets[] = { 0 };

	// Bind them
	vkCmdBindVertexBuffers(m_CommandBuffer, 0, 1, vertexBuffers, vertexOffsets);
	vkCmdBindVertexBuffers(m_CommandBuffer, 1, 1, instanceBuffers, instaceOffsets);
	vkCmdBindIndexBuffer(m_CommandBuffer, indexBuffer->GetRawBuffer(), 0, VK_INDEX_TYPE_UINT16);

	// Set the index count
	_indexCount = _instance->GetVertexObject()->GetIndexCount();
}

void HookGui::HGWidgetBackgroundShader::RenderCall(uint32_t _globalInstanceCount, uint32_t _indexCount, uint32_t _instanceCount)
{
	// vkCmdPushConstants(m_CommandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(int32_t), &_globalInstanceCount);

	vkCmdDrawIndexed(m_CommandBuffer, _indexCount, _instanceCount, 0, 0, _globalInstanceCount);
}