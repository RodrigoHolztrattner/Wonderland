////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardSupplyObject.h"

Hoard::Supply::HoardSupplyObject::HoardSupplyObject()
{
	// Set the initial data
	m_Status = Status::Unknow;
}

Hoard::Supply::HoardSupplyObject::~HoardSupplyObject()
{
}

bool Hoard::Supply::HoardSupplyObject::Initialize()
{
	// Set the status
	m_Status = Status::Created;

	return true;
}

void Hoard::Supply::HoardSupplyObject::FinishLoadingProcess()
{
	m_Status = Status::Initialized;
}