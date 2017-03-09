////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroupRequest.h"
#include "..\VWContext.h"

VulkanWrapper::VWTextureGroupRequest::VWTextureGroupRequest()
{
	// Set the initial data
	m_RequestType = RequestType::Unknow;
}

VulkanWrapper::VWTextureGroupRequest::~VWTextureGroupRequest()
{
}

void VulkanWrapper::VWTextureGroupRequest::CreateFromId(VWTextureGroupReference* _resourceReference, uint32_t _resourceId, std::function<void()> _wakeCallback)
{
	// Set the resource ptr
	m_ResourceReference = _resourceReference;

	// Set the wake callback
	m_WakeCallback = _wakeCallback;

	// Set the id
	m_ResourceId = _resourceId;

	// Set the request type
	m_RequestType = RequestType::InternalIdentifier;
}

void VulkanWrapper::VWTextureGroupRequest::CreateFromPath(VWTextureGroupReference* _resourceReference, std::string _path, std::function<void()> _wakeCallback)
{
	// Set the resource ptr
	m_ResourceReference = _resourceReference;

	// Set the wake callback
	m_WakeCallback = _wakeCallback;

	// Set the resource name/path
	m_ResourcePath = _path;

	// Set the request type
	m_RequestType = RequestType::ExternalPath;
}