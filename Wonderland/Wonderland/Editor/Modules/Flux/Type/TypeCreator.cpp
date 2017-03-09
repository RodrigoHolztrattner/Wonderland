////////////////////////////////////////////////////////////////////////////////
// Filename: TypeCreator.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TypeCreator.h"
#include "TypeRegister.h"

Flux::TypeCreator::TypeCreator()
{
}

Flux::TypeCreator::~TypeCreator()
{
}

Flux::Type* Flux::TypeCreator::CreateType(std::string _typeName, Flux::Class* _bondedClass)
{
	// Get the type register instance
	Flux::TypeRegister* typeRegister = Flux::TypeRegister::GetInstance();

	// Check if a type with the name name already exist
	if (typeRegister->TypeWithNameExists(_typeName))
	{
		// Error, a class with the name name already exist
		return nullptr;
	}

	// The new type
	Flux::Type* newType = (_bondedClass != nullptr) ? new Flux::Type(_typeName, *_bondedClass) : new Flux::Type(_typeName);

	// Generate a valid handle for this type
	newType->GenerateHandle();

	// Register the new type
	if (!typeRegister->RegisterType(newType))
	{
		return nullptr;
	}

	// Generate a new handle for the variable type
	newType->GenerateHandle();

	return newType;
}