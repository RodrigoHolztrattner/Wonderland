////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWContextBase.h"
#include "..\..\Peon\Peon.h"

VulkanWrapper::VWContextBase::VWContextBase()
{
	// Set the initial data
	m_IsValid = false;
}

VulkanWrapper::VWContextBase::~VWContextBase()
{
}

uint32_t VulkanWrapper::VWContextBase::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(m_GraphicInstance.GetPhysicalDevice(), &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}