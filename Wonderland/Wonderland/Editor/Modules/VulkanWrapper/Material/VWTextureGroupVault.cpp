////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroupVault.h"
#include "..\VWContext.h"

VulkanWrapper::VWTextureGroupVault::VWTextureGroupVault()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWTextureGroupVault::~VWTextureGroupVault()
{
}

bool VulkanWrapper::VWTextureGroupVault::Initialize()
{

	return true;
}

VulkanWrapper::VWTextureGroup* VulkanWrapper::VWTextureGroupVault::IsTextureGroupLoaded(HashedStringIdentifier _textureGroupIdentifier)
{
	// For each texture group loaded
	for (auto& textureGroupHolder : m_TextureGroups)
	{
		// Compare the resource paths
		if (!textureGroupHolder.resourceGroupIdentifier == _textureGroupIdentifier)
		{
			return textureGroupHolder.textureGroup;
		}
	}

	return nullptr;
}

void VulkanWrapper::VWTextureGroupVault::InsertTextureGroup(VWTextureGroup* _textureGroup, HashedStringIdentifier _textureGroupIdentifier)
{
	TextureGroupHolder textureGroupHolder = {};
	textureGroupHolder.textureGroup = _textureGroup;
	textureGroupHolder.resourceGroupIdentifier = _textureGroupIdentifier;

	m_TextureGroups.push_back(textureGroupHolder);
}

