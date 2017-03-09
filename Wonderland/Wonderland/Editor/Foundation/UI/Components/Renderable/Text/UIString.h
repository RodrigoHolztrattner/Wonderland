////////////////////////////////////////////////////////////////////////////////
// Filename: UIString.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"
#include "UIFont.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

// The UI char type
struct UIChar
{
	// The original char
	char originalChar;

	// The position and size
	Vector2 position;
	Vector2 size;

	// The absolute position and size
	Vector2 absolutePosition;
	Vector2 absoluteSize;

	// The advance amount
	unsigned int advanceAmount;

	// The line index and pad
	unsigned int lineIndex;
	unsigned int linePad;

	// A reference to the glyph data
	UIFont::GlyphType* glyphData;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: UIString
////////////////////////////////////////////////////////////////////////////////
class UIString
{
public:

	// The horizontal string formatation
	enum class HorizontalFormatation
	{
		RightAlign,
		LeftAlign,
		Centralized
	};

	// The vertical string formatation
	enum class VerticalFormatation
	{
		TopAlign,
		BottomAlign,
		Centralized
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	UIString();
	UIString(const UIString&);
	~UIString();

	// Initialize the UIString object
	bool Initialize(char* _fontName, unsigned int _fontSize);

	// Set the formatation
	void SetFormatation(HorizontalFormatation _horizontal, VerticalFormatation _vertical);

	// Set the pad amount
	void SetPadAmout(Vector2 _padAmount);

private:

///////////////
// MODIFIERS //
public: ///////

	// Update
	void Update(Vector2 _framePosition, Vector2 _frameSize, bool _force = false);

	// Set the text
	void SetText(std::string _text);

	// Return the text
	std::vector<UIChar> GetText();

	// Return the font type
	UIFont* GetFont();

	// Insert a new char into the current text string
	void InsertNewChar(char _char);

	// Remove the char at our cursor position
	void RemoveCursorChar();

	// Update the text frame
	void UpdateTextFrame(Vector2 _framePosition, Vector2 _frameSize);

	// Return the max size used by the text
	Vector2 GetMaxDimensionSize();

private:

	// Find the string position we are at
	int MapMousePositionToString(Vector2 _mousePosition);

////////////
// CURSOR //
public: ////

	// Cursor reposition
	void CursorReposition(Vector2 _framePosition, Vector2 _frameSize, Vector2 _location);

	// Return the cursor data
	UIChar GetCursorData();

private:

	// Update the cursor
	void UpdateCursor(Vector2 _framePosition, Vector2 _frameSize);

///////////////
// FORMATING //
private: //////

	// Format the text horizontally
	void FormatHorizontally(Vector2 _framePosition, Vector2 _frameSize, unsigned int _fromIndex, unsigned int _toIndex, unsigned int _widthAmount);

	// Format the text horizontally
	void FormatVertically(Vector2 _framePosition, Vector2 _frameSize, unsigned int _heightAmount, unsigned _heightIncrement);

///////////////
// VARIABLES //
private: //////

	// The font, text and cursor data
	UIFont* m_Font;
	std::vector<UIChar> m_Text;
	UIChar m_Cursor;

	// The pad amount
	Vector2 m_PadAmount;

	// The cursor position (sempre aponta para uma string à frente de onde está)
	unsigned int m_CursorPosition;

	// The string formatation
	HorizontalFormatation m_HorizontalFormatation;
	VerticalFormatation m_VerticalFormatation;

	// If we need to update the glyph position
	bool m_NeedUpdate;

	// The max dimension used by the text
	Vector2 m_MaxDimension;
};