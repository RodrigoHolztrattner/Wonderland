////////////////////////////////////////////////////////////////////////////////
// Filename: CommandModule.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\BaseModule.h"
#include "CommandType.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\..\..\..\Support\Container\Array\StaticArray.h"

/////////////
// DEFINES //
/////////////

// We know the view class
class UIBase;

// We know the UICommandComponent class
class UICommandComponent;

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: CommandModule
////////////////////////////////////////////////////////////////////////////////
class CommandModule
{
public:
	CommandModule();
	CommandModule(const CommandModule&);
	~CommandModule();

	// Initialize the command module
	bool Initialize();

	// Update all widgets
	void Update(UIBase* _widget, float _time, int _mouseX, int _mouseY);

	// Register a command
	void RegisterCommand(CommandType _command);

	// Process all commands
	void ProcessCommands(UIBase* _mainWidget, int _mouseX, int _mouseY);

	// Shutdown the command module
	void Shutdown();

private:

	// Process mouse command
	bool ProcessMouseCommand(UIBase* _widget, CommandType _command);

	// Process the keyboard command
	bool ProcessKeyboardCommand(UIBase* _widget, CommandType _command);

private:

	// The command array
	StaticArray<CommandType, 10> m_CommandArray;

	// The focus widget
	UIBase* m_FocusWidget;

	// The hover widget
	UIBase* m_HoverWidget;

	// Control keys
	bool m_IsShiftPressed;
	bool m_IsCtrlPressed;
	bool m_IsAltPressed;
};