///////////////////////////////////////////////////////////////////////////////
// Filename: WCallback.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WCallback.h"

/*

WCallback::WCallback()
{
	// Set to false
	m_Set = false;
}

WCallback::WCallback(const WCallback& other)
{
	// Copy the new data
	m_Callback = other.m_Callback;
	m_Set = other.m_Set;
}

WCallback::~WCallback()
{
}


template <class CallType>
void WCallback::Set(CallType* member, void (CallType::* const &function)(void*))
{
	// Check if we didnt already set
	if(m_Set)
	{
		return;
	}

	// Set the function
	m_Callback = makeFunctor((CBFunctor1<void*>*)0,*member,function);

	// Set the bool variable
	m_Set = true;
}


bool WCallback::IsSet()
{
	return m_Set;
}

*/