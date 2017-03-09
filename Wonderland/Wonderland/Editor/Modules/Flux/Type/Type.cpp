////////////////////////////////////////////////////////////////////////////////
// Filename: Type.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Type.h"
#include "..\Class\Class.h"

Flux::Type::Type()
{
}

Flux::Type::Type(std::string _typeName, Flux::Handle _bondedClass)
{
	// Set the data
	m_TypeName = _typeName;
	m_BondedClassHandle = _bondedClass;
	m_IsPrimitive = !_bondedClass.IsValid();
}

Flux::Type::~Type()
{
}

std::string Flux::Type::GetTypeName()
{
	return m_TypeName;
}

Flux::Handle Flux::Type::GetTypeHandle()
{
	return m_BondedClassHandle;
}

bool Flux::Type::IsPrimitiveType()
{
	return m_IsPrimitive;
}