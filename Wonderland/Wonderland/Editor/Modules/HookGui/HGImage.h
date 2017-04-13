////////////////////////////////////////////////////////////////////////////////
// Filename: HGImage.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "..\VulkanWrapper\VulkanWrapper.h"

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

// HookGui workspace
NamespaceBegin(HookGui)

////////////////
// FORWARDING //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HGImage
////////////////////////////////////////////////////////////////////////////////
class HGImage
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGImage();
	~HGImage();
 
////////////////////
// INITIALIZATION //
public: ////////////
    
    // Initialize the image with a single
    bool InitWithSingleImage(VulkanWrapper::Context* _context, const char* _imageGroup, const char* _imageName);

	// Initialize the image to use an animation
	bool InitWithGroupAnimated(VulkanWrapper::Context* _context, const char* _imageGroup);

	// Add an image from the current group to the animation table
	void AddImageForAnimation(const char* _imageName);

	// Set the animation time
	void SetAnimationTime(float _animationTime) { m_AnimationTotalTime = _animationTime; }

	// Update this image
	void Update(float _timeElapsed);

public:

	// Return the texture group reference
	VulkanWrapper::TextureGroup* GetTextureGroupReference() { return m_TextureGroup.GetResource(); }

	// Return the texture
	VulkanWrapper::Texture GetTexture() { return m_Textures[m_CurrentTextureIndex]; }

	// If this image is valid to be used
	bool IsValid();
    
///////////////
// VARIABLES //
private: //////
    
	// The image texture group
	VulkanWrapper::TextureGroupReference m_TextureGroup;
 
	// All the textures we will use
	std::vector<VulkanWrapper::Texture> m_Textures;

	// The current texture index
	uint32_t m_CurrentTextureIndex;

	// The animation total and current times
	float m_AnimationTotalTime;
	float m_AnimationCurrentTime;

	// If this image is valid (short verification)
	bool m_IsValid;

	// If we are animated
	bool m_IsAnimated;
};

// HookGui workspace
NamespaceEnd(HookGui)
