////////////////////////////////////////////////////////////////////////////////
// Filename: VWShaderPipelineBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "..\Core\VWGraphicAdapter.h"
#include "..\Renderable\VWRenderable.h"

#include "..\Resource\VWBuffer.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWGraphicAdapter;
class VWWindow;
class VWSwapChain;
class VWGraphicInstance;
class VWRenderable;
class VWContext;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWShaderPipelineBase
////////////////////////////////////////////////////////////////////////////////
class VWShaderPipelineBase
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWShaderPipelineBase();
	~VWShaderPipelineBase();

///////////////////////
// PIPELINE CREATION //
protected: ////////////

	VkPipelineShaderStageCreateInfo CreateShardStage(VWGraphicInstance* _graphicInstance, char* _filename, VkShaderStageFlagBits _stage, const char* _name, VkPipelineShaderStageCreateFlags _flags = 0, const VkSpecializationInfo* _specializationInfo = nullptr);
	VkPipelineVertexInputStateCreateInfo CreateVertexInputState(VkPipelineVertexInputStateCreateFlags _flags = 0);
	VkPipelineInputAssemblyStateCreateInfo CreateInputAssemblyState(VkPrimitiveTopology _topology, VkBool32 _primitiveRestartEnable, VkPipelineInputAssemblyStateCreateFlags _flags = 0);
	VkPipelineViewportStateCreateInfo CreatePipelineViewport();
	VkPipelineRasterizationStateCreateInfo CreateRasterizer(VkPolygonMode _polygonMode);
	VkPipelineMultisampleStateCreateInfo CreateMultisampleState(VkSampleCountFlagBits _sampleCount);
	VkPipelineDepthStencilStateCreateInfo CreateDepthStencilState(VkBool32 _testEnable, VkBool32 _writeEnable, VkCompareOp _compareOp, VkBool32 _boundsTestEnable, VkBool32 _stencilTestEnable, VkStencilOpState _front = {}, VkStencilOpState _back = {}, float _minDepthBounds = 0, float _maxDepthBounds = 0);
	VkPipelineColorBlendStateCreateInfo CreateColorBlendState();
	VkPipelineLayout CreatePipelineLayout(VWGraphicInstance* _graphicInstance, VkDescriptorSetLayout* _setLayouts, uint32_t _totalLayouts, VkPushConstantRange* _pushConstants = nullptr, uint32_t _pushConstantRangeCount = 0, VkPipelineLayoutCreateFlags _flags = 0);
	void AddVertexInputAttributeDescription(uint32_t _binding, uint32_t _location, VkFormat _format, uint32_t _offset);
	void AddVertexInputBindingDescription(uint32_t _binding, uint32_t _stride, VkVertexInputRate _vertexInputRate);
	void AddViewport(float _x, float _y, float _width, float _height, float _minDepth, float _maxDepth);
	void AddScissor(VkOffset2D _offset, VkExtent2D _extent);
	void AddColorBlendAttachment(VkColorComponentFlags _flags);
	void AddColorBlendAttachment(VkColorComponentFlags _flags, VkBlendFactor _srcColorBlendFactor, VkBlendFactor _dstColorBlendFactor, VkBlendOp _colorBlendOp, VkBlendFactor _srcAlphaBlendFactor, VkBlendFactor _dstAlphaBlendFactor, VkBlendOp _alphaBlendOp);
	
///////////////////
// OTHER METHODS //
protected: ////////

	// Create framebuffers
	void CreateFramebuffers(VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain, std::vector<VkFramebuffer>& _framebuffers, VkRenderPass _renderPass);

	// Read a shader fiçe
	std::vector<char> ReadShaderFile(const std::string& filename);

	// Create a shader module
	void CreateShaderModule(VWGraphicInstance* _graphicInstance, const std::vector<char>& code, VkShaderModule& _shaderModule);

///////////////
// VARIABLES //
private: //////

	// Pipeline creation variables
	std::vector<VkVertexInputAttributeDescription> m_VertexInputAttrDescription;
	std::vector<VkVertexInputBindingDescription> m_VertexInputBindingDescription;
	std::vector<VkViewport> m_Viewports;
	std::vector<VkRect2D> m_Scissors;
	std::vector<VkPipelineColorBlendAttachmentState> m_ColorBlendAttachments;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)