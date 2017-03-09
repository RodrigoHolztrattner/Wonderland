////////////////////////////////////////////////////////////////////////////////
// Filename: FluxInputDispatcher.cpp
////////////////////////////////////////////////////////////////////////////////
#include "InputDispatcher.h"

HookGui::InputDispatcher::InputDispatcher()
{
	// Set the initial data
    // ...
}

HookGui::InputDispatcher::~InputDispatcher()
{
}

void HookGui::InputDispatcher::StartIterator()
{
    // Reset the iterator position
    m_Iterator = 0;
}

HookGui::InputCommand HookGui::InputDispatcher::GetIteratorInput()
{
    // Return the input at the iterator position
    return m_InputArray[m_Iterator];
}

void HookGui::InputDispatcher::ConsumeIteratorInput()
{
    // Remove the current input
    m_InputArray.erase(m_InputArray.begin() + m_Iterator);
    
    // Subtract one from the iterator
    m_Iterator--;
}

void HookGui::InputDispatcher::IteratorIncrement()
{
    // Increment the iterator
    m_Iterator++;
}

bool HookGui::InputDispatcher::IteratorIsValid()
{
    return m_Iterator < m_InputArray.size();
}
