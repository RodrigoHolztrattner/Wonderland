////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWidgetController.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGInputController.h"

HookGui::HGInputController::HGInputController()
{
	// Set the initial data
    // ...
}

HookGui::HGInputController::~HGInputController()
{
}

void HookGui::HGInputController::ProcessInputCommands(HGWidget* _mainWidget, HGInputDispatcher& _inputDispatcher)
{
	// Lets start processing the input
	_inputDispatcher.StartIterator();
	
	// Until our iterator is valid
	while (_inputDispatcher.IteratorIsValid())
	{
		// Get the input
		HGInputCommand input = _inputDispatcher.GetIteratorInput();

		// If we used this input
		bool inputConsumed = false;

		// Get the input type
		switch (input.inputAuthor)
		{
			case HGInputAuthor::System:
			{
				break;
			}

			case HGInputAuthor::Mouse:
			{
				// Process the mouse input from the main widget
				if (ProcessMouseInput(_mainWidget, input))
				{
					// Set that we used the input
					inputConsumed = true;
				}

				break;
			}

			case HGInputAuthor::Keyboard:
			{
				break;
			}
		}

		// If we used the input, remove if from the dispatcher
		if (inputConsumed || true)
		{
			// Remove it
			_inputDispatcher.ConsumeIteratorInput();
		}
	}
}

bool HookGui::HGInputController::ProcessMouseInput(HGWidget* _currentWidget, HGInputCommand& _input)
{
	// Get the input location
	uint32_t x = _input.upperParam;
	uint32_t y = _input.lowerParam;

	// Check if the mouse input was inside this widget area
	if (!_currentWidget->PointIsInside(x, y))
	{
		return false;
	}

	// Check if we can interact or if we are hidden
	if (!_currentWidget->CanInteract() || _currentWidget->IsHidden())
	{
		return false;
	}

	// Check if any of this widget child can receive this input
	const std::vector<HGWidget*>& childArray = _currentWidget->GetChildArray();
	for (int i = 0; i < childArray.size(); i++)
	{
		// Check if this child uses this input
		if (ProcessMouseInput(childArray[i], _input))
		{
			return true;
		}
	}

	// Ok if we are here, the input is ours //

	// Check if this widget can receive inputs
	if (!_currentWidget->CanReceiveInput())
	{
		return false;
	}

	// Process the input for this widget
	if (!_currentWidget->EvaluateInput(_input))
	{
		return false;
	}

	return true;
}