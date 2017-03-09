////////////////////////////////////////////////////////////////////////////////
// Filename: View.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Base\UIBase.h"

#include "..\..\..\..\Support\Container\Array\Array.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

// We know the command type
struct CommandType;

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: View
////////////////////////////////////////////////////////////////////////////////
class View : public UIBase
{
public:
	View(UIBase* _parent);
	~View();

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

	// Update this widget
	virtual void Update(float _time);

///////////////
// RENDERING //
public: ///////

	// Render this view
	virtual void Render();

	// The mouse hold type
	enum class MouseHoldType
	{
		None,
		Top,
		Right,
		Bottom,
		Left,
		Center
	};

	// The mouse hold type
	MouseHoldType m_MouseHoldType;

	// Mouse offset
	Vector2 m_MouseOffset;

	// The original mouse location, position and size
	Vector2 m_MouseOriginalLocation;
	Vector2 m_OriginalSize;

};
