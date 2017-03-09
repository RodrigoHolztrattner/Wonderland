////////////////////////////////////////////////////////////////////////////////
// Filename: UIString.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIString.h"

#include "..\..\..\..\Context\Context.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIString::UIString()
{
	// Set the initial data
	m_CursorPosition = 0;
	m_PadAmount = Vector2(5, 5);
	m_HorizontalFormatation = HorizontalFormatation::Centralized;
	m_VerticalFormatation = VerticalFormatation::Centralized;
	m_NeedUpdate = true;
	m_Font = nullptr;
}

UIString::UIString(const UIString& other)
{
}

UIString::~UIString()
{
}

bool UIString::Initialize(char* _fontName, unsigned int _fontSize)
{
	// Check if we should delete the old font
	if (m_Font != nullptr)
	{
		delete m_Font;
		m_Font = nullptr;
	}

	// Create the new font
	m_Font = new UIFont();
	m_Font->Initialize(_fontName, _fontSize); // "Roboto-Regular.ttf", 16
	m_NeedUpdate = true;

	return true;
}

void UIString::SetFormatation(HorizontalFormatation _horizontal, VerticalFormatation _vertical)
{
	// Set the data
	m_HorizontalFormatation = _horizontal;
	m_VerticalFormatation = _vertical;
	m_NeedUpdate = true;
}

void UIString::SetPadAmout(Vector2 _padAmount)
{
	// Set the pad amount
	m_PadAmount = _padAmount;
	m_NeedUpdate = true;
}

///////////////
// MODIFIERS //
///////////////

void UIString::SetText(std::string _text)
{
	// Clear the text array
	m_Text.clear();
	m_CursorPosition = 0;

	// For each char
	for (int i = 0; i < _text.size(); i++)
	{
		// Insert the new char
		InsertNewChar(_text[i]);
		m_CursorPosition++;
	}

	// Need update to true
	m_NeedUpdate = true;
}

std::vector<UIChar> UIString::GetText()
{
	return m_Text;
}

UIFont* UIString::GetFont()
{
	return m_Font;
}

void UIString::Update(Vector2 _framePosition, Vector2 _frameSize, bool _force)
{
	// Check if we need to update
	if (m_NeedUpdate || _force)
	{
		// Update the text
		UpdateTextFrame(_framePosition, _frameSize);
	}
}

int UIString::MapMousePositionToString(Vector2 _mousePosition)
{
	// For each string
	for (int i = 0; i < m_Text.size(); i++)
	{
		// Set how much we are inside the width and height sizes
		float widthPercent = (_mousePosition.x - m_Text[i].absolutePosition.x) / (float)m_Text[i].absoluteSize.x;
		float heightPercent = (_mousePosition.y - m_Text[i].absolutePosition.y) / (float)m_Text[i].absoluteSize.y;

		// Check if the mouse position is inside this glyph
		if (widthPercent >= 1 || widthPercent < 0 || heightPercent >= 1 || heightPercent < 0)
		{
			continue;
		}

		// Adjust the index
		if (widthPercent > 0.5)
		{
			i++;
		}

		return i;
	}

	return -1;
}

void UIString::InsertNewChar(char _char)
{
	UIChar newChar;

	// Check if the cursor position is valid
	if (m_CursorPosition < 0 || m_CursorPosition > m_Text.size())
	{
		m_CursorPosition = m_Text.size();
	}

	// Prepare the new char data
	newChar.position = Vector2(0, 0);
	newChar.size = Vector2(0, 0);
	newChar.originalChar = _char;
	newChar.glyphData = m_Font->GetGlyphData(_char);
	newChar.absoluteSize.width = newChar.glyphData->size.width;
	newChar.absoluteSize.height = newChar.glyphData->size.height;
	newChar.advanceAmount = newChar.glyphData->advance.x;

	// Add the new char to the array
	m_Text.insert(m_Text.begin() + m_CursorPosition, newChar);

	// Increment the cursor position
	m_CursorPosition++;

	// Need update to true
	m_NeedUpdate = true;
}

void UIString::RemoveCursorChar()
{
	// Check if the cursor is in bounds
	m_CursorPosition = Clamp(m_CursorPosition, 0, m_Text.size());

	// Check if we can remove
	if (!m_CursorPosition)
	{
		return;
	}

	// Remove the char close to our cursor position
	m_Text.erase(m_Text.begin() + m_CursorPosition - 1);

	// Increment the cursor position
	m_CursorPosition--;

	// Need update to true
	m_NeedUpdate = true;
}

Vector2 UIString::GetMaxDimensionSize()
{
	return m_MaxDimension;
}

void UIString::UpdateTextFrame(Vector2 _framePosition, Vector2 _frameSize)
{
	// Our current frame position and size
	Vector2 framePosition = _framePosition;
	Vector2 frameSize = _frameSize;

	// Zero the max dimension
	m_MaxDimension = Vector2(0, 0);

	// Set our working area
	framePosition.x += m_PadAmount.x;
	framePosition.y += m_PadAmount.y;
	frameSize.width -= m_PadAmount.x * 2;
	frameSize.height -= m_PadAmount.y * 2;

	// Get the screen width and height
	int ScreenWidth = Context::GetInstance()->GetScreenWidth();
	int ScreenHeight = Context::GetInstance()->GetScreenHeight();
	
	// Set the height adjustment
	float heightAdjustment = 0; //  (frameSize.height - m_Font->GetFontSize()) / 2.0f; // +3;

	// Set the width and height pad
	int widthPad = m_Font->GetFontSize() / 16;
	int heightPad = m_Font->GetFontSize() / 3 + m_Font->GetFontSize();

	// Set our control variables
	int currentLine = 0;
	int lineStartIndex = 0;
	int currentLineWidth = 0;
	int currentHeight = m_Font->GetFontSize();

	// For each glyph
	for (int i = 0; i < m_Text.size(); i++)
	{
		// Get the current glyph data
		UIFont::GlyphType* glyphData = m_Text[i].glyphData;

		// Check if we need to change the line
		if (currentLineWidth + glyphData->advance.x >= frameSize.width || m_Text[i].originalChar == 13)
		{
			// Increment the current line
			currentLine++;

			// Format the glyphs from the lineStartIndex to the current index (i)
			FormatHorizontally(framePosition, frameSize, lineStartIndex, i, currentLineWidth);

			// Zero the current line width (new line, new width)
			currentLineWidth = 0;

			// Remove this char from the text array
			// m_Text.erase(m_Text.begin() + i);

			// Increment the current height
			currentHeight += heightPad;

			// Set the new line start index
			lineStartIndex = i;
		}

		// Set the glyph absolute position
		m_Text[i].absolutePosition.x = framePosition.x + currentLineWidth + glyphData->position.x;
		m_Text[i].absolutePosition.y = framePosition.y + frameSize.height - glyphData->position.y - heightAdjustment + currentLine * heightPad;

		// Set the line index and pad
		m_Text[i].lineIndex = currentLine;
		m_Text[i].linePad = framePosition.y + frameSize.height - heightAdjustment + currentLine * heightPad;

		// Increment the current line width
		currentLineWidth += m_Text[i].advanceAmount;
	}

	// If we are inside the line number zero or our currentLineWidth is bigger then zero, we need to force the horizontal format
	if (currentLine == 0 || currentLineWidth > 0)
	{
		// Force this!
		// Format the glyphs from the lineStartIndex to the current index (i)
		FormatHorizontally(framePosition, frameSize, lineStartIndex, m_Text.size(), currentLineWidth);
	}

	// Format the text vertically
	FormatVertically(framePosition, frameSize, currentHeight, heightPad);

	// For each glyph: Set the relative position and size, also calculate the screen transformation
	for (int i = 0; i < m_Text.size(); i++)
	{
		// Set the glyph position and size
		m_Text[i].position = m_Text[i].absolutePosition.DivideBy(ScreenWidth, ScreenHeight);
		m_Text[i].size = m_Text[i].absoluteSize.DivideBy(ScreenWidth, ScreenHeight);

		// Convert the position and the size to screen coordinates
		m_Text[i].position = Vector3::TransformToScreenPosition(m_Text[i].position, m_Text[i].size);
		m_Text[i].size = Vector3::TransformToScreenSize(m_Text[i].size);
	}

	// Update the cursor
	UpdateCursor(_framePosition, _frameSize);

	// No need for update
	m_NeedUpdate = false;
}

void UIString::UpdateCursor(Vector2 _framePosition, Vector2 _frameSize)
{
	// Check if the cursor is in bounds
	m_CursorPosition = Clamp(m_CursorPosition, 0, m_Text.size());
	
	// Our current frame position and size
	Vector2 framePosition = _framePosition;
	Vector2 frameSize = _frameSize;

	// Set the screen width and height
	int ScreenWidth = Context::GetInstance()->GetScreenWidth();
	int ScreenHeight = Context::GetInstance()->GetScreenHeight();

	// Set the med pos
	float medPos = (frameSize.height - m_Font->GetFontSize()) / 2.0f;

	// Set the base data
	char cursorChar = '|';
	m_Cursor.originalChar = cursorChar;
	m_Cursor.glyphData = m_Font->GetGlyphData(cursorChar);
	m_Cursor.size = Vector2(m_Cursor.glyphData->size.x / ScreenWidth, m_Cursor.glyphData->size.y / ScreenHeight);
	
	// Check we are at the position 0
	if (m_CursorPosition == 0)
	{
		// Set the cursor position
		m_Cursor.position = Vector2((framePosition.x) / ScreenWidth, (framePosition.y + frameSize.y - m_Cursor.glyphData->position.y - medPos) / ScreenHeight);
		m_Cursor.position = Vector3::TransformToScreenPosition(m_Cursor.position, m_Cursor.size);
	}
	else
	{
		// Set the cursor position
		m_Cursor.position = m_Text[m_CursorPosition-1].position;
		// m_Cursor.position.y = (m_Text[m_CursorPosition - 1].linePad) / ScreenHeight;
		m_Cursor.position.x += m_Text[m_CursorPosition - 1].size.x;
	}

	m_Cursor.size.x *= 1.5f;
	m_Cursor.size.y *= 2;
	//m_Cursor.size = Vector3::TransformToScreenSize(m_Cursor.size);

	// std::cout << "Cursor pos: x = " << m_Cursor.position.x << " | y = " << m_Cursor.position.y << std::endl;
}

////////////
// CURSOR //
////////////

void UIString::CursorReposition(Vector2 _framePosition, Vector2 _frameSize, Vector2 _location)
{
	// Set the cursor index position
	int newCursorPos = MapMousePositionToString(_location);
	if (newCursorPos != -1)
	{
		// Update the cursor pos
		m_CursorPosition = newCursorPos;

		// Update the cursor
		UpdateCursor(_framePosition, _frameSize);
	}
}

UIChar UIString::GetCursorData()
{
	return m_Cursor;
}

///////////////
// FORMATING //
///////////////

void UIString::FormatHorizontally(Vector2 _framePosition, Vector2 _frameSize, unsigned int _fromIndex, unsigned int _toIndex, unsigned int _widthAmount)
{
	// The width pad amount
	unsigned int widthPad = 0;

	// Check the horizontal formatation
	switch (m_HorizontalFormatation)
	{
		// Right
		case UIString::HorizontalFormatation::RightAlign:
		{
			// Set the width pad
			widthPad = _frameSize.width - _widthAmount;

			break;
		}
		// Left
		case UIString::HorizontalFormatation::LeftAlign:
		{
			// Set the width pad
			widthPad = 0;

			break;
		}
		// Center
		case UIString::HorizontalFormatation::Centralized:
		{
			// Set the width pad
			widthPad = (_frameSize.width - _widthAmount) / 2.0f;

			break;
		}
	}

	// For each glyph
	for (int i = _fromIndex; i < _toIndex; i++)
	{
		// Set the glyph absolute position
		m_Text[i].absolutePosition.x += widthPad;
	}

	// Set the max dimension (width)
	if (_widthAmount > m_MaxDimension.width) m_MaxDimension.width = _widthAmount;
}

void UIString::FormatVertically(Vector2 _framePosition, Vector2 _frameSize, unsigned int _heightAmount, unsigned int _heightIncrement)
{
	// The height pad amount
	int heightPad = 0;

	// Check the horizontal formatation
	switch (m_VerticalFormatation)
	{
		// Top
		case UIString::VerticalFormatation::TopAlign:
		{
			// Set the width pad
			heightPad = -(_frameSize.height - m_Font->GetFontSize());

			break;
		}
		// Bottom
		case UIString::VerticalFormatation::BottomAlign:
		{
			// Set the width pad
			heightPad = -(_heightAmount - m_Font->GetFontSize());
		
			break;
		}
		// Centralized
		case UIString::VerticalFormatation::Centralized:
		{
			// Set the width pad
			heightPad = -((_frameSize.height - _heightAmount) / 2.0f) - (_heightAmount - m_Font->GetFontSize());

			break;
		}
	}

	// For each glyph
	for (int i = 0; i < m_Text.size(); i++)
	{
		// Set the glyph absolute position
		m_Text[i].absolutePosition.y += heightPad;
	}

	// Set the max dimension (height)
	if (_heightAmount > m_MaxDimension.height) m_MaxDimension.height = _heightAmount;
}