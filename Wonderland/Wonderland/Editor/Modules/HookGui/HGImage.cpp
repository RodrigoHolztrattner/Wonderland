////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWidget.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGImage.h"

HookGui::HGImage::HGImage()
{
	// Set the initial data
	m_IsValid = false;
	m_IsAnimated = false;
	m_AnimationTotalTime = 1.0f;
	m_CurrentTextureIndex = 0;
}

HookGui::HGImage::~HGImage()
{
}

bool HookGui::HGImage::InitWithSingleImage(VulkanWrapper::Context* _context, const char* _imageGroup, const char* _imageName)
{
	// Get the texture group manager
	VulkanWrapper::TextureGroupManager* textureGroupManager = _context->GetTextureGroupManager();

	// Get the texture group
	textureGroupManager->RequestObject(&m_TextureGroup, _imageGroup);

	// Set the new texture
	VulkanWrapper::Texture newTexture;
	newTexture.CreateWithTextureGroup(&m_TextureGroup, _imageName);

	// Insert the texture
	m_Textures.push_back(newTexture);

	return true;
}

bool HookGui::HGImage::InitWithGroupAnimated(VulkanWrapper::Context* _context, const char* _imageGroup)
{
	// Get the texture group manager
	VulkanWrapper::TextureGroupManager* textureGroupManager = _context->GetTextureGroupManager();

	// Get the texture group
	textureGroupManager->RequestObject(&m_TextureGroup, _imageGroup);

	// Set that we use animation
	m_IsAnimated = true;

	return true;
}

void HookGui::HGImage::AddImageForAnimation(const char* _imageName)
{
	// Set the new texture
	VulkanWrapper::Texture newTexture;
	newTexture.CreateWithTextureGroup(&m_TextureGroup, _imageName);

	// Insert the texture
	m_Textures.push_back(newTexture);
}

void HookGui::HGImage::Update(float _timeElapsed)
{
	// If we dont use animation
	if (!m_IsAnimated)
	{
		return;
	}

	// Increment the time elapsed
	m_AnimationCurrentTime += _timeElapsed;

	// Check if we dont overlap
	while (m_AnimationCurrentTime >= m_AnimationTotalTime)
	{
		// Set the current animation time
		m_AnimationCurrentTime -= m_AnimationTotalTime;
	}

	// Set the current texture index
	m_CurrentTextureIndex = (m_AnimationCurrentTime / m_AnimationTotalTime) * m_Textures.size();
}


bool HookGui::HGImage::IsValid()
{
	// Check if we are valid
	if (m_IsValid)
	{
		return true;
	}

	// Check if the texture group reference is valid
	if (!m_TextureGroup.IsValid())
	{
		return false;
	}

	// Check if the texture group is valid
	if (!m_TextureGroup->IsValid())
	{
		return false;
	}

	// Set that we are valid
	m_IsValid = true;

	return true;
}
