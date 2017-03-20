////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTexture.h"
#include "..\..\VWContext.h"
#include <cmath>

VulkanWrapper::VWTexture::VWTexture()
{
	// Set the initial data
	m_Initialized = false;
	m_IsIndexValid = false;
}

VulkanWrapper::VWTexture::~VWTexture()
{
}

void VulkanWrapper::VWTexture::CreateWithTextureGroup(Reference::Blob<VWTextureGroup>* _textureGroup, const char* _textureName)
{
	// Set the data
	m_TextureGroup = _textureGroup;

	// Set the name
	m_TextureName = _textureName;

	// Set initialized
	m_Initialized = true;
}

bool VulkanWrapper::VWTexture::IsValid()
{
	// Check if we are initialized
	if (!m_Initialized)
	{
		return false;
	}

	// Check if the texture group is valid
	if (!m_TextureGroup->IsValid())
	{
		return false;
	}

	// Check the texture group status
	if (m_TextureGroup->GetResource()->GetStatus() != Hoard::Supply::Object::Status::Initialized)
	{
		return false;
	}
	
	// Check if the resource inside the texture reference is valid
	if (!(*m_TextureGroup)->GetResourceReference()->IsValid())
	{
		return false;
	}

	// Check the resource inside the texture reference status
	if ((*m_TextureGroup)->GetResourceReference()->GetResource()->GetStatus() != Hoard::Resource::ResourceStatus::Initialized)
	{
		return false;
	}

	return true;
}

uint32_t VulkanWrapper::VWTexture::GetTextureIndex()
{
	// Check if the index is valid
	if (m_IsIndexValid)
	{
		return m_TextureIndex;
	}

	// Calculate the indexes
	CalculateTextureIndexes();

	return m_TextureIndex;
}

float VulkanWrapper::VWTexture::GetTextureFetchIndex()
{
	// Check if the index is valid
	if (m_IsIndexValid)
	{
		return m_TextureIndex;
	}

	// Calculate the indexes
	CalculateTextureIndexes();

	return m_TextureFetchIndex;
}

void VulkanWrapper::VWTexture::CalculateTextureIndexes()
{
	// Check if we are initialized
	if (!m_Initialized)
	{
		m_IsIndexValid = -1;
		m_TextureFetchIndex = -1;
		return;
	}

	// Check if we are valid
	if (!IsValid())
	{
		m_IsIndexValid = -1;
		m_TextureFetchIndex = -1;
		return;
	}

	// Get the texture group object
	VWTextureGroup* textureGroup = m_TextureGroup->GetResource();

	// Find the texture index
	m_TextureIndex = textureGroup->FindTextureIndex(m_TextureName);
	if (m_TextureIndex != -1)
	{
		// Calculate the fetch index
		// m_TextureFetchIndex = std::max(0.0f, std::min(d - 1.0f, std::floor(layer + 0.5f)));
		m_TextureFetchIndex = m_TextureIndex;

		// The index is valid
		m_IsIndexValid = true;
	}
}