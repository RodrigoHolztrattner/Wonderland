////////////////////////////////////////////////////////////////////////////////
// Filename: HGWidgetShader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\VulkanWrapper\VulkanWrapper.h"

#include "..\HGWidget.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

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

// HookGui workspace
NamespaceBegin(HookGui)

////////////////
// FORWARDING //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HGWidgetShader
////////////////////////////////////////////////////////////////////////////////
class HGWidgetShader : public VulkanWrapper::ShaderBase
{
public:

	uint32_t MaximumInstances = 64;

	struct InstanceData
	{
		glm::vec4 position;
		glm::vec4 size;
		glm::vec4 rotation;
		glm::vec4 extra;
	};

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGWidgetShader();
	~HGWidgetShader();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this render shard object
	bool Initialize(VulkanWrapper::Context* _context);

	// Return a reference to our command buffer
	const VkCommandBuffer GetCommandBufferReference() { return m_CommandBuffer; }

	// Update the uniform buffer
	void UpdateUniformBuffer(VulkanWrapper::Context* _graphicContext);

	// Add a widget to be rendered
	void AddWidget(HGWidget* _widget);

	// Render all widgets
	void Render(VulkanWrapper::Context* _graphicContext, int _swapchainImageIndex);

	// Is this shader is valid to be used
	bool IsValid();

private:

	// Create the graphics pipeline
	void CreateGraphicsPipeline(VulkanWrapper::Context* _graphicContext);

	// Create the render pass
	void CreateRenderPass(VulkanWrapper::Context* _graphicContext);

	// Create the descriptor set
	void CreateDescriptorSet(VulkanWrapper::Context* _graphicContext);

	// Create our buffers
	void CreateUniformBuffer(VulkanWrapper::Context* _graphicContext);
	void CreateInstanceBuffer(VulkanWrapper::Context* _context);

private:


	// Called when we start the rendering process
	void BeginRender(VulkanWrapper::Context* _graphicContext, int _swapchainImageIndex);

	// Called when we end the rendering process
	void EndRender();

	// Buffers are ok, just update the instance data into the instance buffer
	void UpdateInstanceData(VulkanWrapper::Context* _context);

///////////////
// VARIABLES //
private: //////

	// Our renderables
	std::vector<HGWidget*> m_Renderables;

	// The pipeline layout, our render pass and the graphics pipeline
	VkPipelineLayout m_PipelineLayout;
	VkRenderPass m_RenderPass;
	VkPipeline m_GraphicsPipeline;

	// Our descriptor data
	VkDescriptorSetLayout m_DescriptorSetLayout; // Referente à forma que os dados vão ser passados para os shaders (inclusive quais shaders) e como serão interpretados, qual posição, etc
	VkDescriptorPool m_DescriptorPool; // Reference aos dados passados ao shader como textura e uniform buffers
	VkDescriptorSet m_DescriptorSet; // Usa os dados reais dos buffers e cria esse descriptor set (possivelmente devemos usar isso por objeto)

	// Our framebuffers
	std::vector<VkFramebuffer> m_Framebuffers;

	// The command buffer we are using to write all the draw calls
	VkCommandBuffer m_CommandBuffer;

	// Our buffers
	VulkanWrapper::Buffer m_InstanceBuffer;
	VulkanWrapper::Buffer m_UniformBuffer;

	// Our widget model object
	VulkanWrapper::ModelReference m_WidgetModel;
};

// HookGui workspace
NamespaceEnd(HookGui)