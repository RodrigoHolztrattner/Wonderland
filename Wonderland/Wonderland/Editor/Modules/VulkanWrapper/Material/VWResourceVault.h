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

	struct InternalResourceHolder
	{
		// The resource itself
		VWResource* resource;

		// The resource identifier
		uint32_t resourceIdentifier;
	};

	struct ExternalResourceHolder
	{
		// The resource itself
		VWResource* resource;

		// The resource path
		std::string resourcePath;
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
	VWResource* IsInternalResourceLoaded(uint32_t _resourceIdentifier);

	// Check if a external resource is currently loaded into memory
	VWResource* IsExternalResourceLoaded(std::string _resourcePath);

	// Insert a external resource into memory
	void InsertExternalResource(VWResource* _resource, std::string _resourcePath);

///////////////
// VARIABLES //
private: //////

	// Our internal resource array
	std::vector<InternalResourceHolder> m_InternalResources;

	// Our external resource array
	std::vector<ExternalResourceHolder> m_ExternalResources;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)