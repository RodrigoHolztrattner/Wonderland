////////////////////////////////////////////////////////////////////////////////
// Filename: UITextBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\View\View.h"
#include "UIFont.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

// We know the command type
struct CommandType;

////////////
// STRUCT //
////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UITextBase
////////////////////////////////////////////////////////////////////////////////
class UITextBase : public View
{
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

		// A reference to the glyph data
		UIFont::GlyphType* glyphData;
	};

public:
	UITextBase(View* _parent, UIFont* _fontType);
	~UITextBase();

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

	// Return the font type
	UIFont* GetFontType()
	{
		return m_Font;
	}

protected:

	// Rebuild callback
	virtual void RebuildCallback()
	{
		// Update the text frame
		UpdateTextFrame();
	}

private:

	// Insert a new char into the current text string
	void InsetNewChar(char _char);

	// Update the text frame
	void UpdateTextFrame();

	// Find the string position we are at
	int MapMousePositionToString(Vector2 _mousePosition);

	// Adjust the cursor if it is out of bounds
	// void AdjustCursor();

	////////////
	// SHADER //
public: ////////

	// Render this UITextBase
	virtual void Render();

	// Set the text
	void SetText(std::string _text);
	
	// Return the text
	std::vector<UIChar> GetText() { return m_Text; }

private:

	// The font object
	UIFont* m_Font;

	// The text
	std::vector<UIChar> m_Text;

	// The cursor position (sempre aponta para uma string à frente de onde está)
	unsigned int m_CursorPosition;
};
