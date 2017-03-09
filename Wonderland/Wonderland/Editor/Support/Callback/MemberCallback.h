////////////////////////////////////////////////////////////////////////////////
// Filename: MemberCallback.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MemberCallback_H_
#define _MemberCallback_H_

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
// Class name: MemberCallback
////////////////////////////////////////////////////////////////////////////////
template <typename ParameterType>
class MemberCallback
{
private:

public:
	MemberCallback()
	{
		// Set to false
		m_Set = false;
	}

	template <class CallType>
	MemberCallback(CallType& member, void (CallType::* const &function)(ParameterType))
	{
		// Set the function
		m_Callback = makeFunctor((CBFunctor1<ParameterType>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}
	MemberCallback(const MemberCallback& other)
	{
		// Copy the new data
		m_Callback = other.m_Callback;
		m_Set = other.m_Set;
	}
	~MemberCallback()
	{

	}

	// Set the function for this callback
	template <class CallType>
	void Set(CallType& member, void (CallType::* const &function)(ParameterType))
	{
		// Check if we didnt already set
		if (m_Set)
		{
			return;
		}

		// Set the function
		m_Callback = makeFunctor((CBFunctor1<ParameterType>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}

	// Return the set value
	bool IsSet()
	{
		return m_Set;
	}

	// Set the callback
	MemberCallback(const CBFunctor1<ParameterType> &uponClickDoThis) :m_Callback(uponClickDoThis) {}

	// The function that will run
	void Run(ParameterType data) { m_Callback(data); }

private:

	// The callback function variable
	CBFunctor1<ParameterType> m_Callback;

	// If the callback is set this will be true
	bool m_Set;
};
/*
template <typename ParameterType1, typename ParameterType2>
class MemberCallback
{
private:

public:
	MemberCallback()
	{
		// Set to false
		m_Set = false;
	}

	template <class CallType>
	MemberCallback(CallType& member, void (CallType::* const &function)(ParameterType1, ParameterType2))
	{
		// Set the function
		m_Callback = makeFunctor((CBFunctor2<ParameterType1, ParameterType2>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}
	MemberCallback(const MemberCallback& other)
	{
		// Copy the new data
		m_Callback = other.m_Callback;
		m_Set = other.m_Set;
	}
	~MemberCallback()
	{

	}

	// Set the function for this callback
	template <class CallType>
	void Set(CallType& member, void (CallType::* const &function)(ParameterType1, ParameterType2))
	{
		// Check if we didnt already set
		if (m_Set)
		{
			return;
		}

		// Set the function
		m_Callback = makeFunctor((CBFunctor2<ParameterType1, ParameterType2>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}

	// Return the set value
	bool IsSet()
	{
		return m_Set;
	}

	// Set the callback
	MemberCallback(const CBFunctor2<ParameterType1, ParameterType2> &uponClickDoThis) :m_Callback(uponClickDoThis) {}

	// The function that will run
	void Run(ParameterType1 data1, ParameterType2 data2) { m_Callback(data1, data2); }

private:

	// The callback function variable
	CBFunctor2<ParameterType1, ParameterType2> m_Callback;

	// If the callback is set this will be true
	bool m_Set;
};

template <typename ParameterType1, typename ParameterType2, typename ParameterType3>
class MemberCallback
{
private:

public:
	MemberCallback()
	{
		// Set to false
		m_Set = false;
	}

	template <class CallType>
	MemberCallback(CallType& member, void (CallType::* const &function)(ParameterType1, ParameterType2, ParameterType3))
	{
		// Set the function
		m_Callback = makeFunctor((CBFunctor3<ParameterType1, ParameterType2, ParameterType3>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}
	MemberCallback(const MemberCallback& other)
	{
		// Copy the new data
		m_Callback = other.m_Callback;
		m_Set = other.m_Set;
	}
	~MemberCallback()
	{

	}

	// Set the function for this callback
	template <class CallType>
	void Set(CallType& member, void (CallType::* const &function)(ParameterType1, ParameterType2, ParameterType3))
	{
		// Check if we didnt already set
		if (m_Set)
		{
			return;
		}

		// Set the function
		m_Callback = makeFunctor((CBFunctor3<ParameterType1, ParameterType2, ParameterType3>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}

	// Return the set value
	bool IsSet()
	{
		return m_Set;
	}

	// Set the callback
	MemberCallback(const CBFunctor3<ParameterType1, ParameterType2, ParameterType3> &uponClickDoThis) :m_Callback(uponClickDoThis) {}

	// The function that will run
	void Run(ParameterType1 data1, ParameterType2 data2, ParameterType3 data3) { m_Callback(data1, data2, data3); }

private:

	// The callback function variable
	CBFunctor3<ParameterType1, ParameterType2, ParameterType3> m_Callback;

	// If the callback is set this will be true
	bool m_Set;
};

template <typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
class MemberCallback
{
private:

public:
	MemberCallback()
	{
		// Set to false
		m_Set = false;
	}

	template <class CallType>
	MemberCallback(CallType& member, void (CallType::* const &function)(ParameterType1, ParameterType2, ParameterType3, ParameterType4))
	{
		// Set the function
		m_Callback = makeFunctor((CBFunctor4<ParameterType1, ParameterType2, ParameterType3, ParameterType4>*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}
	MemberCallback(const MemberCallback& other)
	{
		// Copy the new data
		m_Callback = other.m_Callback;
		m_Set = other.m_Set;
	}
	~MemberCallback()
	{

	}

	// Set the function for this callback
	template <class CallType>
	void Set(CallType& member, void (CallType::* const &function)(ParameterType1, ParameterType2, ParameterType3, ParameterType4))
	{
		// Check if we didnt already set
		if (m_Set)
		{
			return;
		}

		// Set the function
		m_Callback = makeFunctor((CBFunctor4<ParameterType1, ParameterType2, ParameterType3, ParameterType4*)0, member, function);

		// Set the bool variable
		m_Set = true;
	}

	// Return the set value
	bool IsSet()
	{
		return m_Set;
	}

	// Set the callback
	MemberCallback(const CBFunctor4<ParameterType1, ParameterType2, ParameterType3, ParameterType4> &uponClickDoThis) :m_Callback(uponClickDoThis) {}

	// The function that will run
	void Run(ParameterType1 data1, ParameterType2 data2, ParameterType3 data3, ParameterType4 data4) { m_Callback(data1, data2, data3, data4); }

private:

	// The callback function variable
	CBFunctor4<ParameterType1, ParameterType2, ParameterType3, ParameterType4> m_Callback;

	// If the callback is set this will be true
	bool m_Set;
};
*/
#endif