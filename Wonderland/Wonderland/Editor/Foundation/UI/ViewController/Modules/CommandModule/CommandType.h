////////////////////////////////////////////////////////////////////////////////
// Filename: CommandType.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

// The command control keys
enum CommandControlKey
{
	None	=	0,
	Shift	=	1 << 0,
	Ctrl	=	1 << 1,
	Alt		=	1 << 2
};

// The command actor enum
enum class CommandActor
{
	Mouse,
	Keyboard,
	System
};

// The command action enum
enum class CommandAction
{
	Press = GLFW_PRESS,
	Release = GLFW_RELEASE,
	Hold = GLFW_REPEAT,
	OnFocus = 10,
	LostFocus = 11,
	Hover = 20,
	HoverClear = 21,
	Update = 22
};

// The button type
enum class CommandButton
{
	None	=	-1,
	Left	=	0,
	Right	=	1,
	Middle	=	2
};

// The command type
struct CommandType
{
	CommandType() {}
	CommandType(CommandActor _actor, CommandAction _action, unsigned int _firstParam, unsigned int _secondParam, void* _object = nullptr)
	{
		actor = _actor;
		action = _action;
		button = CommandButton::None;
		firstParam = _firstParam;
		secondParam = _secondParam;
		controlKey = CommandControlKey::None;
		object = _object;
	}
	CommandType(CommandActor _actor, CommandAction _action, CommandButton _button, unsigned int _firstParam, unsigned int _secondParam, void* _object = nullptr)
	{
		actor = _actor;
		action = _action;
		button = _button;
		firstParam = _firstParam;
		secondParam = _secondParam;
		controlKey = CommandControlKey::None;
		object = _object;
	}
	CommandType(const CommandType& _other)
	{
		actor = _other.actor;
		action = _other.action;
		button = _other.button;
		firstParam = _other.firstParam;
		secondParam = _other.secondParam;
		controlKey = _other.controlKey;
		object = _other.object;
	}

	// The command data
	CommandActor actor;

	// The command action
	CommandAction action;

	// The command button
	CommandButton button;

	// The first message-dependent param
	unsigned int firstParam;

	// The second message-dependent param
	unsigned int secondParam;

	// The command control key
	CommandControlKey controlKey;

	// Any object
	void *object;
};