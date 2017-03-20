////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResourceRequest.h"
#include "..\VWContext.h"

VulkanWrapper::VWResourceRequest::VWResourceRequest()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWResourceRequest::~VWResourceRequest()
{
}

void VulkanWrapper::VWResourceRequest::Create(Reference::Blob<VWResource>* _resourceReference, uint32_t _resourceId, std::function<void()> _wakeCallback, std::function<void()> _processMethod)
{
	// Set the resource ptr
	m_ResourceReference = _resourceReference;

	// Set the wake callback
	m_WakeCallback = _wakeCallback;

	// Set the id
	m_ResourceId = _resourceId;

	// Set the process method
	m_ResourceProcessMethod = _processMethod;
}