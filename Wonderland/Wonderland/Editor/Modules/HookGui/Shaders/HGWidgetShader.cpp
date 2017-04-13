////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGWidgetShader.h"
#include "..\..\ModelComposer\ModelComposer.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

HookGui::HGWidgetShader::HGWidgetShader()
{
	// Set the initial data
	// ...
}

HookGui::HGWidgetShader::~HGWidgetShader()
{
}

bool HookGui::HGWidgetShader::Initialize(VulkanWrapper::Context* _graphicContext)
{
	// Get the model manager
	VulkanWrapper::ModelManager* modelManager = _graphicContext->GetModelManager();

	// Request our widget model object
	modelManager->RequestObject(&m_WidgetModel, "square");

	// Create the instance buffer
	CreateInstanceBuffer(_graphicContext);

	// Create the uniform buffer
	CreateUniformBuffer(_graphicContext);

	// Create the descriptor set
	CreateDescriptorSet(_graphicContext);

	// Create our render pass
	CreateRenderPass(_graphicContext);

	// Create the graphic pipeline
	CreateGraphicsPipeline(_graphicContext);

	// Create the frame buffers
	CreateFramebuffers(_graphicContext->GetGraphicInstance(), _graphicContext->GetSwapChain(), m_Framebuffers, m_RenderPass);

	// Create the command buffer
	m_CommandBuffer = VWShaderBase::CreateCommandBuffer(_graphicContext, VK_COMMAND_BUFFER_LEVEL_PRIMARY, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

	return true;
}

void HookGui::HGWidgetShader::CreateDescriptorSet(VulkanWrapper::Context* _graphicContext)
{
	// Add our layout descriptors
	VWShaderBase::AddDescriptorSetLayoutBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT);

	// Create the set layout
	m_DescriptorSetLayout = VWShaderBase::CreateDescriptorSetLayout(_graphicContext->GetGraphicInstance());

	// Create the descriptor pool
	m_DescriptorPool = VWShaderBase::CreateDescriptorPool(_graphicContext);

	// Create the descriptor set
	m_DescriptorSet = VWShaderBase::CreateDescriptorSet(_graphicContext, m_DescriptorPool, 1, &m_DescriptorSetLayout);

	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = m_UniformBuffer.GetRawBuffer();
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(UniformBufferObject);

	std::array<VkWriteDescriptorSet, 1> descriptorWrites = {};

	descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[0].dstSet = m_DescriptorSet;
	descriptorWrites[0].dstBinding = 1;
	descriptorWrites[0].dstArrayElement = 0;
	descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrites[0].descriptorCount = 1;
	descriptorWrites[0].pBufferInfo = &bufferInfo;

	vkUpdateDescriptorSets(_graphicContext->GetGraphicInstance()->GetDevice(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}

void HookGui::HGWidgetShader::CreateGraphicsPipeline(VulkanWrapper::Context* _graphicContext)
{
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = VWShaderBase::CreateShardStage(_graphicContext->GetGraphicInstance(), "shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT, "main");
	VkPipelineShaderStageCreateInfo fragShaderStageInfo = VWShaderBase::CreateShardStage(_graphicContext->GetGraphicInstance(), "shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT, "main");
	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	// Set our vertex input binding description
	VWShaderBase::AddVertexInputBindingDescription(0, sizeof(ModelComposer::VertexFormat),		VK_VERTEX_INPUT_RATE_VERTEX);
	VWShaderBase::AddVertexInputBindingDescription(1, sizeof(InstanceData),						VK_VERTEX_INPUT_RATE_INSTANCE);
	
	// Set our vertex input attribute description
	VWShaderBase::AddVertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT,		offsetof(ModelComposer::VertexFormat, position));
	VWShaderBase::AddVertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32_SFLOAT,			offsetof(ModelComposer::VertexFormat, textureCoordinate));
	VWShaderBase::AddVertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32B32_SFLOAT,		offsetof(ModelComposer::VertexFormat, normal));
	VWShaderBase::AddVertexInputAttributeDescription(0, 3, VK_FORMAT_R32G32B32_SFLOAT,		offsetof(ModelComposer::VertexFormat, binormal));
	VWShaderBase::AddVertexInputAttributeDescription(1, 4, VK_FORMAT_R32G32B32_SFLOAT,		offsetof(InstanceData, position));
	VWShaderBase::AddVertexInputAttributeDescription(1, 5, VK_FORMAT_R32G32B32_SFLOAT,		offsetof(InstanceData, size));
	VWShaderBase::AddVertexInputAttributeDescription(1, 6, VK_FORMAT_R32G32B32_SFLOAT,		offsetof(InstanceData, rotation));
	VWShaderBase::AddVertexInputAttributeDescription(1, 7, VK_FORMAT_R32G32B32_SFLOAT,		offsetof(InstanceData, extra));

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

	// Create the depth stencil state
	VkPipelineDepthStencilStateCreateInfo depthStencil = VWShaderBase::CreateDepthStencilState(VK_TRUE, VK_TRUE, VK_COMPARE_OP_LESS, VK_FALSE, VK_FALSE);

	// Add a color blend attachment
	VWShaderBase::AddColorBlendAttachment(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);

	// Create our color blend state
	VkPipelineColorBlendStateCreateInfo colorBlending = VWShaderBase::CreateColorBlendState();

	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	pushConstantRange.size = sizeof(int32_t);
	pushConstantRange.offset = 0;

	// Create a new pipeline layout using the descriptor set
	VkDescriptorSetLayout descriptorSetLayouts[] = { _graphicContext->GetTextureGroupManager()->GetDescriptorSetLayout(), m_DescriptorSetLayout };
	m_PipelineLayout = VWShaderBase::CreatePipelineLayout(_graphicContext->GetGraphicInstance(), descriptorSetLayouts, 2, &pushConstantRange, 0);
	
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
	pipelineInfo.layout = m_PipelineLayout;
	pipelineInfo.renderPass = m_RenderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.pDepthStencilState = &depthStencil;

	// Create our pipeline
	if (vkCreateGraphicsPipelines(_graphicContext->GetGraphicInstance()->GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}
}

void HookGui::HGWidgetShader::CreateRenderPass(VulkanWrapper::Context* _graphicContext)
{
	// Get the swap chain object
	VulkanWrapper::SwapChain* swapChain = _graphicContext->GetSwapChain();

	// Start a new render pass
	VWShaderBase::RenderPass renderPass = VWShaderBase::StartRenderPass();
	{
		// Create a color and depth attachments
		VWShaderBase::ColorAttachmentDescription colorAttachment = VWShaderBase::CreateColorAttachmentDescriptor(renderPass, swapChain->GetFormat(), VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE,
			VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
		VWShaderBase::DepthAttachmentDescription depthAttachment = VWShaderBase::CreateDepthAttachmentDescriptor(renderPass, swapChain->GetDepthImage()->GetFormat(), VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

		// Create a subpass
		VWShaderBase::SubPass subPass = VWShaderBase::StartSubPass(renderPass, VK_PIPELINE_BIND_POINT_GRAPHICS);

		// Add the attachment references
		VWShaderBase::AddColorAttachmentReference(subPass, colorAttachment, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
		VWShaderBase::SetDepthAttachmentReference(subPass, depthAttachment, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

		// Add the dependency
		VWShaderBase::AddDependency(renderPass, VWShaderBase::SubPassExternal, VWShaderBase::SubPassNull, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
			VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);

		// Create the render pass
		m_RenderPass = VWShaderBase::CreateRenderPass(_graphicContext->GetGraphicInstance(), renderPass);
	}
}

void HookGui::HGWidgetShader::CreateInstanceBuffer(VulkanWrapper::Context* _context)
{
	// Create the vertex position buffer
	VkDeviceSize bufferSize = sizeof(InstanceData) * MaximumInstances;

	InstanceData* tempData = new InstanceData[MaximumInstances];

	m_InstanceBuffer.Create(_context, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, tempData, bufferSize);

	delete [] tempData;
}


void HookGui::HGWidgetShader::CreateUniformBuffer(VulkanWrapper::Context* _graphicContext)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	UniformBufferObject bufferData = {};
	
	// Get the swap chain dimensions
	float width = _graphicContext->GetSwapChain()->GetExtent().width;
	float height = _graphicContext->GetSwapChain()->GetExtent().height;

	bufferData.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	bufferData.proj = glm::ortho(0.0f, width, -height, 0.0f, -1.0f, 1.0f);
	bufferData.model = glm::mat4();

	// Create the index buffer
	m_UniformBuffer.Create(_graphicContext, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &bufferData, bufferSize);
}


void HookGui::HGWidgetShader::UpdateUniformBuffer(VulkanWrapper::Context* _graphicContext)
{
	// Get the swap chain dimensions
	float width = _graphicContext->GetSwapChain()->GetExtent().width;
	float height = _graphicContext->GetSwapChain()->GetExtent().height;

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projMatrix = glm::ortho(-width/2, width/2, -height / 2, height / 2, -1.0f, 1.0f);
	glm::mat4 modelMatrix = glm::mat4();

	UniformBufferObject ubo[1] = {};

	// For each ubo
	for (int i = 0; i < 1; i++)
	{
		ubo[i].model = modelMatrix;
		ubo[i].view = viewMatrix;
		ubo[i].proj = projMatrix;
		// ubo[i].proj[1][1] *= -1;
	}

	m_UniformBuffer.Update(_graphicContext, &ubo);
}

bool HookGui::HGWidgetShader::IsValid()
{
	// Check if the widget model reference is valid
	if (!m_WidgetModel.IsValid())
	{
		return false;
	}
	
	// Check if the widget model object is valid
	if (!m_WidgetModel->IsValid())
	{
		return false;
	}

	return true;
}

void HookGui::HGWidgetShader::AddWidget(HGWidget* _widget)
{
	// Check if this shader is valid to be used
	if (!IsValid())
	{
		return;
	}

	// Check if the widget is valid
	if (_widget->IsValid())
	{
		m_Renderables.push_back(_widget);
	}
}

void HookGui::HGWidgetShader::Render(VulkanWrapper::Context* _graphicContext, int _swapchainImageIndex)
{
	// Check if this shader is valid to be used
	if (!IsValid())
	{
		return;
	}

	// Update the instance data
	UpdateInstanceData(_graphicContext);

	// Begin the rendering process
	BeginRender(_graphicContext, _swapchainImageIndex);

	// Get the vertex buffers
	VulkanWrapper::Buffer* vertexBuffer = m_WidgetModel->GetVertexBuffer();
	VulkanWrapper::Buffer* indexBuffer = m_WidgetModel->GetIndexBuffer();

	// Set the buffers and offsets
	VkBuffer vertexBuffers[] = { vertexBuffer->GetRawBuffer() };
	VkBuffer instanceBuffers[] = { m_InstanceBuffer.GetRawBuffer() };
	VkDeviceSize vertexOffsets[] = { 0 };
	VkDeviceSize instaceOffsets[] = { 0 };

	// Bind them
	vkCmdBindVertexBuffers(m_CommandBuffer, 0, 1, vertexBuffers, vertexOffsets);
	vkCmdBindVertexBuffers(m_CommandBuffer, 1, 1, instanceBuffers, instaceOffsets);
	vkCmdBindIndexBuffer(m_CommandBuffer, indexBuffer->GetRawBuffer(), 0, VK_INDEX_TYPE_UINT32);

	// Set the initial texture identificator
	uint32_t currentTextureIdentificator = -1;

	// The total number of instances to be rendered
	uint32_t totalInstances = 0;

	// The first instance to be rendered
	uint32_t firstInstance = 0;

	// For each widget
	for (int i = 0; i < m_Renderables.size(); i++)
	{
		// Get the current widget
		HGWidget* widget = m_Renderables[i];

		// Get the widget image
		HGImage* widgetImage = widget->GetImage();

		// Get the image texture group
		VulkanWrapper::TextureGroup* widgetImageTextureGroup = widgetImage->GetTextureGroupReference();

		// Get the texture group identificator
		uint32_t textureIdentificator = widgetImageTextureGroup->GetTextureGroupIdentificator();

		// Check if we are using the same texture group
		if (currentTextureIdentificator != textureIdentificator)
		{
			// Update the texture identificator
			VkDescriptorSet descriptorSets[] = { widgetImageTextureGroup->GetDescriptorSet(), m_DescriptorSet };
			vkCmdBindDescriptorSets(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_PipelineLayout, 0, 2, descriptorSets, 0, nullptr);

			// If we have at last one instance
			if (totalInstances)
			{
				// Issue a draw call
				vkCmdDrawIndexed(m_CommandBuffer, m_WidgetModel->GetIndexCount(), totalInstances, 0, 0, firstInstance);

				// Set the new first instance
				firstInstance = i;

				// Zero the total instances
				totalInstances = 0;
			}
			
			// Set the new current texture identificator
			currentTextureIdentificator = textureIdentificator;
		}

		// Increment the total number of instances
		totalInstances++;
	}

	// Check if we have instances remaining
	if (totalInstances)
	{
		// Issue the last draw call
		vkCmdDrawIndexed(m_CommandBuffer, m_WidgetModel->GetIndexCount(), totalInstances, 0, 0, firstInstance);
	}

	// Clear the renderable array
	m_Renderables.clear();

	// End the rendering process
	EndRender();
}

void HookGui::HGWidgetShader::BeginRender(VulkanWrapper::Context* _graphicContext, int _swapchainImageIndex)
{
	// Get a new command buffer for this rendering
	// m_CommandBuffer = _graphicContext->GetValidFrameCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);

	// Set the command buffer begin indo
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT; // VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT 

	// Begin the command buffer
	vkBeginCommandBuffer(m_CommandBuffer, &beginInfo);

	// Set the clear color
	std::array<VkClearValue, 2> clearValues = {};
	clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
	clearValues[1].depthStencil = { 1.0f, 0 };

	// Set the render pass info
	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = m_RenderPass;
	renderPassInfo.framebuffer = m_Framebuffers[_swapchainImageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = _graphicContext->GetSwapChain()->GetExtent();
	renderPassInfo.clearValueCount = 0; // clearValues.size()
	renderPassInfo.pClearValues = clearValues.data();

	// Begin the render pass
	vkCmdBeginRenderPass(m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	// Set our pipeline
	vkCmdBindPipeline(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
}

void HookGui::HGWidgetShader::EndRender()
{
	// End the render pass
	vkCmdEndRenderPass(m_CommandBuffer);

	// End the command buffer record
	if (vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to record command buffer!");
	}
}

void HookGui::HGWidgetShader::UpdateInstanceData(VulkanWrapper::Context* _context)
{
	// Create the vertex position buffer
	VkDeviceSize bufferSize = sizeof(InstanceData) * MaximumInstances;

	// Set the instance temporary data //TODO: usar memória por frame e não ficar alocando usando new/delete
	InstanceData* tempData = new InstanceData[MaximumInstances];

	// For each renderable
	for (int i = 0; i < m_Renderables.size(); i++)
	{
		// Get the current widget
		HGWidget* widget = m_Renderables[i];

		// Get the instance data
		InstanceData& instanceData = tempData[i];
		
		// Get the widget frame
		HGFrame widgetFrame = widget->GetFrame();

		// Get the widget transform matrix
		glm::mat4 widgetTransformMatrix = widget->GetTransformMatrix();

		// Set the transform data
		instanceData.position = glm::vec4(widgetFrame.x, widgetFrame.y, 0, 0);
		instanceData.size = glm::vec4(widgetFrame.width, widgetFrame.height, 1, 0);
		instanceData.rotation = glm::vec4(0, 0, 0, 0);
		instanceData.extra = glm::vec4(0, 0, 0, 0);

		// Get the swap chain dimensions
		float width = _context->GetSwapChain()->GetExtent().width;
		float height = _context->GetSwapChain()->GetExtent().height;

		// TEST

		glm::vec4 vertice(0, 0, 0, 0);

		vertice.x *= 330;
		vertice.y *= 240;
		
		vertice.x += 0;
		vertice.y += 0;

		glm::mat4 projMatrix = glm::ortho(0.0f, width, -height, 0.0f, -1.0f, 1.0f);

		glm::vec4 result = projMatrix * vertice;
		result.x -= 1;
		result.y -= 1;

		// TEST

		// Get the diffuse texture from the object
		VulkanWrapper::Texture widgetTextureImage = widget->GetImage()->GetTexture();

		// Set the texture fetch instance
		instanceData.extra.w = widgetTextureImage.GetTextureFetchIndex();
	}

	// Update the instance buffer
	m_InstanceBuffer.Update(_context, tempData);

	// Delete the temporary data
	delete[] tempData;
}
