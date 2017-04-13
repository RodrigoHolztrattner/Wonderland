////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWidgetController.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGInputComponent.h"

HookGui::HGInputComponent::HGInputComponent()
{
	// Set the initial data
    m_RootView = nullptr;
    m_IsHidden = false;
    m_CanInteract = true;
}

HookGui::HGInputComponent::~HGInputComponent()
{
}

bool HookGui::HGInputComponent::EvaluateInput(HGInputCommand _inputCommand)
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
