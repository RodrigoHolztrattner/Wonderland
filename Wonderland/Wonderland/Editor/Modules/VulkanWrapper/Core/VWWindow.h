////////////////////////////////////////////////////////////////////////////////
// Filename: VWWindow.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

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
class VWSwapChain;
class VWWindow;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWWindowInputCallback
////////////////////////////////////////////////////////////////////////////////
class VWWindowInputCallback
{
public:

	// Process a key callback
	virtual void ProcessKeyCallback(int key, int scancode, int action, int mods) = 0;

	// Process a mouse callback
	virtual void ProcessMouseCallback(int button, int action, int mods) = 0;

	// The glfw window reference
	GLFWwindow* windowReference;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: VWWindow
////////////////////////////////////////////////////////////////////////////////
class VWWindow
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWWindow();
	~VWWindow();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize();

	// Release
	void Release();

	// Return if this object was initialized
	bool IsValid();

	// Return the window
	GLFWwindow* GetWindow();

	// Return the width/height
	unsigned int GetWidth();
	unsigned int GetHeight();

	// Set the input callback object
	void SetInputCallbackObject(VWWindowInputCallback* _inputCallbackObject);

	// Return the input callback object
	VWWindowInputCallback* GetInputCallbackObject();

private:

///////////////
// VARIABLES //
private: //////

	// The glfw window
	GLFWwindow* m_Window;

	// The size
	unsigned int m_Width;
	unsigned int m_Height;

	// If this object is valid
	bool m_IsValid;

	// Our input callback object
	VWWindowInputCallback* m_InputCallbackObject;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)