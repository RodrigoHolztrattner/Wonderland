////////////////////////////////////////////////////////////////////////////////
// Filename: TypeCreator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include "Type.h"
#include "..\Class\Class.h"

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
// Class name: TypeCreator
////////////////////////////////////////////////////////////////////////////////
class TypeCreator
{

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	TypeCreator();
	~TypeCreator();

//////////////////
// MAIN METHODS //
public: //////////

	// Return a instance to this class
	static TypeCreator* GetInstance()
	{
		// The instance
		static Flux::TypeCreator* typeCreator = nullptr;
		if (typeCreator == nullptr)
		{
			// Create the new type creator object
			typeCreator = new Flux::TypeCreator();
		}

		return typeCreator;
	}

	// Create a new variable type
	Flux::Type* CreateType(std::string _typeName, Flux::Class* _bondedClass = nullptr);

///////////////
// VARIABLES //
private: //////
};

// Flux workspace
NamespaceEnd(Flux)