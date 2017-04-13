////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWindow.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGWindow.h"

HookGui::HGWindow::HGWindow()
{
	// Set the initial data
    m_IsHidden = false;
    m_CanInteract = true;
}

HookGui::HGWindow::~HGWindow()
{
}

bool HookGui::HGWindow::Initialize()
{
    return true;
}

void HookGui::HGWindow::Update(float _elapsedTime)
{
    // If we can interact
    if(m_CanInteract)
    {
        // Process the input for all child widget controllers
        ProcessInput();
    }
}

void HookGui::HGWindow::Shutdown()
{
    
}

HookGui::HGInputDispatcher* HookGui::HGWindow::GetInputDispatcher()
{
    return &m_InputDispatcher;
}

void HookGui::HGWindow::ProcessInput()
{
    // For each input
    for(m_InputDispatcher.StartIterator(); m_InputDispatcher.IteratorIsValid(); m_InputDispatcher.IteratorIncrement())
    {
        // Get the current input
        HGInputCommand input = m_InputDispatcher.GetIteratorInput();
        
        // For each child widget controller
        for(auto child : m_WidgetControllers)
        {
            // Process the input
            if(child->EvaluateInput(input))
            {
                // Consume the input
                m_InputDispatcher.ConsumeIteratorInput();
                
                break;
            }
        }
    }
}
