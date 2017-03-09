////////////////////////////////////////////////////////////////////////////////
// Filename: UICommandComponentCallback.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\Support\Callback\Callback.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UICommandComponentCallback
////////////////////////////////////////////////////////////////////////////////
template <typename ParameterType>
class UICommandComponentCallback
{
private:

public:
	UICommandComponentCallback()
	{
		// Set to false
		m_Set = false;
	}

	template <class CallType>
	UICommandComponentCallback(CallType& member, bool (CallType::* const &function)(ParameterType))
	{
		// Set the function
		m_Callback = makeFunctor((CBFunctor1wRet<ParameterType, bool>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}
	UICommandComponentCallback(const UICommandComponentCallback& other)
	{
		// Copy the new data
		m_Callback = other.m_Callback;
		m_Set = other.m_Set;
	}
	~UICommandComponentCallback()
	{

	}

	// Set the function for this callback
	template <class CallType>
	void Set(CallType& member, bool (CallType::* const &function)(ParameterType))
	{
		// Check if we didnt already set
		if (m_Set)
		{
			return;
		}

		// Set the function
		m_Callback = makeFunctor((CBFunctor1wRet<ParameterType, bool>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}

	// Return the set value
	bool IsSet()
	{
		return m_Set;
	}

	// Set the callback
	UICommandComponentCallback(const CBFunctor1wRet<ParameterType, bool> &uponClickDoThis) :m_Callback(uponClickDoThis) {}

	// The function that will run
	bool Run(ParameterType data) { return m_Callback(data); }

private:

	// The callback function variable
	CBFunctor1wRet<ParameterType, bool> m_Callback;

	// If the callback is set this will be true
	bool m_Set;
};
