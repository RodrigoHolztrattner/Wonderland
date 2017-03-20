////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardResource.h"

Hoard::HoardResource::HoardResource()
{
	// Set the initial data
	m_TotalReferences = 0;
}

Hoard::HoardResource::~HoardResource()
{
}

void Hoard::HoardResource::Initialize()
{
	// Set the current status
	//m_Status = ResourceStatus::Created;
	SetStatus(ResourceStatus::Created);

	// Increment the reference count
	IncrementReferenceCount();
}

void Hoard::HoardResource::Release()
{

}