////////////////////////////////////////////////////////////////////////////////
// Filename: TriggerManager.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TriggerManager.h"

TriggerManager::TriggerManager()
{
}

TriggerManager::TriggerManager(const TriggerManager& other)
{
}

TriggerManager::~TriggerManager()
{
}

void TriggerManager::RegisterTrigger(TriggerHandle* _who, FHashedString _signal)
{
	// Get the trigger
	TriggerType* trigger = GetTrigger(_signal);

	// Set the data
	trigger->callees.Add(_who);

	// Add the new trigger
	m_TriggerArray.Add(trigger, _signal.Hash());
}

void TriggerManager::RegisterTrigger(TriggerHandle* _who, MemberCallback<void*> _callback, FHashedString _signal)
{
	// Get the trigger
	TriggerType* trigger = GetTrigger(_signal);

	// Set the data
	trigger->callees.Add(_who);
	trigger->calleeCallbacks.Add(_callback);

	// Add the new trigger
	m_TriggerArray.Add(trigger, _signal.Hash());
}

void TriggerManager::UnregisterTrigger(TriggerHandle* _who, FHashedString _signal)
{
	// Try to find the trigger
	TriggerType* trigger = m_TriggerArray[_signal.Hash()];
	if (trigger == nullptr)
	{
		return;
	}

	// Remove the caller
	// ...
}

void TriggerManager::CallTrigger(FHashedString _signal)
{
	// Try to find the trigger
	TriggerType* trigger = m_TriggerArray[_signal.Hash()];
	if (trigger == nullptr)
	{
		return;
	}

	// For each caller
	// ...

	// For each callback
	// ...
}

TriggerManager::TriggerType* TriggerManager::GetTrigger(FHashedString _signal)
{
	// Try to find the trigger
	TriggerType* trigger = m_TriggerArray[_signal.Hash()];
	if (trigger != nullptr)
	{
		return trigger;
	}

	// Create a new trigger
	trigger = new TriggerType;
	trigger->signal = _signal.Hash();

	return trigger;
}