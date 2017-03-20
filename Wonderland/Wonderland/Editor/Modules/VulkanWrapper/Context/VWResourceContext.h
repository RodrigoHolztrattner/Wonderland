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

#include "..\Core\VWGraphicAdapter.h"
#include "..\..\Hoard\Hoard.h"

#include "..\Resource\Texture\VWTextureGroupIndex.h"
#include "..\Resource\Model\VWModelIndex.h"

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
	Hoard::ResourceManager* GetResourceManager() { return &m_ResourceManager; }

	// Return all index loader references
	Hoard::Supply::IndexLoader<VWTextureGroupIndex>* GetTextureGroupIndexLoader() { return &m_TextureGroupIndexLoader; }
	Hoard::Supply::IndexLoader<VWModelIndex>* GetModelIndexLoader() { return &m_ModelIndexLoader; }

///////////////
// VARIABLES //
private: //////

	// The graphic adapter reference
	VWGraphicAdapter* m_GraphicAdapterReference;

	// The resource manager
	Hoard::ResourceManager m_ResourceManager;

	// All the index loaders
	Hoard::Supply::IndexLoader<VWTextureGroupIndex> m_TextureGroupIndexLoader;
	Hoard::Supply::IndexLoader<VWModelIndex> m_ModelIndexLoader;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)