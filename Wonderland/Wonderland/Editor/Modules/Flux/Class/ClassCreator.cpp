////////////////////////////////////////////////////////////////////////////////
// Filename: ClassCreator.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ClassCreator.h"
#include "ClassRegister.h"
#include "..\Type\TypeRegister.h"
#include "..\Type\TypeCreator.h"
#include "..\Type\Type.h"

Flux::ClassCreator::ClassCreator()
{
}

Flux::ClassCreator::~ClassCreator()
{
}

Flux::Class* Flux::ClassCreator::CreateClass(std::string _className)
{
	// Get all register and creator instances we need
	Flux::ClassRegister* classRegister = Flux::ClassRegister::GetInstance();
	Flux::TypeRegister* typeRegister = Flux::TypeRegister::GetInstance();
	Flux::TypeCreator* typeCreator = Flux::TypeCreator::GetInstance();

	// Check if a class with the same name already exist
	if (classRegister->ClassWithNameExists(_className))
	{
		// Error, a class with the same name already exist
		return nullptr;
	}

	// Check if a type with the same name already exist
	if (typeRegister->TypeWithNameExists(_className))
	{
		// Error, a type with the same name already exist
		return nullptr;
	}

	// The new class object
	Flux::Class* newClass = new Flux::Class(_className);

	// Generate a new handle for the class object
	newClass->GenerateHandle();

	// Create the new variable type
	Flux::Type* newClassType = typeCreator->CreateType(_className, newClass);

	// Register the new class
	classRegister->RegisterClass(newClass);

	return newClass;
}
