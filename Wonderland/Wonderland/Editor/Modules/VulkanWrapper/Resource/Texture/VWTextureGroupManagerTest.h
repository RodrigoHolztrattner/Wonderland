////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroupManagerTest.h
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

#include "..\..\Material\VWDescriptorSetCreator.h"
#include "VWTextureGroup.h"
#include "VWTextureGroupIndex.h"

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
// Class name: VWTextureGroupManagerTest
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupManagerTest : public Hoard::Supply::Manager<VWTextureGroup, VWTextureGroupIndex>, public VWDescriptorSetCreator
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroupManagerTest();
	~VWTextureGroupManagerTest();

//////////////////
// MAIN METHODS //
public: //////////

	// Create the descriptor layout
	void CreateDescriptorLayout(VWContext* _graphicContext);

	// Release this image
	void Release() override;

	// Create a new supply object and request the resource loading
	VWTextureGroup* CreateAndRequestObject(Hoard::ResourceManager* _resourceManager, uint32_t _resourceIdentifier) override;

///////////////
// VARIABLES //
private: //////

	// The context reference
	VWContext* m_ContextReference;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)