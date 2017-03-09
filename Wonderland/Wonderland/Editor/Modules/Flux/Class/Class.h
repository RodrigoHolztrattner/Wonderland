////////////////////////////////////////////////////////////////////////////////
// Filename: Class.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "..\Handle\Handle.h"
#include "..\Box\Function\DynamicMemberFunction\DynamicMemberFunction.h"
#include "..\Variable.h"

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

// We know the class creator
class ClassCreator;

////////////////////////////////////////////////////////////////////////////////
// Class name: Class
////////////////////////////////////////////////////////////////////////////////
class Class : public Flux::Handle
{
	// The class creator is a friend
	friend ClassCreator;

//////////////////
// CONSTRUCTORS //
protected: ///////

	// Constructor / destructor
	Class();
	Class(std::string _className);
	~Class();

//////////////////
// MAIN METHODS //
public: //////////

	// Set the class name
	void SetClassName(std::string _name);

	// Return the class name
	std::string GetClassName();

	// Add a member variable
	bool AddMemberVariable(Flux::MemberVariable _memberVariable);

	// Add a member function
	bool AddMemberFunction(Flux::DynamicMemberFunction _memberFunction);

	// Get a member function
	Flux::DynamicMemberFunction* GetMemberFunction(Flux::Handle _memberHandle);
	Flux::DynamicMemberFunction* GetMemberFunction(std::string _memberName);

	// Get a member variable
	Flux::MemberVariable* GetMemberVariable(Flux::Handle _memberHandle);

	// TO-DO: Create the "remove/modify" functions

///////////////
// VARIABLES //
private: //////

	// The class name
	std::string m_ClassName;

	// All the member variables
	std::vector<Flux::MemberVariable> m_MemberVariables;

	// All the member functions
	std::vector<Flux::DynamicMemberFunction> m_MemberFunctions;
};

// Flux workspace
NamespaceEnd(Flux)
