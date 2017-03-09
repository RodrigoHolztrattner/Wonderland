////////////////////////////////////////////////////////////////////////////////
// Filename: UITextBase.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UITextBase.h"
#include "UIFontShader.h"
#include "..\..\Base\UIViewShader.h"

UITextBase::UITextBase(View* _parent, UIFont* _fontType) : View(_parent)
{
	// Set the font type
	m_Font = _fontType;

	// Set the initial data
	m_CursorPosition = 0;
}

UITextBase::~UITextBase()
{
}

bool UITextBase::ProcessCommand(CommandType* _command)
{
	// Mouse command
	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press)
	{
		// Map the cursor position to the current mouse location
		int stringPos = MapMousePositionToString(Vector2(_command->firstParam, _command->secondParam));
		if (stringPos != -1)
		{
			// Set the cursor position
			m_CursorPosition = stringPos;
		}
		else
		{
			// Set the last string position
			m_CursorPosition = m_Text.size();
		}
	}

	// Key command
	if (_command->actor == CommandActor::Keyboard && (_command->action == CommandAction::Press || _command->action == CommandAction::Hold))
	{
		// Backspace check
		if (_command->firstParam == 259)
		{
			// Check if the cursor at a valid position
			if (m_CursorPosition > m_Text.size() || m_CursorPosition == 0)
			{
				return true;
			}

			// Remove the last char
			m_Text.erase(m_Text.begin() + m_CursorPosition-1);
			m_CursorPosition--;
		}
		else
		{
			// Insert the new char
			InsetNewChar(_command->firstParam);
			m_CursorPosition++;
		}

		// Update the text frame
		UpdateTextFrame();
	}

	return true;
}

void UITextBase::Render()
{
	UIFontShader::GetInstance()->AddObject(this);
	UIViewShader::GetInstance()->AddObject(this);
}

/*
void UITextBase::AdjustCursor()
{
	// Check if the cursor at a valid position
	if (m_CursorPosition > m_Text.size() || m_CursorPosition == 0)
	{
		return;
	}
}
*/

int UITextBase::MapMousePositionToString(Vector2 _mousePosition)
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

void UITextBase::SetText(std::string _text)
{
	// Clear the text array
	m_Text.clear();
	m_CursorPosition = 0;

	// For each char
	for (int i = 0; i < _text.size(); i++)
	{
		// Insert the new char
		InsetNewChar(_text[i]);
		m_CursorPosition++;
	}

	// Update the text frame
	UpdateTextFrame();
}

void UITextBase::InsetNewChar(char _char)
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

	// Add the new char to the array
	m_Text.insert(m_Text.begin() + m_CursorPosition, newChar);
}

void UITextBase::UpdateTextFrame()
{
	/*
	int ScreenWidth = GetRootParent()->GetAbsoluteSize().x;
	int ScreenHeight = GetRootParent()->GetAbsoluteSize().y;
	
	int accPos = 0;

	for (int i = 0; i < m_Text.size(); i++)
	{
		// Check if this glyph is valid
		if (accPos + m_Text[i].glyphData->advance.x >= GetAbsoluteSize().x)
		{
			// Remove this char from the text array
			m_Text.erase(m_Text.begin() + i);

			// Ensure we ignore all other glyphs
			accPos = 9999;
			i--;
		}

		// Font size resolution
		float fontResolution = GetAbsoluteSize().y / m_Font->GetFontSize();
		
		// Set the position and the size
		m_Text[i].absolutePosition.x = GetAbsolutePosition().x + accPos;
		m_Text[i].absolutePosition.y = GetAbsolutePosition().y + GetAbsoluteSize().y - (m_Text[i].glyphData->position.y * fontResolution);
		//m_Text[i].absoluteSize.x = m_Text[i].glyphData->advance.x;
		//m_Text[i].absoluteSize.y = GetAbsoluteSize().y; // m_Text[i].glyphData->advance.y
		m_Text[i].absoluteSize.x = m_Text[i].glyphData->size.x * fontResolution;
		m_Text[i].absoluteSize.y = m_Text[i].glyphData->size.y * fontResolution;

		// Increment the acc
		accPos += m_Text[i].absoluteSize.x;

		// Transform the position and the size
		m_Text[i].position.x = m_Text[i].absolutePosition.x / (float)ScreenWidth;
		m_Text[i].position.y = m_Text[i].absolutePosition.y / (float)ScreenHeight;
		m_Text[i].size.x = m_Text[i].absoluteSize.x / (float)ScreenWidth;
		m_Text[i].size.y = m_Text[i].absoluteSize.y / (float)ScreenHeight;

		//
		//
		//

		// Convert the position and the size to screen coordinates
		m_Text[i].position = Vector3::TransformToScreenPosition(m_Text[i].position, m_Text[i].size);
		m_Text[i].size = Vector3::TransformToScreenSize(m_Text[i].size);
	}
	*/
}