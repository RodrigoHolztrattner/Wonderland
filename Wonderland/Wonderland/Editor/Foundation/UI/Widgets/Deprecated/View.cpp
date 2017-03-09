////////////////////////////////////////////////////////////////////////////////
// Filename: View.cpp
////////////////////////////////////////////////////////////////////////////////
#include "View.h"
#include "..\..\ViewController\Modules\CommandModule\CommandModule.h"
#include "..\..\Base\UIViewShader.h"

View::View(UIBase* _parent) : UIBase::UIBase(_parent)
{
}

View::~View()
{
}

bool View::ProcessCommand(CommandType* _command)
{

	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press)
	{
		// Set the mouse location
		Vector2 mouseLocation = Vector2(_command->firstParam, _command->secondParam);

		// Pick region
		float PickRegion = 10.0f;

		// Top
		if (abs(mouseLocation.y - GetFrame().position.y) < PickRegion)
		{
			m_MouseHoldType = MouseHoldType::Top;
		}
		// Right
		else if (abs(mouseLocation.x - (GetFrame().position.x + GetFrame().size.width)) < PickRegion)
		{
			m_MouseHoldType = MouseHoldType::Right;
		}
		// Bottom
		else if (abs(mouseLocation.y - (GetFrame().position.y + GetFrame().size.height)) < PickRegion)
		{
			m_MouseHoldType = MouseHoldType::Bottom;
		}
		// Left
		else if (abs(mouseLocation.x - GetFrame().position.x) < PickRegion)
		{
			m_MouseHoldType = MouseHoldType::Left;
		}
		// Center
		else
		{
			m_MouseHoldType = MouseHoldType::Center;
		}

		// Set the mouse offset
		m_MouseOffset.x = GetFrame().position.x - mouseLocation.x;
		m_MouseOffset.y = GetFrame().position.y - mouseLocation.y;

		// Set the mouse original location
		m_MouseOriginalLocation = mouseLocation;
		m_OriginalSize = GetFrame().size;
	}

	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Release)
	{
		m_MouseHoldType = MouseHoldType::None;
	}

	return true;
}

void View::Update(float _time)
{
	// Base update
	UIBase::Update(_time);
	
	// Get the mouse location
	double xpos, ypos;
	glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);

	// Get the current position and size
	Vector2 position = GetFrame().position;
	Vector2 size = GetFrame().size;

	// Top
	if (m_MouseHoldType == MouseHoldType::Top)
	{
		float difference = m_MouseOriginalLocation.y - ypos;
		size.height = m_OriginalSize.height + difference;
		position.y = ypos;
	}
	// Right
	if (m_MouseHoldType == MouseHoldType::Right)
	{
		float difference = xpos - m_MouseOriginalLocation.x;
		size.width = m_OriginalSize.width + difference;
	}
	// Bottom
	if (m_MouseHoldType == MouseHoldType::Bottom)
	{
		float difference = ypos - m_MouseOriginalLocation.y;
		size.height = m_OriginalSize.height + difference;
	}
	// Left
	if (m_MouseHoldType == MouseHoldType::Left)
	{
		float difference = m_MouseOriginalLocation.x - xpos;
		size.width = m_OriginalSize.width + difference;
		position.x = xpos;
	}
	// Center
	if (m_MouseHoldType == MouseHoldType::Center)
	{
		position.x = xpos + m_MouseOffset.x;
		position.y = ypos + m_MouseOffset.y;
	}

	// Set our frame
	SetFrame(UIFrame::WidgetFrame(position, size));
}

void View::Render()
{
	UIViewShader::GetInstance()->AddObject(this);
}