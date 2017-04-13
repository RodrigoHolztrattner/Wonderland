////////////////////////////////////////////////////////////////////////////////
// Filename: VWShaderBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include "VWShaderPipelineBase.h"
#include "VWShaderDescriptorBase.h"
#include "VWShaderRenderingBase.h"
#include "VWShaderCommandBase.h"
#include "VWShaderRenderPassBase.h"

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
// Class name: VWShaderBase
////////////////////////////////////////////////////////////////////////////////
class VWShaderBase : public VWShaderPipelineBase, public VWShaderDescriptorBase, public VWShaderRenderingBase, public VWShaderCommandBase, public VWShaderRenderPassBase
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWShaderBase();
	~VWShaderBase();

///////////////
// VARIABLES //
private: //////

};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)