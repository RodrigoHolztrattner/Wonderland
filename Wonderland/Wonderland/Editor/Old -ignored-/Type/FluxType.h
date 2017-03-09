////////////////////////////////////////////////////////////////////////////////
// Filename: FluxType.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxType
////////////////////////////////////////////////////////////////////////////////
class FluxType
{
/////////////
// DEFINES //
public: /////

	// The execution type
	static constexpr const char* ExecutionVariable = "exec";

/////////////
// DEFINES //
public: /////

	// The type origin
	enum class TypeOrigin
	{
		System,
		User
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxType();
	~FluxType();

//////////////////
// MAIN METHODS //
public: //////////

	// Create this type
	void CreateType(std::string _name, TypeOrigin _origin = TypeOrigin::System);

	// Set the name
	void SetName(std::string _name);

	// Get the name
	std::string GetName();

	// Compare
	static bool Compare(std::string _type1, std::string _type2);

///////////////
// VARIABLES //
private: //////

	// The type name
	std::string m_Name;

	// The type origin
	TypeOrigin m_Origin;
};