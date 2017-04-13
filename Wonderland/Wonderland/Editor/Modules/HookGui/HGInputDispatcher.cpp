////////////////////////////////////////////////////////////////////////////////
// Filename: FluxInputDispatcher.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGInputDispatcher.h"

HookGui::HGInputDispatcher::HGInputDispatcher()
{
	// Set the initial data
    // ...
}

HookGui::HGInputDispatcher::~HGInputDispatcher()
{
}

void HookGui::HGInputDispatcher::StartIterator()
{
    // Reset the iterator position
    m_Iterator = 0;
}

HookGui::HGInputCommand HookGui::HGInputDispatcher::GetIteratorInput()
{
    // Return the input at the iterator position
    return m_InputArray[m_Iterator];
}

void HookGui::HGInputDispatcher::ConsumeIteratorInput()
{
    // Remove the current input
    m_InputArray.erase(m_InputArray.begin() + m_Iterator);
    
    // Subtract one from the iterator
    m_Iterator--;
}

void HookGui::HGInputDispatcher::IteratorIncrement()
{
    // Increment the iterator
    m_Iterator++;
}

bool HookGui::HGInputDispatcher::IteratorIsValid()
{
    return m_Iterator < m_InputArray.size();
}

void HookGui::HGInputDispatcher::ProcessKeyCallback(int key, int scancode, int action, int mods)
{
	// Prepare the new input command
	HGInputCommand newInput = {};
	newInput.inputAuthor = HGInputAuthor::Keyboard;
	newInput.inputEvent = HGInputCommand::MapActionFromGLFW(action);
	newInput.inputKey = HGInputKey::Keyboard;
	newInput.keyParam = key;
	newInput.upperParam = -1;
	newInput.lowerParam = -1;

	// Add the new input
	m_InputArray.push_back(newInput);
}

void HookGui::HGInputDispatcher::ProcessMouseCallback(int button, int action, int mods)
{
	// Get the cursor position
	double xpos, ypos;
	glfwGetCursorPos(windowReference, &xpos, &ypos);

	// Get the window size
	int width, height;
	glfwGetWindowSize(windowReference, &width, &height);

	// Prepare the new input command
	HGInputCommand newInput = {};
	newInput.inputAuthor = HGInputAuthor::Mouse;
	newInput.inputEvent = HGInputCommand::MapActionFromGLFW(action);
	newInput.inputKey = HGInputCommand::MapButtonFromGLFW(button);
	newInput.keyParam = -1;
	newInput.upperParam = xpos;
	newInput.lowerParam = ypos;

	// Add the new input
	m_InputArray.push_back(newInput);
}