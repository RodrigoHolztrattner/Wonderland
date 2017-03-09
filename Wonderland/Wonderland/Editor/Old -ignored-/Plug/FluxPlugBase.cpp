////////////////////////////////////////////////////////////////////////////////
// Filename: FluxPlugBase.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxPlugBase.h"
#include "..\LinkObject.h"

FluxPlugBase::FluxPlugBase()
{
	// Set the initial data
	m_PlugType = PlugType::Undefined;
}

FluxPlugBase::FluxPlugBase(const FluxPlugBase& _other)
{
	// Copy the plug type and name
	m_PlugType = _other.m_PlugType;
	m_PlugName = _other.m_PlugName;
}

FluxPlugBase::~FluxPlugBase()
{
}

void FluxPlugBase::SetPlugName(std::string _name)
{
	m_PlugName = _name;
}

std::string FluxPlugBase::GetPlugName()
{
	return m_PlugName;
}

void FluxPlugBase::SetPlugType(PlugType _type)
{
	m_PlugType = _type;
}

FluxPlugBase::PlugType FluxPlugBase::GetPlugType()
{
	return m_PlugType;
}

bool FluxPlugBase::IsFromType(PlugType _type)
{
	if (m_PlugType == _type)
	{
		return true;
	}

	return false;
}