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

//

#include "Core\VWGraphicAdapter.h"
#include "Core\VWGraphicInstance.h"
#include "Core\VWSwapChain.h"
#include "Core\VWWindow.h"

#include "Context\VWContext.h"
#include "Context\VWResourceContext.h"

#include "Resource\VWBuffer.h"
#include "Resource\VWImageArray.h"

#include "Resource\Model\VWModel.h"
#include "Resource\Model\VWModelIndex.h"
#include "Resource\Model\VWModelManager.h"

#include "Resource\Texture\VWTexture.h"
#include "Resource\Texture\VWTextureGroup.h"
#include "Resource\Texture\VWTextureGroupIndex.h"
#include "Resource\Texture\VWTextureGroupManager.h"

#include "Renderable\VWRenderable.h"

#include "Shader\VWShaderBase.h"

#include "VWMaterialShader.h"

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

// Core
typedef VWGraphicAdapter			GraphicAdapter;
typedef VWGraphicInstance			GraphicInstance;
typedef VWSwapChain					SwapChain;
typedef VWWindow					Window;

// Context
typedef VWContext					Context;
typedef VWResourceContext			ResourceContext;

// Resource
typedef VWBuffer					Buffer;
typedef VWImageArray				ImageArray;

// Resource/Model
typedef VWModel						Model;
typedef VWModelIndex				ModelIndex;
typedef VWModelManager				ModelManager;

// Resource/Texture
typedef VWTexture					Texture;
typedef VWTextureGroup				TextureGroup;
typedef VWTextureGroupIndex			TextureGroupIndex;
typedef VWTextureGroupManager		TextureGroupManager;

// Renderable
typedef VWRenderable				Renderable;

// Shader
typedef VWShaderBase				ShaderBase;

// ...
typedef VWMaterialShader			MaterialShader;

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)