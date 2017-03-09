////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWShaderCommandBase.h"
#include "..\VWContext.h"

VulkanWrapper::VWShaderCommandBase::VWShaderCommandBase()
{
	// Set the initial data
	m_UseCustomCommandPoolAllocator = false;
}

VulkanWrapper::VWShaderCommandBase::~VWShaderCommandBase()
{
}

VkCommandBuffer VulkanWrapper::VWShaderCommandBase::CreateCommandBuffer(VWContext* _context, VkCommandBufferLevel _level, VkCommandPoolCreateFlags _flags)
{
	// Check if we can create more command buffers
	if (m_UseCustomCommandPoolAllocator)
	{
		throw std::runtime_error("shader cant create more custom command buffers!");
	}

	// Create the command pool
	CreateCommandPool(_context, _flags);

	// Set the command buffer alloc info
	VkCommandBuffer commandBuffer = {};
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_CommandPool;
	allocInfo.level = _level;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(_context->GetGraphicInstance()->GetDevice(), &allocInfo, &commandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}

	// We are using the custom command pool allocator
	m_UseCustomCommandPoolAllocator = true;

	return commandBuffer;
}

std::vector<VkCommandBuffer> VulkanWrapper::VWShaderCommandBase::CreateCommandBuffer(VWContext* _context, VkCommandBufferLevel _level, VkCommandPoolCreateFlags _flags, uint32_t _amount)
{
	// Check if we can create more command buffers
	if (m_UseCustomCommandPoolAllocator)
	{
		throw std::runtime_error("shader cant create more custom command buffers!");
	}

	// Create the command pool
	CreateCommandPool(_context, _flags);

	// Prepare the command buffer vector
	std::vector<VkCommandBuffer> commandBuffers = {};
	commandBuffers.resize(_amount);

	// Set the command buffer alloc info
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_CommandPool;
	allocInfo.level = _level;
	allocInfo.commandBufferCount = _amount;

	if (vkAllocateCommandBuffers(_context->GetGraphicInstance()->GetDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}

	// We are using the custom command pool allocator
	m_UseCustomCommandPoolAllocator = true;

	return commandBuffers;
}

void VulkanWrapper::VWShaderCommandBase::CreateCommandPool(VWContext* _context, VkCommandPoolCreateFlags _flags)
{
	// Query the family indices
	VWGraphicInstance::QueueFamilyIndices queueFamilyIndices = _context->GetGraphicInstance()->FindQueueFamilies(_context->GetGraphicInstance()->GetPhysicalDevice(), _context->GetGraphicInstance()->GetSurface());

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = _flags;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;

	if (vkCreateCommandPool(_context->GetGraphicInstance()->GetDevice(), &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}