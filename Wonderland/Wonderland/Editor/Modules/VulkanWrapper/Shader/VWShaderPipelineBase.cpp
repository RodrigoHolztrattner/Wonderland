////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWShaderPipelineBase.h"
#include "..\VWGraphicAdapter.h"
#include "..\VWSwapChain.h"
#include "..\VWGraphicInstance.h"
#include "..\VWRenderable.h"
#include "..\VWContext.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

VulkanWrapper::VWShaderPipelineBase::VWShaderPipelineBase()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWShaderPipelineBase::~VWShaderPipelineBase()
{
}

std::vector<char> VulkanWrapper::VWShaderPipelineBase::ReadShaderFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

void VulkanWrapper::VWShaderPipelineBase::CreateShaderModule(VWGraphicInstance* _graphicInstance, const std::vector<char>& code, VkShaderModule& _shaderModule)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = (uint32_t*)code.data();

	if (vkCreateShaderModule(_graphicInstance->GetDevice(), &createInfo, nullptr, &_shaderModule) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create shader module!");
	}
}

void VulkanWrapper::VWShaderPipelineBase::AddViewport(float _x, float _y, float _width, float _height, float _minDepth, float _maxDepth)
{
	VkViewport viewport = {};
	viewport.x = _x;
	viewport.y = _y;
	viewport.width = _width;
	viewport.height = _height;
	viewport.minDepth = _minDepth;
	viewport.maxDepth = _maxDepth;

	m_Viewports.push_back(viewport);
}

void VulkanWrapper::VWShaderPipelineBase::AddScissor(VkOffset2D _offset, VkExtent2D _extent)
{
	VkRect2D scissor = {};
	scissor.offset = _offset;
	scissor.extent = _extent;

	m_Scissors.push_back(scissor);
}

void VulkanWrapper::VWShaderPipelineBase::AddColorBlendAttachment(VkColorComponentFlags _flags)
{
	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = _flags;
	colorBlendAttachment.blendEnable = VK_FALSE;

	m_ColorBlendAttachments.push_back(colorBlendAttachment);
}

void VulkanWrapper::VWShaderPipelineBase::AddColorBlendAttachment(VkColorComponentFlags _flags, VkBlendFactor _srcColorBlendFactor, VkBlendFactor _dstColorBlendFactor, VkBlendOp _colorBlendOp, VkBlendFactor _srcAlphaBlendFactor, VkBlendFactor _dstAlphaBlendFactor, VkBlendOp _alphaBlendOp)
{
	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = _flags;
	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = _srcColorBlendFactor;
	colorBlendAttachment.dstColorBlendFactor = _dstColorBlendFactor;
	colorBlendAttachment.colorBlendOp = _colorBlendOp;
	colorBlendAttachment.srcAlphaBlendFactor = _srcAlphaBlendFactor;
	colorBlendAttachment.dstAlphaBlendFactor = _dstAlphaBlendFactor;
	colorBlendAttachment.alphaBlendOp = _alphaBlendOp;

	m_ColorBlendAttachments.push_back(colorBlendAttachment);
}

VkPipelineViewportStateCreateInfo VulkanWrapper::VWShaderPipelineBase::CreatePipelineViewport()
{
	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = m_Viewports.size(); // Apenas maior que 1 caso seja usado um geometry shader (sendo que esse usa a viewport usando um index)
	viewportState.pViewports = m_Viewports.data();
	viewportState.scissorCount = m_Scissors.size();
	viewportState.pScissors = m_Scissors.data();

	return viewportState;
}

VkPipelineRasterizationStateCreateInfo VulkanWrapper::VWShaderPipelineBase::CreateRasterizer(VkPolygonMode _polygonMode)
{
	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = _polygonMode; // Modo final de rasterização aplicado nos vertices
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;				// rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;		// rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	return rasterizer;
}

VkPipelineMultisampleStateCreateInfo VulkanWrapper::VWShaderPipelineBase::CreateMultisampleState(VkSampleCountFlagBits _sampleCount)
{
	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = _sampleCount;

	return multisampling;
}

VkPipelineColorBlendStateCreateInfo VulkanWrapper::VWShaderPipelineBase::CreateColorBlendState()
{
	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = m_ColorBlendAttachments.size();
	colorBlending.pAttachments = m_ColorBlendAttachments.data();
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	return colorBlending;
}

VkPipelineShaderStageCreateInfo VulkanWrapper::VWShaderPipelineBase::CreateShardStage(VWGraphicInstance* _graphicInstance, char* _filename, VkShaderStageFlagBits _stage, const char* _name, VkPipelineShaderStageCreateFlags _flags, const VkSpecializationInfo* _specializationInfo)
{
	auto shaderCode = ReadShaderFile(_filename);

	VkShaderModule shaderModule;
	CreateShaderModule(_graphicInstance, shaderCode, shaderModule);

	VkPipelineShaderStageCreateInfo shaderStageInfo = {};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageInfo.stage = _stage;
	shaderStageInfo.flags = _flags;
	shaderStageInfo.module = shaderModule;
	shaderStageInfo.pName = _name;
	shaderStageInfo.pSpecializationInfo = _specializationInfo;

	return shaderStageInfo;
}

void VulkanWrapper::VWShaderPipelineBase::AddVertexInputAttributeDescription(uint32_t _binding, uint32_t _location, VkFormat _format, uint32_t _offset)
{
	VkVertexInputAttributeDescription vertexInputAttrDescription = {};

	vertexInputAttrDescription.binding = _binding;
	vertexInputAttrDescription.location = _location;
	vertexInputAttrDescription.format = _format;
	vertexInputAttrDescription.offset = _offset;

	m_VertexInputAttrDescription.push_back(vertexInputAttrDescription);
}

void VulkanWrapper::VWShaderPipelineBase::AddVertexInputBindingDescription(uint32_t _binding, uint32_t _stride, VkVertexInputRate _vertexInputRate)
{
	VkVertexInputBindingDescription bindingDescription = {};
	bindingDescription.binding = _binding;
	bindingDescription.stride = _stride;
	bindingDescription.inputRate = _vertexInputRate;

	m_VertexInputBindingDescription.push_back(bindingDescription);
}

VkPipelineVertexInputStateCreateInfo VulkanWrapper::VWShaderPipelineBase::CreateVertexInputState(VkPipelineVertexInputStateCreateFlags _flags)
{
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.flags = _flags;
	vertexInputInfo.vertexBindingDescriptionCount = m_VertexInputBindingDescription.size();
	vertexInputInfo.vertexAttributeDescriptionCount = m_VertexInputAttrDescription.size();
	vertexInputInfo.pVertexBindingDescriptions = m_VertexInputBindingDescription.data();
	vertexInputInfo.pVertexAttributeDescriptions = m_VertexInputAttrDescription.data();

	return vertexInputInfo;
}

VkPipelineInputAssemblyStateCreateInfo VulkanWrapper::VWShaderPipelineBase::CreateInputAssemblyState(VkPrimitiveTopology _topology, VkBool32 _primitiveRestartEnable, VkPipelineInputAssemblyStateCreateFlags _flags)
{
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = _topology; // Como os vertices são passados para o vertex shader (podem ser alterados por um tessellation ou geometry shader)
	inputAssembly.primitiveRestartEnable = _primitiveRestartEnable;
	inputAssembly.flags = _flags;

	return inputAssembly;
}

VkPipelineLayout VulkanWrapper::VWShaderPipelineBase::CreatePipelineLayout(VWGraphicInstance* _graphicInstance, VkDescriptorSetLayout* _setLayouts, uint32_t _totalLayouts, VkPushConstantRange* _pushConstants, uint32_t _pushConstantRangeCount, VkPipelineLayoutCreateFlags _flags)
{
	VkPipelineLayout pipelineLayout = {};
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = _totalLayouts;
	pipelineLayoutInfo.pSetLayouts = _setLayouts;
	pipelineLayoutInfo.pPushConstantRanges = _pushConstants;
	pipelineLayoutInfo.pushConstantRangeCount = _pushConstantRangeCount;
	pipelineLayoutInfo.flags = _flags;

	if (vkCreatePipelineLayout(_graphicInstance->GetDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	return pipelineLayout;
}

void VulkanWrapper::VWShaderPipelineBase::CreateFramebuffers(VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain, std::vector<VkFramebuffer>& _framebuffers, VkRenderPass _renderPass)
{
	// Get the swap chain images
	const std::vector<VkImageView>& swapChainImageViews = _swapChain->GetImageViews();
	_framebuffers.resize(swapChainImageViews.size(), VkFramebuffer());

	for (size_t i = 0; i < swapChainImageViews.size(); i++)
	{
		VkImageView attachments[] = {
			swapChainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = _renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = _swapChain->GetExtent().width;
		framebufferInfo.height = _swapChain->GetExtent().height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(_graphicInstance->GetDevice(), &framebufferInfo, nullptr, &_framebuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}