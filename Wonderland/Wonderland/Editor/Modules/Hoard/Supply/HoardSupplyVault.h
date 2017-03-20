////////////////////////////////////////////////////////////////////////////////
// Filename: HoardSupplyVault.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"

#include "HoardSupplyObject.h"

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

// Hoard Resource Module
NamespaceBegin(Hoard)

// Hoard Resource Supply Module
NamespaceBegin(Supply)

////////////////
// FORWARDING //
////////////////

class VWContext;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardSupplyVault
////////////////////////////////////////////////////////////////////////////////
// typedef HoardSupplyObject ObjectType;
template <typename ObjectType>
class HoardSupplyVault
{
private:

	struct ObjectHolder
	{
		// The object itself
		ObjectType* object;

		// The object identifier
		HashedStringIdentifier identifier;
	};

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardSupplyVault() {}
	~HoardSupplyVault() {}

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the resource manager
	bool Initialize()
	{

		return true;
	}

	// Check if a internal resource is currently loaded into memory
	ObjectType* IsLoaded(HashedStringIdentifier _identifier)
	{
		if (!m_Objects.size())
		{
			return nullptr;
		}

		// For each object loaded
		for (auto& objectHolder : m_Objects)
		{
			// Compare the resource paths
			if (objectHolder.identifier == _identifier)
			{
				return objectHolder.object;
			}
		}

		return nullptr;
	}

	// Insert a external resource into memory
	void Insert(ObjectType* _object, HashedStringIdentifier _identifier)
	{
		ObjectHolder objectHolder = {};
		objectHolder.object = _object;
		objectHolder.identifier = _identifier;

		m_Objects.push_back(objectHolder);
	}

///////////////
// VARIABLES //
private: //////

	// Our object array
	std::vector<ObjectHolder> m_Objects; //TODO: Usar um map
};

// Hoard Resource Supply Module
NamespaceEnd(Supply)

// Hoard Resource Module
NamespaceEnd(Hoard)