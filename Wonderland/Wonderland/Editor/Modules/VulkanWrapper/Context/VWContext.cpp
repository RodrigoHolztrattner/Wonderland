////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWContext.h"
#include "..\..\Peon\Peon.h"
#include "VWResourceContext.h"

VulkanWrapper::VWContext::VWContext()
{
	// Set the initial data
	m_IsValid = false;
}

VulkanWrapper::VWContext::~VWContext()
{
}

bool VulkanWrapper::VWContext::Initialize(VWGraphicAdapter* _adapter, VWResourceContext* _resourceContext)
{
	bool result;

	// Save our adapter reference
	m_GraphicAdapterReference = _adapter;

	// Save our resource context
	m_ResourceContextReference = _resourceContext;

	// Initialize our m_Window
	result = m_Window.Initialize();
	if (!result)
	{
		return false;
	}

	// Initialize our swap chain
	result = m_SwapChain.Initialize();
	if (!result)
	{
		return false;
	}

	// Initialize our graphic instance
	result = m_GraphicInstance.Initialize();
	if (!result)
	{
		return false;
	}

	// Create the surface
	m_GraphicInstance.CreateSurface(_adapter, &m_Window);

	// Create the physical device
	m_GraphicInstance.CreateSuitablePhysicalDevice(_adapter);

	// Create the logical device
	m_GraphicInstance.CreateLogicalDevice(_adapter);

	// Create the command pool
	m_GraphicInstance.CreateCommandPool(_adapter);

	// Create our swap chain
	m_SwapChain.CreateSwapChain(_adapter, &m_Window, &m_GraphicInstance);

	// Create the swap chain image views
	m_SwapChain.CreateImageViews(_adapter, &m_GraphicInstance);

	// Create the depth resources
	m_SwapChain.CreateDepthResources(&m_GraphicInstance);

	// Create the semaphores
	m_SwapChain.CreateSemaphores(_adapter, &m_GraphicInstance);

	// Create the background cleaner
	m_SwapChain.CreateBackgroundCleaner(_adapter, &m_GraphicInstance);
	
	// Initialize the command buffer allocator
	result = m_CommandBufferAllocator.Initialize(_adapter, &m_GraphicInstance, Peon::GetTotalWorkers(), 3);
	if (!result)
	{
		return false;
	}

	// Initialize the texture group manager
	result = m_TextureGroupManager.Initialize(_resourceContext->GetTextureGroupIndexLoader(), Peon::GetTotalWorkers());
	if (!result)
	{
		return false;
	}

	// Initialize the model manager
	result = m_ModelManager.Initialize(_resourceContext->GetModelIndexLoader(), Peon::GetTotalWorkers());
	if (!result)
	{
		return false;
	}

	// Create the descriptor layout for the texture group manager
	m_TextureGroupManager.CreateDescriptorLayout(this);

	// Set the context reference for the model manager
	m_ModelManager.SetContextReference(this);

	// Set is valid
	return m_IsValid = true;
}

VkCommandBuffer VulkanWrapper::VWContext::GetValidFrameCommandBuffer(VkCommandBufferLevel _level)
{
	return m_CommandBufferAllocator.CreateFrameCommandBuffer(&m_GraphicInstance, _level, Peon::GetCurrentWorkerIndex());
}

void VulkanWrapper::VWContext::Release()
{
	
}

void VulkanWrapper::VWContext::BeginRenderingFrame()
{

}

void VulkanWrapper::VWContext::EndRenderingFrame()
{
	// Reset the command buffers
	m_CommandBufferAllocator.ResetCommandBuffers(&m_GraphicInstance);
}

void VulkanWrapper::VWContext::ApplicationUpdate()
{
	m_TextureGroupManager.ProcessRequestQueues(m_ResourceContextReference->GetResourceManager());
	m_ModelManager.ProcessRequestQueues(m_ResourceContextReference->GetResourceManager());
}