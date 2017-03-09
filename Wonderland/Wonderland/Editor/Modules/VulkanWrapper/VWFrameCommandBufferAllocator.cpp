////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWFrameCommandBufferAllocator.h"
#include "VWSwapChain.h"
#include "VWWindow.h"
#include "VWGraphicAdapter.h"
#include "VWGraphicInstance.h"

VulkanWrapper::VWFrameCommandBufferAllocator::VWFrameCommandBufferAllocator()
{
	// Set the initial data
	m_TotalFrameMagnitude = 0;
	m_CurrentFrameMagnitude = 0;
}

VulkanWrapper::VWFrameCommandBufferAllocator::~VWFrameCommandBufferAllocator()
{
}

bool VulkanWrapper::VWFrameCommandBufferAllocator::Initialize(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, uint32_t _totalThreads, uint32_t _bufferingMagnitude)
{
	// Set the total frame magnitude
	m_TotalFrameMagnitude = _bufferingMagnitude;

	// Query the family indices
	VWGraphicInstance::QueueFamilyIndices queueFamilyIndices = _graphicInstance->FindQueueFamilies(_graphicInstance->GetPhysicalDevice(), _graphicInstance->GetSurface());

	// For each thread
	for (int i = 0; i < _totalThreads; i++)
	{
		// The per thread data
		CommandDataPerThread perThreadData = {};

		// Buffer magnitude
		for (int j = 0; j < _bufferingMagnitude; j++)
		{
			CommandPoolAux commandPoolAux = {};
			commandPoolAux.sTargetCommandBuffer = 0;

			VkCommandPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.flags = 0;
			poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;

			if (vkCreateCommandPool(_graphicInstance->GetDevice(), &poolInfo, nullptr, &commandPoolAux.sCommandPool) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create command pool!");
			}
			
			perThreadData.sCommandPoolAux.push_back(commandPoolAux);
		}

		m_ThreadCommandData.push_back(perThreadData);
	}

	// Create all command pools
	// CreateCommandPool(_adapter, _graphicInstance, 0);
	// CreateCommandPool(_adapter, _graphicInstance, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	// CreateCommandPool(_adapter, _graphicInstance, VK_COMMAND_POOL_CREATE_TRANSIENT_BIT);
	// CreateCommandPool(_adapter, _graphicInstance, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT | VK_COMMAND_POOL_CREATE_TRANSIENT_BIT);

	return true;
}

VkCommandBuffer VulkanWrapper::VWFrameCommandBufferAllocator::CreateFrameCommandBuffer(VWGraphicInstance* _graphicInstance, VkCommandBufferLevel _level, uint32_t _threadIndex)
{
	// Get the thread command data
	CommandDataPerThread& threadCommandData = m_ThreadCommandData[_threadIndex];
	
	// Check if we dont need to create a new command buffer
	if (threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sTargetCommandBuffer < threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sValidCommandBuffers.size())
	{
		uint32_t commandBufferIndex = threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sTargetCommandBuffer;
		threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sTargetCommandBuffer++;
		return threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sValidCommandBuffers[commandBufferIndex];
	}

	VkCommandBuffer commandBuffer = {};
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sCommandPool;
	allocInfo.level = _level;
	allocInfo.commandBufferCount = 1;
	
	if (vkAllocateCommandBuffers(_graphicInstance->GetDevice(), &allocInfo, &commandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}

	// Insert the command buffer into the command buffer array
	threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sValidCommandBuffers.push_back(commandBuffer);
	threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sTargetCommandBuffer++;

	return commandBuffer;
}

void VulkanWrapper::VWFrameCommandBufferAllocator::ResetCommandBuffers(VWGraphicInstance* _graphicInstance)
{
	// Increment the current frame
	m_CurrentFrameMagnitude++;
	if (m_CurrentFrameMagnitude >= m_TotalFrameMagnitude)
	{
		m_CurrentFrameMagnitude = 0;
	}

	// For each thread data
	for (auto& threadCommandData : m_ThreadCommandData)
	{
		// Reset all command buffers from this command pool
		vkResetCommandPool(_graphicInstance->GetDevice(), threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sCommandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
		threadCommandData.sCommandPoolAux[m_CurrentFrameMagnitude].sTargetCommandBuffer = 0;
	}
}