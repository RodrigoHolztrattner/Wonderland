////////////////////////////////////////////////////////////////////////////////
// Filename: TypeRegister.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TypeRegister.h"
#include "..\Class\Class.h"

Flux::TypeRegister::TypeRegister()
{
}

Flux::TypeRegister::~TypeRegister()
{
}

bool Flux::TypeRegister::RegisterType(Flux::Type* _newType)
{
	// Check if a type with the same name already exists
	if (TypeWithNameExists(_newType->GetTypeName()))
	{
		return false;
	}

	// Add the new type into the registered array
	m_RegisteredTypes.push_back(_newType);

	return true;
}

Flux::Type* Flux::TypeRegister::GetType(std::string _name)
{
	return FindTypeByName(_name);
}

Flux::Type* Flux::TypeRegister::GetType(Flux::Handle _typeHandle)
{
	return FindTypeByHandle(_typeHandle);
}

bool Flux::TypeRegister::TypeWithNameExists(std::string _typeName)
{
	return FindTypeByName(_typeName) != nullptr;
}

Flux::Type* Flux::TypeRegister::FindTypeByName(std::string _name)
{
	// For each registered type
	for (auto typeObject : m_RegisteredTypes)
	{
		// Compare the names
		if (!_name.compare(typeObject->GetTypeName()))
		{
			return typeObject;
		}
	}

	return nullptr;
}

Flux::Type* Flux::TypeRegister::FindTypeByHandle(Flux::Handle _handle)
{
	// For each registered type
	for (auto typeObject : m_RegisteredTypes)
	{
		// Compare the names
		if (typeObject->CompareHandle(_handle))
		{
			return typeObject;
		}
	}

	return nullptr;
}