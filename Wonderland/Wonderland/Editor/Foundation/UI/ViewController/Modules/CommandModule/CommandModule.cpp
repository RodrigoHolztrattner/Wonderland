////////////////////////////////////////////////////////////////////////////////
// Filename: CommandModule.cpp
////////////////////////////////////////////////////////////////////////////////
#include "CommandModule.h"
#include "..\..\..\Widgets\UIBase.h"
#include <iostream>

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\..\Components\Tree\UITreeComponent.h"
#include "..\..\..\Components\State\UIStateComponent.h"
#include "..\..\..\Components\Frame\UIFrameComponent.h"
#include "..\..\..\Components\Command\UICommandComponent.h"

CommandModule::CommandModule()
{
	// Set the initial data
	m_FocusWidget = nullptr;
	m_HoverWidget = nullptr;
}

CommandModule::CommandModule(const CommandModule& other)
{
}

CommandModule::~CommandModule()
{
}

bool CommandModule::Initialize()
{
	return true;
}

void CommandModule::Update(UIBase* _widget, float _time, int _mouseX, int _mouseY)
{
	// If we have a wiget on focus, update it
	if (m_FocusWidget != nullptr)
	{
		// Get the command component
		UICommandComponent* commandComponent = m_FocusWidget->FindComponent<UICommandComponent>();

		// Send the update command
		commandComponent->EvaluateCommand(CommandType(CommandActor::System, CommandAction::Update, _mouseX, _mouseY));
	}
}

void CommandModule::RegisterCommand(CommandType _command)
{
	// Insert this command to the command array
	m_CommandArray.Add(_command);
}

void CommandModule::ProcessCommands(UIBase* _mainWidget, int _mouseX, int _mouseY)
{
	// Check if the main widget is valid
	if (_mainWidget == nullptr)
	{
		return;
	}

	// Process the hover command
	ProcessMouseCommand(_mainWidget, CommandType(CommandActor::System, CommandAction::Hover, _mouseX, _mouseY));

	// Send the hover clear for the hover widget
	if (m_HoverWidget != nullptr)
	{
		// Get the frame component from our hover object
		UIFrameComponent* frameComponent = m_HoverWidget->FindComponent<UIFrameComponent>();

		// Check if we are inside this widget
		if (!frameComponent->PointIsInsideFrame(Vector2(_mouseX, _mouseY)))
		{
			// Get the command component
			UICommandComponent* commandComponent = m_HoverWidget->FindComponent<UICommandComponent>();

			// Send a hover clear message
			commandComponent->EvaluateCommand(CommandType(CommandActor::System, CommandAction::HoverClear, _mouseX, _mouseY));

			// Set a null ptr
			m_HoverWidget = nullptr;
		}
	}

	// While the command array is not empty
	while (m_CommandArray.Size() != 0)
	{
		// Get the bottom command
		CommandType command = m_CommandArray.Get(0);
		m_CommandArray.Remove(0);

		// Check if we have any triggers
		// ...

		// Check if the command is a mouse one
		if (command.actor == CommandActor::Mouse)
		{
			// Call the process mouse command for the main widget
			ProcessMouseCommand(_mainWidget, command);
		}

		// Esc key
		if (command.actor == CommandActor::Keyboard && command.firstParam == 256)
		{
			exit(0);
		}

		// Check for the keyboard command
		if (command.actor == CommandActor::Keyboard && m_FocusWidget != nullptr)
		{
			// Process the keyboard command for the focus widget
			ProcessKeyboardCommand(m_FocusWidget, command);
		}
		
	}
}

bool CommandModule::ProcessMouseCommand(UIBase* _widget, CommandType _command)
{
	// Get the entity dependency components
	UIStateComponent* entityState = _widget->FindComponent<UIStateComponent>();
	UIFrameComponent* entityFrame = _widget->FindComponent<UIFrameComponent>();
	UITreeComponent* entityTree = _widget->FindComponent<UITreeComponent>();
	UICommandComponent* entityCommand = _widget->FindComponent<UICommandComponent>();

	// Set the mouse position
	int mouseX = _command.firstParam;
	int mouseY = _command.secondParam;

	// Check if the entity is visible
	if (!entityState->IsVisible())
	{
		return false;
	}

	// Check if we are inside this widget
	if (!entityFrame->PointIsInsideFrame(Vector2(mouseX, mouseY)))
	{
		return false;
	}

	// For each tree child
	for (int i = 0; i < entityTree->GetChildArraySize(); i++)
	{
		// Get the child entity tree component
		UITreeComponent* childTreeComponent = entityTree->GetChildByIndex(i);

		// Get the child widget
		UIBase* childWidget = (UIBase*)childTreeComponent->GetEntityOwner();

		// Call the function for the child command component and check the result
		bool result = ProcessMouseCommand(childWidget, _command);
		if (result)
		{
			return true;
		}
	}

	// If the action != hover
	if (_command.action != CommandAction::Hover)
	{
		// Move this widget to the top
		entityTree->MoveToTop();
	}

	// Check if this widget can receive commands
	if (!entityState->CanReceiveCommands())
	{
		return false;
	}

	// If the action != hover
	if (_command.action != CommandAction::Hover)
	{
		// If the current focus widget is valid
		if (m_FocusWidget != nullptr)
		{
			// Get the command component
			UICommandComponent* commandComponent = m_FocusWidget->FindComponent<UICommandComponent>();

			// Send a lost focus message
			CommandType systemCommand = CommandType(CommandActor::System, CommandAction::LostFocus, 0, 0, _widget);
			commandComponent->EvaluateCommand(systemCommand);
		}

		// If the new widget is valid
		if (_widget != nullptr)
		{
			// Set the new focus widget
			m_FocusWidget = _widget;

			// Get the command component
			UICommandComponent* commandComponent = m_FocusWidget->FindComponent<UICommandComponent>();

			// Send a on focus message
			CommandType systemCommand = CommandType(CommandActor::System, CommandAction::OnFocus, 0, 0);
			commandComponent->EvaluateCommand(systemCommand); 
		}
		
	}
	// Hover
	else
	{
		// If our hover object exist
		if (m_HoverWidget != nullptr && m_HoverWidget != _widget)
		{
			// Get the command component
			UICommandComponent* commandComponent = m_HoverWidget->FindComponent<UICommandComponent>();

			// Send a hover clear message
			commandComponent->EvaluateCommand(CommandType(CommandActor::System, CommandAction::HoverClear, 0, 0, _widget));
		}

		// Set the new hover widget
		m_HoverWidget = _widget;
	}
		
	// Ok, pass the command to this widget
	if (entityCommand->EvaluateCommand(_command))
	{
		return true;
	}

	return false;
}

bool CommandModule::ProcessKeyboardCommand(UIBase* _widget, CommandType _command)
{
	// Check if the widget is valid
	if (_widget == nullptr)
	{
		return false;
	}

	/*
	// Check if this widget is valid
	if (!UIBase::IsValid(_widget))
	{
	return false;
	}

	*/

	// Get the entity dependency components
	UIStateComponent* entityState = _widget->FindComponent<UIStateComponent>();

	// Check if the entity is visible
	if (!entityState->IsVisible())
	{
		return false;
	}

	// Check if this widget can receive commands
	if (!entityState->CanReceiveCommands())
	{
		return false;
	}

	// Process the command for the current widget
	_widget->ProcessCommand(&_command);

	return true;
}

void CommandModule::Shutdown()
{

}

/*
void CommandModule::ValidateCommandKey(CommandType* _command)
{
	// Shift key check
	if (_command->firstParam == 340)
	{
		// Press / release
		if (_command->action == CommandAction::Press)
		{
			m_IsShiftPressed = true;
		}
		else if (_command->action == CommandAction::Release)
		{
			m_IsShiftPressed = false;
		}
	}

	// Ctrl key check
	if (_command->firstParam == 341)
	{
		// Press / release
		if (_command->action == CommandAction::Press)
		{
			m_IsCtrlPressed = true;
		}
		else if (_command->action == CommandAction::Release)
		{
			m_IsCtrlPressed = false;
		}
	}

	// Alt key check
	if (_command->firstParam == 342)
	{
		// Press / release
		if (_command->action == CommandAction::Press)
		{
			m_IsAltPressed = true;
		}
		else if (_command->action == CommandAction::Release)
		{
			m_IsAltPressed = false;
		}
	}

	// Reset the control key value
	_command->controlKey = CommandControlKey::None;

	// Adjust the command message
	if (m_IsShiftPressed)
	{
		_command->controlKey = (CommandControlKey)(_command->controlKey + CommandControlKey::Shift);
	}
	if (m_IsCtrlPressed)
	{
		_command->controlKey = (CommandControlKey)(_command->controlKey + CommandControlKey::Ctrl);
	}
	if (m_IsAltPressed)
	{
		_command->controlKey = (CommandControlKey)(_command->controlKey + CommandControlKey::Alt);
	}
}
*/