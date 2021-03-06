////////////////////////////////////////////////////////////////////////////////
// Filename: VWShaderDescriptorBase.h
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
// Class name: VWShaderDescriptorBase
////////////////////////////////////////////////////////////////////////////////
class VWShaderDescriptorBase
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWShaderDescriptorBase();
	~VWShaderDescriptorBase();

////////////////////////////////////
// DESCRIPTOR SET LAYOUT CREATION //
protected: /////////////////////////

	VkDescriptorPool CreateDescriptorPool(VWContext* _graphicContext, uint32_t _maxSets = 1);


	VkDescriptorSetLayout CreateDescriptorSetLayout(VWGraphicInstance* _graphicInstance, VkDescriptorSetLayoutCreateFlags _flags = 0);
	void AddDescriptorSetLayoutBinding(uint32_t _binding, VkDescriptorType _type, uint32_t _count, VkShaderStageFlags _flags, const VkSampler* _immutableSamplers = nullptr);

	VkDescriptorSet CreateDescriptorSet(VWContext* _graphicContext, VkDescriptorPool _pool, uint32_t _descriptorSetCount, VkDescriptorSetLayout* _layouts);

protected:



///////////////
// VARIABLES //
private: //////

	// Descriptor set layout creation
	std::vector<VkDescriptorSetLayoutBinding> m_DescriptorSetLayoutBindings;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)