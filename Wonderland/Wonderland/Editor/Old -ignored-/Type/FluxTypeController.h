////////////////////////////////////////////////////////////////////////////////
// Filename: FluxTypeController.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <unordered_map>
#include "FluxType.h"

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
// Class name: FluxTypeController
////////////////////////////////////////////////////////////////////////////////
class FluxTypeController
{
/////////////
// DEFINES //
public: /////

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxTypeController();
	~FluxTypeController();

	// Add a new type
	void AddType(std::string _typeName, FluxType::TypeOrigin _origin = FluxType::TypeOrigin::System);

	// Remove a type
	void RemoveType(FluxType _type);

	// Validate if a given type exist
	bool ValidateType(FluxType _type);

	// Return a type by name
	FluxType GetTypeByName(std::string _typeName);

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
protected: ////

	// The type map
	std::unordered_map <std::string, FluxType> m_TypeMap;
};