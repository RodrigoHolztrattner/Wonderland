////////////////////////////////////////////////////////////////////////////////
// Filename: VWRenderShard.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "Shader\VWShaderBase.h"
#include "VWGraphicAdapter.h"
#include "VWRenderable.h"

#include "VWBuffer.h"

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
// Class name: VWRenderShard
////////////////////////////////////////////////////////////////////////////////
class VWRenderShard : VWShaderBase
{
public:

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

			return attributeDescriptions;
		}
	};

	const std::vector<Vertex> vertices = {
		{ { -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		{ { 0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { -0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } }
	};

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
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
	VWRenderShard();
	~VWRenderShard();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this render shard object
	bool Initialize(VWContext* _context);

	// Return a reference to all command buffers
	const VkCommandBuffer GetCommandBufferReference() { return m_CommandBuffer; }

	// Insert an object to be rendered
	void AddRenderable(VWRenderable* _renderable) { m_Renderables.push_back(_renderable); }


	//

	void UpdateUniformBuffer(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain, VWRenderable* _renderable, int _index);

	//
	void PrepareCommandBuffer(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain, VWRenderable* _renderable, int _imageIndex);

private:

	void CreateGraphicsPipeline(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain);

	void CreateRenderPass(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain);

	


	void CreateCommandBuffers(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain);

	void CreateUniformBuffer(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);

	//

	void CreateDescriptorPool(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);

	void CreateDescriptorSetLayout(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);

	void CreateDescriptorSet(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);


///////////////
// VARIABLES //
private: //////

	// All objects we will render
	std::vector<VWRenderable*> m_Renderables;

	VkPipelineLayout pipelineLayout;

	VkRenderPass renderPass;

	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> framebuffers;

	VkCommandBuffer m_CommandBuffer;

	VWBuffer m_UniformBuffer;

	VkDescriptorSetLayout descriptorSetLayout; // Referente à forma que os dados vão ser passados para os shaders (inclusive quais shaders) e como serão interpretados, qual posição, etc

	VkDescriptorPool descriptorPool; // Reference aos dados passados ao shader como textura e uniform buffers

	VkDescriptorSet descriptorSet; // Usa os dados reais dos buffers e cria esse descriptor set (possivelmente devemos usar isso por objeto)
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)