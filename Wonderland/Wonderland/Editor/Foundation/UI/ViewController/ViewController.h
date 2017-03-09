////////////////////////////////////////////////////////////////////////////////
// Filename: ViewController.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "Modules\WindowModule\WindowModule.h"
#include "Modules\CommandModule\CommandModule.h"
#include "Modules\RenderModule\RenderModule.h"
#include "..\UI.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <thread>

// #include "..\Base\UIViewShader.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

//
class UITextField;

////////////////////////////////////////////////////////////////////////////////
// Class name: ViewController
////////////////////////////////////////////////////////////////////////////////
class ViewController
{
/////////////
// FRIENDS //
public: /////

	// All modules are friends
	friend WindowModule;
	friend CommandModule;
	friend RenderModule;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
public: //////////////////////

	// Constructor / Destructor
	ViewController();
	~ViewController();

////////////////////
// INITIALIZATION //
public: ////////////

	// Initialize the graphic system
	virtual bool Initialize();

	// Frame update callback
	virtual void FrameUpdate(double _time);

protected:

	// Start updating
	void StartUpdating();

private:

	// Initialize all modules
	bool InitializeModules();

///////////////
// CALLBACKS //
public: ///////

	// Key callback
	virtual void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

	// Mouse button callback
	virtual void MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods);

private:
	
	// ...
	void Exit(void* _data);

	// Frame update aux
	void FrameUpdateAux();

///////////////
// VARIABLES //
protected: ////

	// The main view
	UIView* m_MainView;

private:

	// The update thread
	std::thread m_UpdateThread;

/////////////
// MODULES //
private: ////

	// All modules
	WindowModule m_WindowModule;
	CommandModule m_CommandModule;
	RenderModule m_RenderModule;
};
