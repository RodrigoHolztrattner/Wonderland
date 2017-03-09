////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWBuffer.h"
#include "VWContext.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

VulkanWrapper::VWBuffer::VWBuffer()
{
	m_Buffer = VK_NULL_HANDLE;
	m_BufferMemory = VK_NULL_HANDLE;
	m_StagingBuffer = VK_NULL_HANDLE;
	m_StagingBufferMemory = VK_NULL_HANDLE;
	m_BufferSize = 0;
	m_Initialized = false;
}

VulkanWrapper::VWBuffer::~VWBuffer()
{
}

void VulkanWrapper::VWBuffer::Create(VWContext* _context, VkBufferUsageFlags _usage, const void* _data, VkDeviceSize _size)
{
	// Set the buffer size
	m_BufferSize = _size;

	// Create the stagging buffer
	CreateBuffer(_context, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_StagingBuffer, m_StagingBufferMemory);

	// Create the normal buffer
	CreateBuffer(_context, _usage | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_BufferMemory);

	// Update the buffer
	Update(_context, _data);

	// Set initialized to true
	m_Initialized = true;
}

void VulkanWrapper::VWBuffer::CreateEx(VWContext* _context, VkBufferUsageFlags _normalUsage, VkBufferUsageFlags _staggingUsage, VkMemoryPropertyFlags _normalProperties, VkMemoryPropertyFlags _staggingProperties, const void* _data, VkDeviceSize _size)
{
	// Set the buffer size
	m_BufferSize = _size;

	// Create the stagging buffer
	CreateBuffer(_context, _normalUsage, _normalProperties, m_StagingBuffer, m_StagingBufferMemory);

	// Create the normal buffer
	CreateBuffer(_context, _staggingUsage, _staggingProperties, m_Buffer, m_BufferMemory);

	// Update the buffer
	Update(_context, _data);

	// Set initialized to true
	m_Initialized = true;
}

void VulkanWrapper::VWBuffer::Update(VWContext* _context, const void* _data)
{
	// Map the memory and get the data ptr
	void* data;
	vkMapMemory(_context->GetGraphicInstance()->GetDevice(), m_StagingBufferMemory, 0, m_BufferSize, 0, &data);

	// Copy the data and unmap the buffer
	memcpy(data, _data, m_BufferSize);
	vkUnmapMemory(_context->GetGraphicInstance()->GetDevice(), m_StagingBufferMemory);

	// Commit the stagging buffer data
	CopyBuffer(_context, m_StagingBuffer, m_Buffer, m_BufferSize);
}

void VulkanWrapper::VWBuffer::Release()
{

}

bool VulkanWrapper::VWBuffer::IsRead()
{
	return m_Initialized;
}

void VulkanWrapper::VWBuffer::CreateBuffer(VWContext* _context, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = m_BufferSize;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(_context->GetGraphicInstance()->GetDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(_context->GetGraphicInstance()->GetDevice(), buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = _context->FindMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(_context->GetGraphicInstance()->GetDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(_context->GetGraphicInstance()->GetDevice(), buffer, bufferMemory, 0);
}

void VulkanWrapper::VWBuffer::CopyBuffer(VulkanWrapper::VWContext* _context, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = _context->GetGraphicInstance()->GetCommandPool();
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(_context->GetGraphicInstance()->GetDevice(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(_context->GetGraphicInstance()->GetGraphicQueue().queue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(_context->GetGraphicInstance()->GetGraphicQueue().queue);

	vkFreeCommandBuffers(_context->GetGraphicInstance()->GetDevice(), _context->GetGraphicInstance()->GetCommandPool(), 1, &commandBuffer);
}
