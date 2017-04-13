////////////////////////////////////////////////////////////////////////////////
// Filename: VWCoreUtils.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "VWGraphicInstance.h"

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

////////////////////////////////////////////////////////////////////////////////
// Class name: VWCoreUtils
////////////////////////////////////////////////////////////////////////////////
class VWCoreUtils
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWCoreUtils();
	~VWCoreUtils();

//////////////////
// MAIN METHODS //
public: //////////

	// Find the memory type
	static uint32_t FindMemoryType(VWGraphicInstance* _graphicInstance, uint32_t typeFilter, VkMemoryPropertyFlags properties);

///////////////
// VARIABLES //
protected: ////

};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)