////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroupManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "VWDescriptorSetCreator.h"
#include "VWTextureGroup.h"

#include <vector>
#include <map>
#include <array>
#include <list>

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
class VWTexture;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWTextureGroupManager
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupManager : public VWDescriptorSetCreator
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroupManager();
	~VWTextureGroupManager();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize(VWContext* _graphicContext);

	// Release this image
	void Release();

public:
	
	// Request a texture group
	void RequestTextureGroup(VWTextureGroupReference* _textureGroupReference, uint32_t _groupIdentifier, std::function<void()> _onLoadCallback);
	void RequestTextureGroup(VWTextureGroupReference* _textureGroupReference, std::string _groupName, std::function<void()> _onLoadCallback);


	VWTexture* GetTexture(VWContext* _graphicContext, std::string _textureName, std::string _textureGroup);

private:
public:

	// Get/find a texture group
	VWTextureGroup* GetTextureGroup(std::string _textureGroup) { return FindTextureGroup(_textureGroup); }
	VWTextureGroup* FindTextureGroup(std::string _textureGroup);

	// Create a texture
	VWTexture* CreateTexture(VWContext* _graphicContext, std::string _textureName, VkCommandPool _commandPool);

///////////////
// VARIABLES //
private: //////

	// Our texture groups
	std::map<std::string, VWTextureGroup> m_TextureGroups;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)