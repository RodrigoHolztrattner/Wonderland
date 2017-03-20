////////////////////////////////////////////////////////////////////////////////
// Filename: VWResourceVault.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "..\..\NamespaceDefinitions.h"
#include "VWResource.h"

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
// Class name: VWResourceVault
////////////////////////////////////////////////////////////////////////////////
class VWResourceVault
{
private:

	struct ResourceHolder
	{
		// The resource itself
		VWResource* resource;

		// The resource identifier
		uint32_t resourceIdentifier;
	};

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWResourceVault();
	~VWResourceVault();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the resource manager
	bool Initialize();

	// Check if a internal resource is currently loaded into memory
	VWResource* IsResourceLoaded(uint32_t _resourceIdentifier);

	// Insert a external resource into memory
	void InsertResource(VWResource* _resource, uint32_t _resourceIdentifier);

///////////////
// VARIABLES //
private: //////

	// Our internal resource array
	std::vector<ResourceHolder> m_Resources;

};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)