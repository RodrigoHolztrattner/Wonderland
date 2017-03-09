////////////////////////////////////////////////////////////////////////////////
// Filename: WCallback.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WCallback_H_
#define _WCallback_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "Callback.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: WCallback
////////////////////////////////////////////////////////////////////////////////
template <typename ParameterType>
class WCallback
{
private:

public:
	WCallback()
	{
		// Set to false
		m_Set = false;
	}
	template <class CallType>
	WCallback(CallType& member, void (CallType::* const &function)(ParameterType*))
	{
		// Set the function
		m_Callback = makeFunctor((CBFunctor1<ParameterType*>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}
	WCallback(const WCallback& other)
	{
		// Copy the new data
		m_Callback = other.m_Callback;
		m_Set = other.m_Set;
	}
	~WCallback()
	{

	}

	// Set the function for this callback
	template <class CallType>
	void Set(CallType& member, void (CallType::* const &function)(ParameterType*))
	{
		// Check if we didnt already set
		if(m_Set)
		{
			return;
		}

		// Set the function
		m_Callback = makeFunctor((CBFunctor1<ParameterType*>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}

	// Set the callback
	WCallback(const CBFunctor1<ParameterType*> &uponClickDoThis) :m_Callback(uponClickDoThis){}

	// The function that will run
	void Run(ParameterType* data){ m_Callback(data); }

	// Return the set value
	bool IsSet()
	{
		return m_Set;
	}
	
private:

	// The callback function variable
	CBFunctor1<ParameterType*> m_Callback;

	// If the callback is set this will be true
	bool m_Set;
};

#endif
