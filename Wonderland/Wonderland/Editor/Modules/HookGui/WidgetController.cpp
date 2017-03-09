////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWidgetController.cpp
////////////////////////////////////////////////////////////////////////////////
#include "WidgetController.h"

HookGui::WidgetController::WidgetController()
{
	// Set the initial data
    m_RootView = nullptr;
    m_IsHidden = false;
    m_CanInteract = true;
}

HookGui::WidgetController::~WidgetController()
{
}

bool HookGui::WidgetController::EvaluateInput(InputCommand _inputCommand)
{
    // If we cant interact, return false
    if(!m_CanInteract)
    {
        return false;
    }
    
    //
    // ...
    
    return false;
}
