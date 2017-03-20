////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWCoreUtils.h"

VulkanWrapper::VWCoreUtils::VWCoreUtils()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWCoreUtils::~VWCoreUtils()
{
}

uint32_t VulkanWrapper::VWCoreUtils::FindMemoryType(VWGraphicInstance* _graphicInstance, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(_graphicInstance->GetPhysicalDevice(), &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}