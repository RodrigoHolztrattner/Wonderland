////////////////////////////////////////////////////////////////////////////////
// Filename: FluxApplicationInstance.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ApplicationInstance.h"
#include "Modules\GlobalInstance.h"
#include "Modules\VulkanWrapper\VulkanWrapper.h"

#include <chrono>

ApplicationInstance::ApplicationInstance()
{
	// Set the initial data
	// ...
}

ApplicationInstance::~ApplicationInstance()
{
}

bool ApplicationInstance::Initialize()
{
	bool result;

	// Get the graphic adapter singleton
	VulkanWrapper::GraphicAdapter* graphicAdapter = GlobalInstance<VulkanWrapper::GraphicAdapter>();

	// Get the resource context singleton
	VulkanWrapper::VWResourceContext* resourceContext = GlobalInstance<VulkanWrapper::VWResourceContext>();

	// Initialize our graphic context
	result = m_Context.Initialize(graphicAdapter, resourceContext);
	if (!result)
	{
		return false;
	}

	// Initialize our render shard
	result = m_RenderShard.Initialize(&m_Context);
	if (!result)
	{
		return false;
	}
	
	//
	{
		// Initialize the alpha object
		result = m_ObjectAlpha.Initialize(&m_Context);
		if (!result)
		{
			return false;
		}

		
		// Initialize the beta object
		result = m_ObjectBeta.Initialize(&m_Context);
		if (!result)
		{
			return false;
		}

		// Initialize the gama object
		result = m_ObjectGama.Initialize(&m_Context);
		if (!result)
		{
			return false;
		}
		
	}
	
	// Set is valid
	return m_IsValid = true;
}

void ApplicationInstance::Release()
{

}

void ApplicationInstance::Update(float _timeElapsed)
{
	// Check if we should close this application
	if (glfwWindowShouldClose(m_Context.GetWindow()->GetWindow()))
	{
		// Wait for device
		vkDeviceWaitIdle(m_Context.GetGraphicInstance()->GetDevice());

		// Release this window
		m_Context.GetWindow()->Release();

		// Set is valid to false
		m_IsValid = false;

		return;
	}

	// Begin the rendering frame
	m_Context.BeginRenderingFrame();

	// Update our renderables
	m_ObjectAlpha.Update(_timeElapsed, true, false, false);
	m_ObjectBeta.Update(_timeElapsed, false, true, false);
	m_ObjectGama.Update(_timeElapsed, true, true, false);

	// Get the graphic adapter singleton
	VulkanWrapper::GraphicAdapter* graphicAdapter = GlobalInstance<VulkanWrapper::GraphicAdapter>();

	// Get the next image from this swap chain
	uint32_t imageIndex = m_Context.GetSwapChain()->AcquireNextImage(graphicAdapter, m_Context.GetGraphicInstance());

	//

	m_RenderShard.UpdateUniformBuffer(&m_Context, &m_ObjectAlpha);

	m_RenderShard.AddRenderable(&m_ObjectAlpha);
	m_RenderShard.AddRenderable(&m_ObjectBeta);
	m_RenderShard.AddRenderable(&m_ObjectGama);

	m_RenderShard.RenderOpaqueGeometry(&m_Context, imageIndex);

	//

	VkCommandBuffer commandBuffer = m_RenderShard.GetCommandBufferReference();

	// Submit the graphic queue
	m_Context.GetSwapChain()->SubmitGraphicQueue(graphicAdapter, m_Context.GetGraphicInstance(), &commandBuffer, 1, imageIndex);

	m_Context.GetSwapChain()->PresentQueue(graphicAdapter, m_Context.GetGraphicInstance(), imageIndex);

	// End the rendering frame
	m_Context.EndRenderingFrame();
}