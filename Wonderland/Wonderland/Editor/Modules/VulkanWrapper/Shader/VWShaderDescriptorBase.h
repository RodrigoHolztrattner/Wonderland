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

#include "..\VWGraphicAdapter.h"
#include "..\VWRenderable.h"

#include "..\VWBuffer.h"

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

	VkDescriptorSetLayout CreateDescriptorSetLayout(VWGraphicInstance* _graphicInstance, VkDescriptorSetLayoutCreateFlags _flags = 0);
	void AddDescriptorSetLayoutBinding(uint32_t _binding, VkDescriptorType _type, uint32_t _count, VkShaderStageFlags _flags, const VkSampler* _immutableSamplers = nullptr);

///////////////
// VARIABLES //
private: //////

	// Descriptor set layout creation
	std::vector<VkDescriptorSetLayoutBinding> m_DescriptorSetLayoutBindings;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)