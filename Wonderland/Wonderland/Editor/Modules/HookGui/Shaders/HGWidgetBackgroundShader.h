////////////////////////////////////////////////////////////////////////////////
// Filename: HGWidgetBackgroundShader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\VulkanWrapper\VulkanWrapper.h"

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

// Just another graphic wrapper
NamespaceBegin(HookGui)

////////////////
// FORWARDING //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HGWidgetBackgroundShader
////////////////////////////////////////////////////////////////////////////////
class HGWidgetBackgroundShader : public VulkanWrapper::VWShaderBase
{
public:

	uint32_t MaximumInstances = 64;

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;
		glm::vec2 texCoord;
	};

	struct InstanceData
	{
		glm::vec4 model1;
		glm::vec4 model2;
		glm::vec4 model3;
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
	HGWidgetBackgroundShader();
	~HGWidgetBackgroundShader();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this render shard object
	bool Initialize(VulkanWrapper::VWContext* _context);

	// Return a reference to all command buffers
	const VkCommandBuffer GetCommandBufferReference() { return m_CommandBuffer; }

	//

	void UpdateUniformBuffer(VulkanWrapper::VWContext* _graphicContext, VulkanWrapper::VWRenderable* _renderable);

private:

	void CreateGraphicsPipeline(VulkanWrapper::VWContext* _graphicContext);

	void CreateRenderPass(VulkanWrapper::VWContext* _graphicContext);

	
	void CreateUniformBuffer(VulkanWrapper::VWContext* _graphicContext);

	void CreateInstanceBuffer(VulkanWrapper::VWContext* _context);

	//

	void CreateDescriptorPool(VulkanWrapper::VWContext* _graphicContext);

	void CreateDescriptorSetLayout(VulkanWrapper::VWContext* _graphicContext);

	void CreateDescriptorSet(VulkanWrapper::VWContext* _graphicContext);

	//

	// Called when we start the rendering process
	void BeginRender(VulkanWrapper::VWContext* _graphicContext, int _swapchainImageIndex);

	// Called when we end the rendering process
	void EndRender();

	// Buffers are ok, just update the instance data into the instance buffer
	void UpdateInstanceData(VulkanWrapper::VWContext* _context, std::vector<VulkanWrapper::VWRenderable*>& _renderables);

	// Called when we need to update the shader textures
	void UpdateTextures(VulkanWrapper::VWRenderable* _instance);

	// Called when we need to update the shader vertex/index buffers
	void UpdateVertices(VulkanWrapper::VWRenderable* _instance, uint32_t& _indexCount);

	// Everything is ready to go, just render what was processed
	void RenderCall(uint32_t _globalInstanceCount, uint32_t _indexCount, uint32_t _instanceCount);


///////////////
// VARIABLES //
private: //////

	// All objects we will render
	std::vector<VulkanWrapper::VWRenderable*> m_Renderables;

	VkPipelineLayout pipelineLayout;

	VkRenderPass renderPass;

	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> framebuffers;

	VkCommandBuffer m_CommandBuffer;

	VulkanWrapper::VWBuffer m_UniformBuffer;

	VulkanWrapper::VWBuffer m_InstanceBuffer;

	VkDescriptorSetLayout descriptorSetLayout; // Referente à forma que os dados vão ser passados para os shaders (inclusive quais shaders) e como serão interpretados, qual posição, etc

	VkDescriptorPool descriptorPool; // Reference aos dados passados ao shader como textura e uniform buffers

	VkDescriptorSet descriptorSet; // Usa os dados reais dos buffers e cria esse descriptor set (possivelmente devemos usar isso por objeto)
};

// Just another graphic wrapper
NamespaceEnd(HookGui)