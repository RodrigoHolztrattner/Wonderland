////////////////////////////////////////////////////////////////////////////////
// Filename: VWBuffer.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\NamespaceDefinitions.h"
#include "..\GlobalInstance.h"

#include "VWGraphicAdapter.h"
#include "VWWindow.h"
#include "VWGraphicInstance.h"
#include "VWSwapChain.h"
#include "VWBuffer.h"
#include "VWContext.h"
#include "VWRenderable.h"
#include "Shader\VWShaderBase.h"

#include "VWMaterialShader.h"
#include "Material\VWTextureGroupManager.h"
#include "Resource\VWResourceManager.h"

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

////////////////
// FORWARDING //
////////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

/////////////
// DEFINES //
/////////////

 typedef VWWindow				Window;
 typedef VWBuffer				Buffer;
 typedef VWSwapChain			SwapChain;
 typedef VWTexture				Texture;
 typedef VWGraphicAdapter		GraphicAdapter;
 typedef VWMaterialShader		RenderShard;
 typedef VWGraphicInstance		GraphicInstance;
 typedef VWRenderable			Renderable;
 typedef VWContext				Context;
 typedef VWResourceManager		ResourceManager;
 typedef VWShaderBase			ShaderBase;

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)