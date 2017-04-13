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
	result = m_WidgetShader.Initialize(&m_Context);
	if (!result)
	{
		return false;
	}

	// Initialize our widget manager
	result = m_WidgetManager.Initialize(&m_Context);
	if (!result)
	{
		return false;
	}

	// Initialize the root widget
	m_RootWidget.Initialize();
	m_RootWidget.SetFrame(HookGui::HGFrame(0, 0, m_Context.GetWindow()->GetWidth(), m_Context.GetWindow()->GetHeight()));
	m_RootWidget.CanReceiveInput(false);
	m_RootWidget.CanBeRendered(false);

	//
	{
		// Initialize the alpha object
		result = m_MainWidget.Initialize();
		if (!result)
		{
			return false;
		}

		m_MainWidget.SetFrame(HookGui::HGFrame(0, 200, 640, 280));

		// Get the widget image
		HookGui::HGImage* widgetImage = m_MainWidget.GetImage();

		m_RootWidget.AddSubwidget(&m_MainWidget);

		// Initialize the image
		widgetImage->InitWithSingleImage(&m_Context, "textureGroupSky", "Ground");

		// Initialize the alpha object
		result = m_MenuWidget.Initialize();
		if (!result)
		{
			return false;
		}

		m_MenuWidget.SetFrame(HookGui::HGFrame(0, 100, 640, 100));

		// Get the widget image
		HookGui::HGImage* menuWidgetImage = m_MenuWidget.GetImage();

		m_RootWidget.AddSubwidget(&m_MenuWidget);


		// Initialize the image
		menuWidgetImage->InitWithSingleImage(&m_Context, "textureGroupSky", "Ground");
		
		m_MenuWidget.AddAnchor(&m_MainWidget, HookGui::HGAnchor::Policy::BottomAlign, HookGui::HGAnchor::Modifier::Scale);

		//

		m_MainWidget.AddSubwidget(&m_MenuWidget);
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

	// Do the widget update
	m_WidgetManager.Update(&m_RootWidget, _timeElapsed);

	// Render all widgets
	m_WidgetManager.Render(&m_RootWidget);

	// Check if we are ready to go
	if (!m_WidgetShader.IsValid())
	{
		return;
	}

	// Begin the rendering frame
	m_Context.BeginRenderingFrame();
	
	// Update our renderables
	// m_ObjectAlpha.Update(_timeElapsed, true, false, false);

	// Get the graphic adapter singleton
	VulkanWrapper::GraphicAdapter* graphicAdapter = GlobalInstance<VulkanWrapper::GraphicAdapter>();

	// Get the next image from this swap chain
	uint32_t imageIndex = m_Context.GetSwapChain()->AcquireNextImage(graphicAdapter, m_Context.GetGraphicInstance());

	//

	m_WidgetShader.UpdateUniformBuffer(&m_Context);

	
	m_WidgetShader.AddWidget(&m_MenuWidget);
	m_WidgetShader.AddWidget(&m_MainWidget);

	static float time = 0;
	time += _timeElapsed;

	float inc = std::sin(time) * 50.0f;
	m_MainWidget.SetFrame(HookGui::HGFrame(0, 200 + inc, 640, 280 - inc));
	

	m_WidgetShader.Render(&m_Context, imageIndex);

	//

	VkCommandBuffer commandBuffer = m_WidgetShader.GetCommandBufferReference();

	// Submit the graphic queue
	m_Context.GetSwapChain()->SubmitGraphicQueue(graphicAdapter, m_Context.GetGraphicInstance(), &commandBuffer, 1, imageIndex);

	m_Context.GetSwapChain()->PresentQueue(graphicAdapter, m_Context.GetGraphicInstance(), imageIndex);

	// End the rendering frame
	m_Context.EndRenderingFrame();
}