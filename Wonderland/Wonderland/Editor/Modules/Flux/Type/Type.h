////////////////////////////////////////////////////////////////////////////////
// Filename: Type.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include "..\Handle\Handle.h"

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

// We know the variable type creator
class TypeCreator;

////////////////////////////////////////////////////////////////////////////////
// Class name: Type
////////////////////////////////////////////////////////////////////////////////
class Type : public Flux::Handle
{
	// The variable type creator is a friend
	friend TypeCreator;

//////////////////
// CONSTRUCTORS //
protected: ///////

	// Constructor / destructor
	Type();
	Type(std::string _typeName, Flux::Handle _bondedClass = Flux::Handle());
	~Type();

//////////////////
// MAIN METHODS //
public: //////////

	// Return the type name
	std::string GetTypeName();

	// Return the type handle
	Flux::Handle GetTypeHandle();

	// Return if this type is a primitive one
	bool IsPrimitiveType();

///////////////
// VARIABLES //
private: //////

	// The Type name
	std::string m_TypeName;

	// If this Type is bonded, here is the class handle
	Flux::Handle m_BondedClassHandle;

	// If this is a primitive Type
	bool m_IsPrimitive;
};

// Flux workspace
NamespaceEnd(Flux)
