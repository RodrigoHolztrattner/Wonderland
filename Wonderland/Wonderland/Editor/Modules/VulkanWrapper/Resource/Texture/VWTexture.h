////////////////////////////////////////////////////////////////////////////////
// Filename: VWTexture.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\..\..\Reference.h"
#include "VWTextureGroup.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

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
// Class name: VWTexture
////////////////////////////////////////////////////////////////////////////////
class VWTexture
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTexture();
	~VWTexture();

//////////////////
// MAIN METHODS //
public: //////////

	// Create this texture
	void CreateWithTextureGroup(Reference::Blob<VWTextureGroup>* _textureGroup, const char* _textureName);

	// Check if this texture is valid
	bool IsValid();

	// Check if the texture index is valid
	bool IsIndexValid() { return m_IsIndexValid; }

	// Return the texture index
	uint32_t GetTextureIndex();

	// Return the texture fetch index
	float GetTextureFetchIndex();

private:

	// Calculate the texture indexes
	void CalculateTextureIndexes();

///////////////
// VARIABLES //
private: //////

	// If this image was initialized
	bool m_Initialized;

	// If the texture index was set
	bool m_IsIndexValid;

	// The texture group reference
	Reference::Blob<VWTextureGroup>* m_TextureGroup;

	// The texture index
	uint32_t m_TextureIndex;

	// The texture float index
	float m_TextureFetchIndex;

	// The texture name
	const char* m_TextureName;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)