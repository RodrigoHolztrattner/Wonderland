////////////////////////////////////////////////////////////////////////////////
// Filename: VWContextBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include "..\Core\VWGraphicAdapter.h"
#include "..\Core\VWWindow.h"
#include "..\Core\VWGraphicInstance.h"
#include "..\Core\VWSwapChain.h"
// #include "VWRenderShard.h"

#include "..\Misc\VWFrameCommandBufferAllocator.h"
#include "VWResourceContext.h"
#include "..\..\Hoard\Hoard.h"

#include "..\Resource\Texture\VWTextureGroupManager.h"
#include "..\Resource\Model\VWModelManager.h"

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
// Class name: VWContextBase
////////////////////////////////////////////////////////////////////////////////
class VWContextBase
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWContextBase();
	~VWContextBase();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	virtual bool Initialize(VWGraphicAdapter* _adapter, VWResourceContext* _resourceContext) = 0;

	// Release
	virtual void Release() = 0;

	// Find the memory type
	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

public:

	// Return if we are valid
	bool IsValid() { return m_IsValid; }

	// Return the graphic adapter reference
	VWGraphicAdapter* GetGraphicAdapter() { return m_GraphicAdapterReference; }

	// Return our resource context reference
	VWResourceContext* GetResourceContext() { return m_ResourceContextReference; }

	// Return our window
	VWWindow* GetWindow() { return &m_Window; }

	// Return our graphic instance
	VWGraphicInstance* GetGraphicInstance() { return &m_GraphicInstance; }

	// Return our swap chain
	VWSwapChain* GetSwapChain() { return &m_SwapChain; }

	// Return the command buffer allocator
	VWFrameCommandBufferAllocator* GetCommandBufferAllocator() { return &m_CommandBufferAllocator; }

	// Return our texture group manager
	VWTextureGroupManager* GetTextureGroupManager() { return &m_TextureGroupManager; }

	// Return our model manager
	VWModelManager* GetModelManager() { return &m_ModelManager; }

///////////////
// VARIABLES //
protected: ////

	// A ptr to our graphic adapter
	VWGraphicAdapter* m_GraphicAdapterReference;

	// A ptr to our resource context
	VWResourceContext* m_ResourceContextReference;

	// Our window instance
	VWWindow m_Window;

	// Our graphic instance
	VWGraphicInstance m_GraphicInstance;

	// Our swap chain instance
	VWSwapChain m_SwapChain;

	// Our command buffer allocator
	VWFrameCommandBufferAllocator m_CommandBufferAllocator;

	// Our texture group manager
	VWTextureGroupManager m_TextureGroupManager;

	// Our model manager
	VWModelManager m_ModelManager;

	// If we are valid
	bool m_IsValid;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)