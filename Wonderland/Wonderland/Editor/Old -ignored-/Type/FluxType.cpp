////////////////////////////////////////////////////////////////////////////////
// Filename: FluxType.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxType.h"

FluxType::FluxType()
{
}

FluxType::~FluxType()
{
}

void FluxType::CreateType(std::string _name, TypeOrigin _origin)
{
	m_Name = _name;
	m_Origin = _origin;
}

void FluxType::SetName(std::string _name)
{
    m_Name = _name;
}

std::string FluxType::GetName()
{
    return m_Name;
}

bool FluxType::Compare(std::string _type1, std::string _type2)
{
	if (!_type1.compare(_type2))
	{
		return true;
	}

	return false;
}