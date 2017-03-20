////////////////////////////////////////////////////////////////////////////////
// Filename: HoardResourceVault.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include "..\NamespaceDefinitions.h"
#include "HoardResource.h"

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

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardResourceVault
////////////////////////////////////////////////////////////////////////////////
class HoardResourceVault
{
private:

	struct ResourceHolder
	{
		// The resource itself
		HoardResource* resource;

		// The resource identifier
		uint32_t resourceIdentifier;
	};

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardResourceVault();
	~HoardResourceVault();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the resource manager
	bool Initialize();

	// Check if a internal resource is currently loaded into memory
	HoardResource* IsResourceLoaded(uint32_t _resourceIdentifier);

	// Insert a external resource into memory
	void InsertResource(HoardResource* _resource, uint32_t _resourceIdentifier);

///////////////
// VARIABLES //
private: //////

	// Our internal resource array
	std::vector<ResourceHolder> m_Resources;

};

// Hoard Resource Module
NamespaceEnd(Hoard)