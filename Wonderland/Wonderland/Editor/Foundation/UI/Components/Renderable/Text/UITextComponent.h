////////////////////////////////////////////////////////////////////////////////
// Filename: UITextComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\ECS\ECS_Component.h"
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"
#include "..\..\Frame\UIFrameToken.h"
#include "UIFont.h"
#include "UIString.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

/** UIFrameComponent */
class UIFrameComponent;

/** UIFrameComponent */
class UIStateComponent;

// We know the CommandType struct
struct CommandType;

////////////////////////////////////////////////////////////////////////////////
// Class name: UITextComponent
////////////////////////////////////////////////////////////////////////////////
class UITextComponent : public ECS_Component
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	UITextComponent();
	UITextComponent(const UITextComponent&);
	~UITextComponent();

private:
 
    // Add a unique ID to this component class
    AddComponentUniqueID(UITextComponent);

	// Register the class dependencies
	RegisterClassDependencies(UIFrameComponent, UIStateComponent);

///////////////
// MODIFIERS //
public: ///////

	// Set the font type
	bool SetFontType(char* _fontName, unsigned int _fontSize);

	// Set the formatation
	void SetFormatation(UIString::HorizontalFormatation _horizontal, UIString::VerticalFormatation _vertical);

	// Set the pad amount
	void SetPadAmout(Vector2 _padAmount);

	// Set the text
	void SetText(std::string _text);

	// Set/get the text color
	void SetTextColor(Vector4 _color);

	// Return the text color
	Vector4 GetTextColor();

	// Return the text
	std::vector<UIChar> GetText();

	// Return the font type
	UIFont* GetFont();

	// Process a command
	void ProcessCommand(CommandType* _command);

	// Check if the cursor is active
	bool IsCursorActive();

	// Return the cursor data
	UIChar GetCursorData();

	// Return the max dimension used by the text
	Vector2 GetMaxDimensionSize();

/////////////
// VIRTUAL //
public: /////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed);

	// The clear method
	virtual void Clear();

//////////////
// CALLBACK //
private: /////


///////////////
// VARIABLES //
private: //////

	// Our string
	UIString m_String;

	// The text color
	Vector4 m_TextColor;

	// The cursor and if it is visible
	bool m_ShowCursor;

	// If the cursor is enable, the time to show/hide the cursor and the cursor state
	bool m_CursorEnable;
	bool m_CursorState;
	float m_CursorStateChangeTime;

	// The cursor position (sempre aponta para uma string à frente de onde está)
	unsigned int m_CursorPosition;

	// The frame token (track the frame changed event)
	UIFrameToken m_FrameToken;
};