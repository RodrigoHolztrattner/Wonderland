////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardResourceRequest.h"

Hoard::HoardResourceRequest::HoardResourceRequest()
{
	// Set the initial data
	// ...
}

Hoard::HoardResourceRequest::~HoardResourceRequest()
{
}

void Hoard::HoardResourceRequest::Create(Reference::Blob<HoardResource>* _resourceReference, uint32_t _resourceId, std::function<void()> _wakeCallback, std::function<void()> _processMethod)
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