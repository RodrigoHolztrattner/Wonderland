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
#include "Modules\HookGui\HGWidget.h"
#include "Modules\HookGui\Shaders\HGWidgetShader.h"
#include "Modules\HookGui\HookGui.h"

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

	// Return the root widget
	HookGui::HGWidget* GetRootWidget() { return &m_RootWidget; }

public:

	// Return if we are valid
	bool IsValid() { return m_IsValid; }
 
///////////////
// VARIABLES //
private: //////

	// Our graphic context
	VulkanWrapper::Context m_Context;

	// Our render shard
	HookGui::HGWidgetShader m_WidgetShader;

	// Our widget manager
	HookGui::WidgetManager m_WidgetManager;

	// Our root widget
	HookGui::HGWidget m_RootWidget;

	// Our renderable objects
	HookGui::HGWidget m_MainWidget;
	HookGui::HGWidget m_MenuWidget;

	// If we are valid
	bool m_IsValid;
};