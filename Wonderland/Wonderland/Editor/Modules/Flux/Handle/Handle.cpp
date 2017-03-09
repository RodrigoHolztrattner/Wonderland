////////////////////////////////////////////////////////////////////////////////
// Filename: Handle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Handle.h"

Flux::Handle::Handle()
{
	// Set the initial data
	m_State = State::Invalid;
	m_Value = 0;
}

Flux::Handle::~Handle()
{
}

void Flux::Handle::GenerateHandle()
{
	// Get the current global handle
	unsigned long currentHandle = GetCurrentGlobalHandle();

	// Set our handle and the state
	m_Value = currentHandle;
	m_State = State::Valid;

	// Increment the new global handle
	SetCurrentGlobalHandle(currentHandle + 1);
}

bool Flux::Handle::CompareHandle(Flux::Handle _handle)
{
	// Check both states
	if (m_State == State::Invalid || _handle.m_State == State::Invalid)
	{
		return false;
	}

	return true;
}

bool Flux::Handle::IsValid()
{
	return m_State == State::Valid;
}

////////////
// GLOBAL //
////////////

// Set the initial value for the global handle
unsigned long Flux::Handle::s_CurrentHandle = 0;

void Flux::Handle::SetCurrentGlobalHandle(unsigned long _currentHandle)
{ 
	s_CurrentHandle = _currentHandle; 
}

unsigned long Flux::Handle::GetCurrentGlobalHandle()
{ 
	return s_CurrentHandle; 
}