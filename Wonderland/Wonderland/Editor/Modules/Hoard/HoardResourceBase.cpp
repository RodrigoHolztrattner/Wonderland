////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardResourceBase.h"

Hoard::HoardResourceBase::HoardResourceBase()
{
	// Set the initial data
	m_Status = ResourceStatus::Unknow;
	next = nullptr;
}

Hoard::HoardResourceBase::~HoardResourceBase()
{
}

void Hoard::HoardResourceBase::InsertWakeCallback(std::function<void()> _wakeMethod)
{
	m_WakeCallbacks.push_back(_wakeMethod);
}

void Hoard::HoardResourceBase::ProcessWakeCallbacks()
{
	// For each wake callback
	for (auto& callback : m_WakeCallbacks)
	{
		// Call the callback
		callback();
	}

	// Clear the callback list
	m_WakeCallbacks.clear();
}