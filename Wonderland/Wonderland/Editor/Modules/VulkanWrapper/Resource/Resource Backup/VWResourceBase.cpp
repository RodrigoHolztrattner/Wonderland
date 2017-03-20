////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResourceBase.h"
#include "..\VWContext.h"

VulkanWrapper::VWResourceBase::VWResourceBase()
{
	// Set the initial data
	m_Status = ResourceStatus::Unknow;
	next = nullptr;
}

VulkanWrapper::VWResourceBase::~VWResourceBase()
{
}

void VulkanWrapper::VWResourceBase::InsertWakeCallback(std::function<void()> _wakeMethod)
{
	m_WakeCallbacks.push_back(_wakeMethod);
}

void VulkanWrapper::VWResourceBase::ProcessWakeCallbacks()
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