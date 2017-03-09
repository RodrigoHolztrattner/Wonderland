////////////////////////////////////////////////////////////////////////////////
// Filename: VWMaterial.h
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
class VWContext;
class VWObject;

////////////////
// STRUCTURES //
////////////////

//TODO: Collect data from the renderable using the parameters

////////////////////////////////////////////////////////////////////////////////
// Class name: VWMaterial
////////////////////////////////////////////////////////////////////////////////
class VWMaterial
{
public:

	struct DescriptorLayoutBindingAux
	{
		// The binding name
		std::string sBindingName;

		// The binding info itself
		VkDescriptorSetLayoutBinding sDescriptorBindingInfo;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWMaterial();
	~VWMaterial();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize(VWContext* _graphicContext);

	// Release this image
	void Release();

	// Return if this image was initialized
	bool IsRead();

	void CreateDescriptorPool(VWContext* _graphicContext, uint32_t _maxSets = 1);
	void CreateDescriptorSetLayout(VWContext* _graphicContext, VkDescriptorSetLayoutCreateFlags _flags = 0);

	//
	void AddDescriptorSetLayoutBinding(uint32_t _binding, VkDescriptorType _type, std::string _bindingName, uint32_t _count, VkShaderStageFlags _flags, const VkSampler* _immutableSamplers = nullptr);

	// Generate a descriptor set from our layout
	VkDescriptorSet GenerateDescriptorSet(VWContext* _context);



private:

	void FindBindingsForDescriptorSet(VWContext* _graphicContext, VkDescriptorSet _descriptorSet, VWObject* _object);

///////////////
// VARIABLES //
private: //////

	// If this image was initialized
	bool m_Initialized;

	// Our descriptor poll where texture agrupments will create their descriptor set
	VkDescriptorPool m_DescriptorPool;

	// Our descriptor set layout matching the shader interface
	VkDescriptorSetLayout m_DescriptorSetLayout;

	// This is our static descriptor set, we will only use it if there ir no external dependency inside the rendering phase.
	// This descriptor set was made to be used with instancing
	VkDescriptorSet m_StaticDescriptorSet;

	//
	//
	//

	// Descriptor set layout creation
	std::vector<DescriptorLayoutBindingAux> m_DescriptorSetLayoutBindings;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)