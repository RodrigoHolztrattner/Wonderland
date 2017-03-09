////////////////////////////////////////////////////////////////////////////////
// Filename: TypeRegister.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "Type.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Flux workspace
NamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// Class name: TypeRegister
////////////////////////////////////////////////////////////////////////////////
class TypeRegister
{

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	TypeRegister();
	~TypeRegister();

	// Return a instance to this class
	static TypeRegister* GetInstance()
	{
		// The instance
		static Flux::TypeRegister* typeRegister = nullptr;
		if (typeRegister == nullptr)
		{
			// Create the new type register object
			typeRegister = new Flux::TypeRegister();
		}

		return typeRegister;
	}

	// Register a new type
	bool RegisterType(Flux::Type* _newType);

	// Return a registered type with the given name
	Flux::Type* GetType(std::string _name);

	// Return a registered type with the given handle
	Flux::Type* GetType(Flux::Handle _typeHandle);

	// Check if a type with a given name already exist
	bool TypeWithNameExists(std::string _typeName);

//////////////////
// MAIN METHODS //
public: //////////

private:

	// Find a type by name
	Flux::Type* FindTypeByName(std::string _name);

	// Find a type by handle
	Flux::Type* FindTypeByHandle(Flux::Handle _handle);

///////////////
// VARIABLES //
private: //////

	// All the registered types
	std::vector<Flux::Type*> m_RegisteredTypes;
};

// Flux workspace
NamespaceEnd(Flux)
