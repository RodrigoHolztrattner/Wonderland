////////////////////////////////////////////////////////////////////////////////
// Filename: ApplicationInstance.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Modules\VulkanWrapper\VulkanWrapper.h"

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

// The data per thread
struct ThreadLocalData
{

};

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationInstance
////////////////////////////////////////////////////////////////////////////////
class ApplicationInstance
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	ApplicationInstance();
	~ApplicationInstance();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize();

	// Release
	void Release();

	// The update function
	void Update(float _timeElapsed);

	// Return the context reference
	VulkanWrapper::Context* GetContextReference() { return &m_Context; }

public:

	// Return if we are valid
	bool IsValid() { return m_IsValid; }
 
///////////////
// VARIABLES //
private: //////

	// Our graphic context
	VulkanWrapper::Context m_Context;

	// Our render shard
	VulkanWrapper::VWMaterialShader m_RenderShard;

	// Our renderable objects
	VulkanWrapper::Renderable m_ObjectAlpha;
	VulkanWrapper::Renderable m_ObjectBeta;
	VulkanWrapper::Renderable m_ObjectGama;

	// If we are valid
	bool m_IsValid;

};