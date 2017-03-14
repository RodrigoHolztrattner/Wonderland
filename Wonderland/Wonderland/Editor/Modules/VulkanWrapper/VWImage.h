////////////////////////////////////////////////////////////////////////////////
// Filename: VWTexture.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

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

	// Create this image
	void Create(VWContext* _graphicContext, VkCommandPool _commandPool, char* _filename);

	// Create this image using extended configuration
	void CreateEx(VWContext* _graphicContext, VkCommandPool _commandPool, VkFormat _format, VkImageUsageFlags _usage, char* _filename);

	// Release this image
	void Release();

	// Return if this image was initialized
	bool IsRead();

public:

	// Update the image with the given data
	void Update(VWContext* _graphicContext, VkCommandPool _commandPool, uint32_t _imageWidth, uint32_t _imageHeight, unsigned char* _imageData);

	// Return the image
	VkImage GetRawImage() { return m_Image; }

	// Return the stagging image
	VkImage GetRawStaggingImage() { return m_StaggingImage; }

	// Return the image view
	VkImageView GetImageView() { return m_ImageView; }

	// Return the sampler
	VkSampler GetSampler() { return m_ImageSampler; }

	// Return the image width/height
	uint32_t GetWidth() { return m_Width; }
	uint32_t GetHeight() { return m_Height; }

	// Get/set the texture id
	void SetId(uint32_t _id) { m_TextureId = _id; }
	uint32_t GetId() { return m_TextureId; }

private:

	// Create the image view
	void CreateImageView(VWContext* _graphicContext);

	// Create the image sampler
	void CreateImageSampler(VWContext* _graphicContext);

	// Create an image
	void CreateImage(VWContext* _graphicContext, uint32_t _width, uint32_t _height, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties, VkImage& _image, VkDeviceMemory& _imageMemory);

	// Copy an image
	void CopyImage(VWContext* _graphicContext, VkCommandPool _commandPool, VkImage _srcImage, VkImage _dstImage, VkDeviceSize _size);

///////////////
// VARIABLES //
private: //////

	// If this image was initialized
	bool m_Initialized;

	// Our image object and memory
	VkImage m_Image;
	VkDeviceMemory m_ImageMemory;

	// Our stagging image and memory
	VkImage m_StaggingImage;
	VkDeviceMemory m_StaggingImageMemory;

	// The image view
	VkImageView m_ImageView;

	// The image sampler
	VkSampler m_ImageSampler;

	// The image width and height
	uint32_t m_Width;
	uint32_t m_Height;

	// The image format and usage flags
	VkFormat m_Format;
	VkImageUsageFlags m_UsageFlags;

	//

	uint32_t m_TextureId;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)