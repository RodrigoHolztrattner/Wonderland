////////////////////////////////////////////////////////////////////////////////
// Filename: VWDescriptorSetCreator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <vector>

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

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWDescriptorSetCreator
////////////////////////////////////////////////////////////////////////////////
class VWDescriptorSetCreator
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWDescriptorSetCreator();
	~VWDescriptorSetCreator();

//////////////////
// MAIN METHODS //
public: //////////

	// Return our descriptor set layout
	VkDescriptorSetLayout GetDescriptorSetLayout() { return m_DescriptorSetLayout; }

protected:

	void CreateDescriptorPool(VWContext* _graphicContext, uint32_t _maxSets = 1);
	void CreateDescriptorSetLayout(VWContext* _graphicContext, VkDescriptorSetLayoutCreateFlags _flags = 0);

	//
	void AddDescriptorSetLayoutBinding(uint32_t _binding, VkDescriptorType _type, uint32_t _count, VkShaderStageFlags _flags, const VkSampler* _immutableSamplers = nullptr);

///////////////
// VARIABLES //
protected: ////

	// Our descriptor poll where texture agrupments will create their descriptor set
	VkDescriptorPool m_DescriptorPool;

	// Our descriptor set layout matching the shader interface
	VkDescriptorSetLayout m_DescriptorSetLayout;

	// Descriptor set layout creation
	std::vector<VkDescriptorSetLayoutBinding> m_DescriptorSetLayoutBindings;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)