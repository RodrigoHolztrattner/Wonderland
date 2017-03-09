////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWindow.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Window.h"

HookGui::Window::Window()
{
	// Set the initial data
    m_IsHidden = false;
    m_CanInteract = true;
}

HookGui::Window::~Window()
{
}

bool HookGui::Window::Initialize()
{
    return true;
}

void HookGui::Window::Update(float _elapsedTime)
{
    // If we can interact
    if(m_CanInteract)
    {
        // Process the input for all child widget controllers
        ProcessInput();
    }
}

void HookGui::Window::Shutdown()
{
    
}

HookGui::InputDispatcher* HookGui::Window::GetInputDispatcher()
{
    return &m_InputDispatcher;
}

void HookGui::Window::ProcessInput()
{
    // For each input
    for(m_InputDispatcher.StartIterator(); m_InputDispatcher.IteratorIsValid(); m_InputDispatcher.IteratorIncrement())
    {
        // Get the current input
        HookGui::InputCommand input = m_InputDispatcher.GetIteratorInput();
        
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
