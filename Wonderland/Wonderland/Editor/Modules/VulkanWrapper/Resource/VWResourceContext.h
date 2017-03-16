////////////////////////////////////////////////////////////////////////////////
// Filename: VWResourceContext.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include "..\VWGraphicAdapter.h"
#include "VWResourceManager.h"
#include "VWResourceIndexLoader.h"

#include "Texture\VWTextureGroupIndex.h"

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
// Class name: VWResourceContext
////////////////////////////////////////////////////////////////////////////////
class VWResourceContext
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWResourceContext();
	~VWResourceContext();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize(VWGraphicAdapter* _adapter, Packet::Manager* _packetManager);

	// Release
	void Release();

	// Process the resource requests
	void ProcessResourceRequests();

	// Return the resource manager reference
	VWResourceManager* GetResourceManager() { return &m_ResourceManager; }

	// Return the texture group index loader reference
	VWResourceIndexLoader<VWTextureGroupIndex>* GetTextureGroupIndexLoader() { return &m_TextureGroupIndexLoader; }

///////////////
// VARIABLES //
private: //////

	// The graphic adapter reference
	VWGraphicAdapter* m_GraphicAdapterReference;

	// The resource manager
	VWResourceManager m_ResourceManager;

	// All the index loaders
	VWResourceIndexLoader<VWTextureGroupIndex> m_TextureGroupIndexLoader;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)