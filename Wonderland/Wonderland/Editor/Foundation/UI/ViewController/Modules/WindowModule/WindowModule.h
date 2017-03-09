////////////////////////////////////////////////////////////////////////////////
// Filename: WindowModule.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\BaseModule.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\..\..\..\Support\Math\Math.h"

/////////////
// DEFINES //
/////////////

// We know the view controller class
class ViewController;

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: WindowModule
////////////////////////////////////////////////////////////////////////////////
class WindowModule : public BaseModule
{
public:
	WindowModule();
	WindowModule(const WindowModule&);
	~WindowModule();

	// Initialize the window module
	bool Initialize();

	// Set the window callback
	void SetWindowCallback(ViewController* _viewController);

	// Return the window module window
	GLFWwindow* GetModuleWindow() { return m_Window; }

	// Shutdown the window module
	void Shutdown();

	// Return the window frame
	Vector4 GetWindowFrame() { return m_WindowFrame; }

private:

	// The window
	GLFWwindow* m_Window;

	// The window frame
	Vector4 m_WindowFrame;

};