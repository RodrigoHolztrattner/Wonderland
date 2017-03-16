////////////////////////////////////////////////////////////////////////////////
// Filename: VWContext.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\NamespaceDefinitions.h"

#include "VWContextBase.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////


////////////
// GLOBAL //
////////////

////////////////
// FORWARDING //
////////////////

class Application;

///////////////
// NAMESPACE //
///////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWResourceContext;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWContext
////////////////////////////////////////////////////////////////////////////////
class VWContext : public VWContextBase
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWContext();
	~VWContext();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize(VWGraphicAdapter* _adapter, VWResourceContext* _resourceContext);

	// Release
	void Release();

	// Begin the rendering frame
	void BeginRenderingFrame();

	// End the rendering frame
	void EndRenderingFrame();

protected:

	// The application class is a friend of us
	friend Application;

	// Do the application update
	void ApplicationUpdate();

////////////////////
// COMMAND BUFFER //
////////////////////

	// Get a valid command buffer for the current frame, the owner is the calling thread
	VkCommandBuffer GetValidFrameCommandBuffer(VkCommandBufferLevel _level);

/////////////
// TEXTURE //
/////////////

	// Load a texture async
	

///////////////
// VARIABLES //
private: //////

};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)