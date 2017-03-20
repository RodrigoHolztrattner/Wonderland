////////////////////////////////////////////////////////////////////////////////
// Filename: VWImage.h
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

class VWGraphicInstance;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWImage
////////////////////////////////////////////////////////////////////////////////
class VWImage
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWImage();
	~VWImage();

//////////////////
// MAIN METHODS //
public: //////////

	// Release this image
	void Release();

	// Update the image with the given data
	void Update(VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, uint32_t _imageWidth, uint32_t _imageHeight, unsigned char* _imageData);

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

	// Return the format
	VkFormat GetFormat() { return m_Format; }

public:

	// Transition the image layout
	void TransitionImageLayout(VulkanWrapper::VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout);
	void TransitionImageLayout(VulkanWrapper::VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, VkImageLayout oldLayout, VkImageLayout newLayout);

	// Create the image view
	void CreateImageView(VWGraphicInstance* _graphicInstance, VkImageAspectFlags _aspectFlags);
	
	// Create the image sampler
	void CreateImageSampler(VWGraphicInstance* _graphicInstance);

	// Create an image
	void CreateImage(VWGraphicInstance* _graphicInstance, uint32_t _width, uint32_t _height, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties, VkImage& _image, VkDeviceMemory& _imageMemory);
	void CreateImage(VWGraphicInstance* _graphicInstance, uint32_t _width, uint32_t _height, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties);

	// Copy an image
	void CopyImage(VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, VkImage _srcImage, VkImage _dstImage, VkDeviceSize _size);

///////////////
// VARIABLES //
private: //////

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
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)