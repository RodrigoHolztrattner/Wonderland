////////////////////////////////////////////////////////////////////////////////
// Filename: VWModelManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\..\..\HashedString.h"
#include "..\..\..\Reference.h"
#include "..\..\..\Hoard\Hoard.h"

#include "VWModel.h"
#include "VWModelIndex.h"

#include <vector>
#include <map>
#include <array>
#include <list>
#include <functional>

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

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWContext;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWModelManager
////////////////////////////////////////////////////////////////////////////////
class VWModelManager : public Hoard::Supply::Manager<VWModel, VWModelIndex>
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWModelManager();
	~VWModelManager();

//////////////////
// MAIN METHODS //
public: //////////

		// Set the context reference
	void SetContextReference(VWContext* _context) { m_ContextReference = _context; }

	// Release this image
	void Release() override;

	// Create a new supply object and request the resource loading
	VWModel* CreateAndRequestObject(Hoard::ResourceManager* _resourceManager, uint32_t _resourceIdentifier) override;

///////////////
// VARIABLES //
private: //////

	// The context reference
	VWContext* m_ContextReference;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)