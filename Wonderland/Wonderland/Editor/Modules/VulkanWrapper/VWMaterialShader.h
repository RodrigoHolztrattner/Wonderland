////////////////////////////////////////////////////////////////////////////////
// Filename: VWMaterialShader.h
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

class VWContext;
class VWRenderable;
class VWTexture;
class VWBuffer;

//TODO: Create the material oposite helper class (for instancing data)


////////////////////////////////////////////////////////////////////////////////
// Class name: VWMaterialShader
////////////////////////////////////////////////////////////////////////////////
class VWMaterialShader : public VWShaderBase
{
public:

	uint32_t MaximumInstances = 64;

	struct InstanceData
	{
		glm::vec4 model1;
		glm::vec4 model2;
		glm::vec4 model3;
		glm::vec4 other;
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
	VWMaterialShader();
	~VWMaterialShader();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this render shard object
	bool Initialize(VWContext* _context);

	// Return a reference to all command buffers
	const VkCommandBuffer GetCommandBufferReference() { return m_CommandBuffer; }

	//

	void UpdateUniformBuffer(VWContext* _graphicContext, VWRenderable* _renderable);

private:

	void CreateGraphicsPipeline(VWContext* _graphicContext);

	void CreateRenderPass(VWContext* _graphicContext);

	
	void CreateUniformBuffer(VWContext* _graphicContext);

	void CreateInstanceBuffer(VWContext* _context);

	//

	void CreateDescriptorPool(VWContext* _graphicContext);

	void CreateDescriptorSetLayout(VWContext* _graphicContext);

	void CreateDescriptorSet(VWContext* _graphicContext);

	//

	// Called when we start the rendering process
	void BeginRender(VWContext* _graphicContext, int _swapchainImageIndex);

	// Called when we end the rendering process
	void EndRender();

	// Buffers are ok, just update the instance data into the instance buffer
	void UpdateInstanceData(VWContext* _context, std::vector<VWRenderable*>& _renderables);

	// Called when we need to update the shader textures
	void UpdateTextures(VWRenderable* _instance);

	// Called when we need to update the shader model data
	void UpdateModel(VWRenderable* _instance, uint32_t& _indexCount);

	// Everything is ready to go, just render what was processed
	void RenderCall(uint32_t _globalInstanceCount, uint32_t _indexCount, uint32_t _instanceCount);


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

	VWBuffer m_InstanceBuffer;

	VkDescriptorSetLayout descriptorSetLayout; // Referente à forma que os dados vão ser passados para os shaders (inclusive quais shaders) e como serão interpretados, qual posição, etc

	VkDescriptorPool descriptorPool; // Reference aos dados passados ao shader como textura e uniform buffers

	VkDescriptorSet descriptorSet; // Usa os dados reais dos buffers e cria esse descriptor set (possivelmente devemos usar isso por objeto)
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)