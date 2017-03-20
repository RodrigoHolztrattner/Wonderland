////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroupRequest.h"
#include "..\..\VWContext.h"

VulkanWrapper::VWTextureGroupRequest::VWTextureGroupRequest()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWTextureGroupRequest::~VWTextureGroupRequest()
{
}

void VulkanWrapper::VWTextureGroupRequest::Create(Reference::Blob<VWTextureGroup>* _resourceReference, HashedStringIdentifier _resourceId)
{
	// Set the resource ptr
	m_TextureGroupReference = _resourceReference;

	// Set the id
	m_TextureGroupIdentifier = _resourceId;
}