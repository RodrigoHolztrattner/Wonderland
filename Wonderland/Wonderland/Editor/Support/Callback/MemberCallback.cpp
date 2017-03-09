///////////////////////////////////////////////////////////////////////////////
// Filename: MemberCallback.cpp
///////////////////////////////////////////////////////////////////////////////
#include "MemberCallback.h"

/*

MemberCallback::MemberCallback()
{
	// Set to false
	m_Set = false;
}

MemberCallback::MemberCallback(const MemberCallback& other)
{
	// Copy the new data
	m_Callback = other.m_Callback;
	m_Set = other.m_Set;
}

MemberCallback::~MemberCallback()
{
}


template <class CallType>
void MemberCallback::Set(CallType* member, void (CallType::* const &function)(void*))
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


bool MemberCallback::IsSet()
{
	return m_Set;
}

*/