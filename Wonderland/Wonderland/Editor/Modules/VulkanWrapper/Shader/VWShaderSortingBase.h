////////////////////////////////////////////////////////////////////////////////
// Filename: VWShaderRenderingBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "..\VWGraphicAdapter.h"
#include "..\VWRenderable.h"

#include "..\VWBuffer.h"

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

////////////////////////////////////////////////////////////////////////////////
// Class name: VWShaderRenderingBase
////////////////////////////////////////////////////////////////////////////////
class VWShaderRenderingBase
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWShaderRenderingBase();
	~VWShaderRenderingBase();

///////////////
// RENDERING //
public: ///////

	// Add a renderable to be rendered
	void AddRenderable(VWRenderable* _renderable);

	// Render all opaque geometry
	void RenderOpaqueGeometry(VWContext* _graphicContext, int _swapchainImageIndex);

	// Render all transparent (remaining) geometry
	void RenderTransparentGeometry();	

protected:

	// Called when we start the rendering process
	virtual void BeginRender(VWContext* _graphicContext, int _swapchainImageIndex) = 0;

	// Called when we end the rendering process
	virtual void EndRender() = 0;

	// Buffers are ok, just update the instance data into the instance buffer
	virtual void UpdateInstanceData(VWContext* _context, std::vector<VWRenderable*>& _renderables);

	// Called when we need to update the shader textures
	virtual void UpdateTextures(VWRenderable* _instance);			

	// Called when we need to update the shader vertex/index buffers
	virtual void UpdateVertices(VWRenderable* _instance, uint32_t& _indexCount);			

	// Everything is ready to go, just render what was processed
	virtual void RenderCall(uint32_t _globalInstanceCount, uint32_t _indexCount, uint32_t _instanceCount);

	// Return the texture identificator for the given object
	virtual uint32_t GetTextureIdentificator(VWRenderable* _instance);

///////////////
// VARIABLES //
private: //////

	// All objects we will render
	std::vector<VWRenderable*> m_Renderables;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)