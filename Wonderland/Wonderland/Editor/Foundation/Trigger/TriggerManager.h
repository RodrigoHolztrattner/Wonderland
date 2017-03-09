////////////////////////////////////////////////////////////////////////////////
// Filename: TriggerManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\String\FHashedString.h"
#include "..\..\Support\Callback\MemberCallback.h"
#include "..\..\Support\Container\Array\Array.h"
#include "..\..\Support\Container\Array\BinaryArray.h"
#include <string>
#include <iostream>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

/*

	- Lambda
	- Callback
	- Function

*/

class TriggerHandle;

////////////////////////////////////////////////////////////////////////////////
// Class name: TriggerManager
////////////////////////////////////////////////////////////////////////////////
class TriggerManager
{
	// The trigger type
	struct TriggerType
	{
		// The callee objects
		Array<TriggerHandle*> callees;

		// The callee callbacks
		Array<MemberCallback<void*>> calleeCallbacks;

		// The trigger signal
		int signal;
	};

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
public: //////////////////////

	// We cant create this widget without using the UIBase::Create()
	TriggerManager();
	TriggerManager(const TriggerManager&);
	~TriggerManager();

	// Register a trigger
	void RegisterTrigger(TriggerHandle* _who, FHashedString _signal);
	void RegisterTrigger(TriggerHandle* _who, MemberCallback<void*> _callback, FHashedString _signal);

	// Unregister a trigger
	void UnregisterTrigger(TriggerHandle* _who, FHashedString _signal);

	// Call a trigger
	void CallTrigger(FHashedString _signal);

private:

	// Return a signal is it exist or create a new one
	TriggerType* GetTrigger(FHashedString _signal);

///////////////
// VARIABLES //
private: //////

	// The trigger array
	BinaryArray<TriggerType*, int> m_TriggerArray;

};