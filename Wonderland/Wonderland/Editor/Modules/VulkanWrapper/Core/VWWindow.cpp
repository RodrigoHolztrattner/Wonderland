////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWWindow.h"
#include "VWGraphicAdapter.h"
#include "VWSwapChain.h"

VulkanWrapper::VWWindow::VWWindow()
{
	// Set the initial data
	m_IsValid = false;
	m_Window = nullptr;
	m_Width = 640;
	m_Height = 480;
	m_InputCallbackObject = nullptr;
}

VulkanWrapper::VWWindow::~VWWindow()
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Convert our user pointer to the vulkan window type
	VulkanWrapper::VWWindow* vulkanWindow = (VulkanWrapper::VWWindow*)glfwGetWindowUserPointer(window);

	// Get the input callback object
	VulkanWrapper::VWWindowInputCallback* inputCallbackObject = vulkanWindow->GetInputCallbackObject();

	// Check if our input callback object was set
	if (inputCallbackObject == nullptr)
	{	
		// Ignore
		return;
	}

	// Process the input
	inputCallbackObject->ProcessKeyCallback(key, scancode, action, mods);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Convert our user pointer to the vulkan window type
	VulkanWrapper::VWWindow* vulkanWindow = (VulkanWrapper::VWWindow*)glfwGetWindowUserPointer(window);

	// Get the input callback object
	VulkanWrapper::VWWindowInputCallback* inputCallbackObject = vulkanWindow->GetInputCallbackObject();

	// Check if our input callback object was set
	if (inputCallbackObject == nullptr)
	{
		// Ignore
		return;
	}

	// Process the input
	inputCallbackObject->ProcessMouseCallback(button, action, mods);
}

bool VulkanWrapper::VWWindow::Initialize()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_Window = glfwCreateWindow(m_Width, m_Height, "Vulkan", nullptr, nullptr);

	glfwSetWindowUserPointer(m_Window, this);
	// glfwSetWindowSizeCallback(m_Window, HelloTriangleApplication::onWindowResized);

	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);

	// Set is valid
	m_IsValid = true;

	return true;
}

void VulkanWrapper::VWWindow::Release()
{
	glfwDestroyWindow(m_Window);
}

bool VulkanWrapper::VWWindow::IsValid()
{
	return m_IsValid;
}

GLFWwindow* VulkanWrapper::VWWindow::GetWindow()
{
	return m_Window;
}

unsigned int VulkanWrapper::VWWindow::GetWidth()
{
	return m_Width;
}

unsigned int VulkanWrapper::VWWindow::GetHeight()
{
	return m_Height;
}

void VulkanWrapper::VWWindow::SetInputCallbackObject(VWWindowInputCallback* _inputCallbackObject)
{
	m_InputCallbackObject = _inputCallbackObject;
	m_InputCallbackObject->windowReference = m_Window;
}

VulkanWrapper::VWWindowInputCallback* VulkanWrapper::VWWindow::GetInputCallbackObject()
{
	return m_InputCallbackObject;
}