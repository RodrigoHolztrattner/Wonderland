////////////////////////////////////////////////////////////////////////////////
// Filename: VWRenderableResource.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "..\Resource\VWBuffer.h"
#include "..\..\Reference.h"

#include "..\Resource\Texture\VWTexture.h"
#include "..\Resource\Texture\VWTextureGroup.h"
#include "..\Resource\Model\VWModel.h"

#include "..\Resource\Texture\VWTextureGroupManager.h"
#include "..\Resource\Model\VWModelManager.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////
// MACROS //
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

////////////////////////////////////////////////////////////////////////////////
// Class name: VWRenderableResource
////////////////////////////////////////////////////////////////////////////////
class VWRenderableResource
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWRenderableResource();
	~VWRenderableResource();

//////////////////
// MAIN METHODS //
public: //////////

	// Return our model object
	VWModel* GetModel() { return m_Model.GetResource(); }

	// Return our texture group
	VWTextureGroup* GetTextureGroup() { return m_TextureGroup.GetResource(); }

	// Return our texture group reference
	VWTextureGroupReference& GetTextureGroupReference() { return m_TextureGroup; }

	// Return our model reference
	VWModelReference& GetModelReference() { return m_Model; }

protected:

	// Verify if a given resource reference is valid to be used
	template <typename ReferenceType>
	bool IsResourceReferenceValid(ReferenceType& _reference)
	{
		// Check if the model reference is valid
		if (!_reference.IsValid())
		{
			return false;
		}

		// Check if the model is valid
		if (!_reference->IsValid())
		{
			return false;
		}

		return true;
	}

///////////////
// VARIABLES //
private: //////
	
	// Our model reference
	VWModelReference m_Model;

	// Our texture group reference
	VWTextureGroupReference m_TextureGroup;

};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)