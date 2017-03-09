////////////////////////////////////////////////////////////////////////////////
// Filename: UITextComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UITextComponent.h"

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\Frame\UIFrameComponent.h"
#include "..\..\State\UIStateComponent.h"

#include "UIFontShader.h"

#include "..\..\..\..\Context\Context.h"
#include "..\..\..\ViewController\Modules\CommandModule\CommandType.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UITextComponent::UITextComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_CursorEnable = true;
	m_ShowCursor = false;
	m_CursorState = true;
	m_TextColor = Vector4(1, 1, 1, 1);
	m_CursorStateChangeTime = 1;
}

UITextComponent::UITextComponent(const UITextComponent& other) : ECS_Component(other)
{
}

UITextComponent::~UITextComponent()
{
}

///////////////
// MODIFIERS //
///////////////

bool UITextComponent::SetFontType(char* _fontName, unsigned int _fontSize)
{
	return m_String.Initialize(_fontName, _fontSize);
}

void UITextComponent::SetFormatation(UIString::HorizontalFormatation _horizontal, UIString::VerticalFormatation _vertical)
{
	m_String.SetFormatation(_horizontal, _vertical);
}

void UITextComponent::SetPadAmout(Vector2 _padAmount)
{
	m_String.SetPadAmout(_padAmount);
}

void UITextComponent::SetText(std::string _text)
{
	m_String.SetText(_text);
}

void UITextComponent::SetTextColor(Vector4 _color)
{
	m_TextColor = _color;
}

Vector4 UITextComponent::GetTextColor()
{
	return m_TextColor;
}

std::vector<UIChar> UITextComponent::GetText()
{
	return m_String.GetText();
}

UIFont* UITextComponent::GetFont()
{
	return m_String.GetFont();
}

Vector2 UITextComponent::GetMaxDimensionSize()
{
	return m_String.GetMaxDimensionSize();
}

void UITextComponent::ProcessCommand(CommandType* _command)
{
	// Get the parent entity
	ECS_Entity* parentEntity = GetEntityOwner();

	// Get the state component from our entity owner
	UIStateComponent* stateComponent = parentEntity->FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = parentEntity->FindComponent<UIFrameComponent>();

	// Check if the cursor is enable
	if (!m_CursorEnable)
	{
		return;
	}

	// On focus command
	if (_command->actor == CommandActor::System && _command->action == CommandAction::OnFocus)
	{
		// Show the cursor
		m_ShowCursor = true;
		m_CursorState = true;
	}

	// Lost focus command
	if (_command->actor == CommandActor::System && _command->action == CommandAction::LostFocus)
	{
		// hide the cursor
		m_ShowCursor = false;
	}

	// Mouse command
	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press)
	{
		// Map the cursor position to the current mouse location
		m_String.CursorReposition(frameComponent->GetFramePosition(), frameComponent->GetFrameSize(), Vector2(_command->firstParam, _command->secondParam));	
	}

	// Key command
	if (_command->actor == CommandActor::Keyboard && (_command->action == CommandAction::Press || _command->action == CommandAction::Hold))
	{
		// Backspace check
		if (_command->firstParam == 259)
		{
			// Remove the char at our cursor position
			m_String.RemoveCursorChar();
		}
		else
		{
			// Insert the new char
			m_String.InsertNewChar(_command->firstParam);
		}
	}

	return ;
}

#include <iostream>

bool UITextComponent::IsCursorActive()
{
	return m_CursorEnable && m_ShowCursor && m_CursorState;
}


UIChar UITextComponent::GetCursorData()
{
	return m_String.GetCursorData();
}

/////////////
// VIRTUAL //
/////////////

void UITextComponent::Update(unsigned int _updateId, float _timeElapsed)
{
	// Get the parent entity
	ECS_Entity* parentEntity = GetEntityOwner();

	// Get the state component from our entity owner
	UIStateComponent* stateComponent = parentEntity->FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = parentEntity->FindComponent<UIFrameComponent>();

	// Update the string if it needs
	m_String.Update(frameComponent->GetFramePosition(), frameComponent->GetFrameSize(), !frameComponent->GetFrameToken().IsEqual(m_FrameToken));

	// Update the cursor state
	if (m_CursorStateChangeTime <= 0)
	{
		// Reset the timer
		m_CursorStateChangeTime = 1;

		// Change the state
		m_CursorState = !m_CursorState;
	}

	// Compare the update if with the render id
	if (stateComponent->GetRenderingID() == _updateId)
	{
		// Render this entity
		UIFontShader::GetInstance()->AddObject(this);
	}

	// Subtract the time for the cursor
	m_CursorStateChangeTime -= _timeElapsed;
}

void UITextComponent::Clear()
{

}