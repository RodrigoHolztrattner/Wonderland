////////////////////////////////////////////////////////////////////////////////
// Filename: HoardSupplyObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\Reference.h"
#include "..\HoardResource.h"

#include <vector>
#include <map>
#include <array>
#include <list>
#include <atomic>

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

class VWTextureGroupManager;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardSupplyObject
////////////////////////////////////////////////////////////////////////////////
class HoardSupplyObject
{
public:

	enum class Status
	{
		Unknow,
		Created,
		Loading,
		Loaded,
		Initialized
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardSupplyObject();
	~HoardSupplyObject();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this object
	bool Initialize();

	// Finish the loading process
	void FinishLoadingProcess();

	// Return the status
	Status GetStatus() { return m_Status; }

	// Return the resource reference
	Reference::Blob<Hoard::HoardResource>* GetResourceReference() { return &m_ResourceReference; }

	// Check if this object is valid
	virtual bool IsValid() = 0;

///////////////
// VARIABLES //
private: //////

	// The status
	Status m_Status;

	// The resource reference
	Reference::Blob<Hoard::HoardResource> m_ResourceReference;
};

// Hoard Resource Supply Module
NamespaceEnd(Supply)

// Hoard Resource Module
NamespaceEnd(Hoard)