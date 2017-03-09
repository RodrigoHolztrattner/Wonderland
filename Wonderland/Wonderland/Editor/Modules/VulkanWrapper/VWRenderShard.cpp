////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWRenderShard.h"
#include "VWGraphicAdapter.h"
#include "VWSwapChain.h"
#include "VWGraphicInstance.h"
#include "VWRenderable.h"
#include "VWContext.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

VulkanWrapper::VWRenderShard::VWRenderShard()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWRenderShard::~VWRenderShard()
{
}

bool VulkanWrapper::VWRenderShard::Initialize(VWContext* _context)
{
	// Create our render pass
	CreateRenderPass(_context->GetGraphicAdapter(), _context->GetGraphicInstance(), _context->GetSwapChain());

	// Create the descriptor layout
	CreateDescriptorSetLayout(_context->GetGraphicAdapter(), _context->GetGraphicInstance());

	// Create the graphic pipeline
	CreateGraphicsPipeline(_context->GetGraphicAdapter(), _context->GetGraphicInstance(), _context->GetSwapChain());

	// Create the frame buffers
	CreateFramebuffers(_context->GetGraphicInstance(), _context->GetSwapChain(), framebuffers, renderPass);

	// Create the uniform buffers
	CreateUniformBuffer(_context->GetGraphicAdapter(), _context->GetGraphicInstance());

	// Create the descriptor pool
	CreateDescriptorPool(_context->GetGraphicAdapter(), _context->GetGraphicInstance());

	// Create the descriptor set
	CreateDescriptorSet(_context->GetGraphicAdapter(), _context->GetGraphicInstance());

	// Create the command buffer
	CreateCommandBuffers(_context->GetGraphicAdapter(), _context->GetGraphicInstance(), _context->GetSwapChain());

	return true;
}

void VulkanWrapper::VWRenderShard::CreateDescriptorSetLayout(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	// Add our layout descriptors
	VWShaderBase::AddDescriptorSetLayoutBinding(0,	VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,			1,	VK_SHADER_STAGE_VERTEX_BIT);
	VWShaderBase::AddDescriptorSetLayoutBinding(1,	VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,	1,	VK_SHADER_STAGE_FRAGMENT_BIT);

	// Create the set layout
	descriptorSetLayout = VWShaderBase::CreateDescriptorSetLayout(_graphicInstance);
}

void VulkanWrapper::VWRenderShard::CreateGraphicsPipeline(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain)
{
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = VWShaderBase::CreateShardStage(_graphicInstance, "shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT, "main");
	VkPipelineShaderStageCreateInfo fragShaderStageInfo = VWShaderBase::CreateShardStage(_graphicInstance, "shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT, "main");
	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	// Set our vertex input binding description
	VWShaderBase::AddVertexInputBindingDescription(0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX);

	// Set our vertex input attribute description
	VWShaderBase::AddVertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32_SFLOAT,		offsetof(Vertex, pos));
	VWShaderBase::AddVertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT,	offsetof(Vertex, color));
	VWShaderBase::AddVertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32_SFLOAT,		offsetof(Vertex, texCoord));

	// Create our input state
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = VWShaderBase::CreateVertexInputState();

	// Create the input assembly
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = VWShaderBase::CreateInputAssemblyState(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE);

	// Add a viewport and the scissor
	VWShaderBase::AddViewport(0, 0, (float)_swapChain->GetExtent().width, (float)_swapChain->GetExtent().height, 0.0f, 1.0f);
	VWShaderBase::AddScissor({ 0, 0 }, _swapChain->GetExtent());

	// Create the pipeline viewport using all viewportes and scissors
	VkPipelineViewportStateCreateInfo viewportState = VWShaderBase::CreatePipelineViewport();

	// Create the rasterizer and the multisample state
	VkPipelineRasterizationStateCreateInfo rasterizer = VWShaderBase::CreateRasterizer(VK_POLYGON_MODE_FILL);
	VkPipelineMultisampleStateCreateInfo multisampling = VWShaderBase::CreateMultisampleState(VK_SAMPLE_COUNT_1_BIT);

	// Add a color blend attachment
	VWShaderBase::AddColorBlendAttachment(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);

	// Create our color blend state
	VkPipelineColorBlendStateCreateInfo colorBlending = VWShaderBase::CreateColorBlendState();

	// Create a new pipeline layout using the descriptor set
	pipelineLayout = VWShaderBase::CreatePipelineLayout(_graphicInstance, &descriptorSetLayout, 1);

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
	if (vkCreateGraphicsPipelines(_graphicInstance->GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}
}

void VulkanWrapper::VWRenderShard::CreateRenderPass(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain)
{
	/*
	- Aqui determinamos funcionalidades de cada "subpass", a função de load por exemplo determina o que fazer no inicio do subpass e a store determina o que será feito
	no final do subpass (caso tenhamos vários subpasses talvez precisamos manter na memória o resultado do ultimo por exemplo, no caso de apenas um subpass tanto faz).
	*/
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = _swapChain->GetFormat();
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

	if (vkCreateRenderPass(_graphicInstance->GetDevice(), &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create render pass!");
	}
}



void VulkanWrapper::VWRenderShard::CreateCommandBuffers(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain)
{
	m_CommandBuffer = _graphicInstance->GetCommandBufferAllocator()->CreateCommandBuffer(_graphicInstance, VK_COMMAND_BUFFER_LEVEL_PRIMARY, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
}

void VulkanWrapper::VWRenderShard::PrepareCommandBuffer(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain, VWRenderable* _renderable, int _imageIndex)
{
	// INVALIDO
	/*

	The descriptor set contents bound by a call to vkCmdBindDescriptorSets may be consumed during host execution of the command, or during shader
	execution of the resulting draws, or any time in between. Thus, the contents must not be altered (overwritten by an update command, or freed)
	between when the command is recorded and when the command completes executing on the queue.

	*/

	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = m_UniformBuffer.GetRawBuffer();
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(UniformBufferObject);
	
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = _renderable->GetImage()->GetImageView();
	imageInfo.sampler = _renderable->GetImage()->GetSampler();

	std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

	descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[0].dstSet = descriptorSet;
	descriptorWrites[0].dstBinding = 0;
	descriptorWrites[0].dstArrayElement = 0;
	descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrites[0].descriptorCount = 1;
	descriptorWrites[0].pBufferInfo = &bufferInfo;

	descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[1].dstSet = descriptorSet;
	descriptorWrites[1].dstBinding = 1;
	descriptorWrites[1].dstArrayElement = 0;
	descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrites[1].descriptorCount = 1;
	descriptorWrites[1].pImageInfo = &imageInfo;

	vkUpdateDescriptorSets(_graphicInstance->GetDevice(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
	// INVALIDO

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	vkBeginCommandBuffer(m_CommandBuffer, &beginInfo);

	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = framebuffers[_imageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = _swapChain->GetExtent();

	VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	renderPassInfo.clearValueCount = 0;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

	VkBuffer vertexBuffers[] = { _renderable->GetVertexBuffer()->GetRawBuffer() };
	VkDeviceSize offsets[] = { 0 };

	// VkRect2D scissor = vks::initializers::rect2D(width, height, 0, 0);
	// vkCmdSetScissor(drawCmdBuffers[i], 0, 1, &scissor);

	vkCmdBindVertexBuffers(m_CommandBuffer, 0, 1, vertexBuffers, offsets);

	vkCmdBindIndexBuffer(m_CommandBuffer, _renderable->GetIndexBuffer()->GetRawBuffer(), 0, VK_INDEX_TYPE_UINT16);

	vkCmdBindDescriptorSets(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);

	vkCmdDrawIndexed(m_CommandBuffer, indices.size(), 3, 0, 0, 0);
	
	vkCmdEndRenderPass(m_CommandBuffer);

	if (vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to record command buffer!");
	}
}

void VulkanWrapper::VWRenderShard::CreateUniformBuffer(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	UniformBufferObject dummy = {};

	// Create the index buffer
	m_UniformBuffer.Create(_adapter, _graphicInstance, _graphicInstance->GetCommandPool(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &dummy, bufferSize);
}

void VulkanWrapper::VWRenderShard::CreateDescriptorPool(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	std::array<VkDescriptorPoolSize, 2> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = 1;
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = 1;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = poolSizes.size();
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = 1;

	if (vkCreateDescriptorPool(_graphicInstance->GetDevice(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void VulkanWrapper::VWRenderShard::CreateDescriptorSet(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	/*
		- Suponto que cada shader tenha um set layout, vamos então pensar que cada "material" tem um descriptor set
		- Podemos enviar mais de 1 descriptor set dentro do command buffer, logo, podemos ter um dedicado totalmente para
		o material (já que precisamos usar o descriptor pool que limita o tipo de envio para a pipeline)

		-> Precisamos separar em 2 descriptor sets (uniform buffer e textura) para ver se é ok enviar + de 1 set
	*/

	VkDescriptorSetLayout layouts[] = { descriptorSetLayout };
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = layouts;

	if (vkAllocateDescriptorSets(_graphicInstance->GetDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to allocate descriptor set!");
	}
}

void VulkanWrapper::VWRenderShard::UpdateUniformBuffer(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain, VWRenderable* _renderable, int _index)
{
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), _swapChain->GetExtent().width / (float)_swapChain->GetExtent().height, 0.1f, 10.0f);

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

	m_UniformBuffer.Update(_adapter, _graphicInstance, _graphicInstance->GetCommandPool(), &ubo);
}