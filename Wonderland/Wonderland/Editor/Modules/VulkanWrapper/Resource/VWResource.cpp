////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResource.h"
#include "..\VWContext.h"

VulkanWrapper::VWResource::VWResource()
{
	// Set the initial data
	m_TotalReferences = 0;
}

VulkanWrapper::VWResource::~VWResource()
{
}

void VulkanWrapper::VWResource::Initialize()
{
	// Set the current status
	//m_Status = ResourceStatus::Created;
	SetStatus(ResourceStatus::Created);

	// Increment the reference count
	IncrementReferenceCount();
}

void VulkanWrapper::VWResource::Release()
{

}