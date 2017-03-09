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
}

VulkanWrapper::VWWindow::~VWWindow()
{
}

bool VulkanWrapper::VWWindow::Initialize()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_Window = glfwCreateWindow(m_Width, m_Height, "Vulkan", nullptr, nullptr);

	glfwSetWindowUserPointer(m_Window, this);
	// glfwSetWindowSizeCallback(m_Window, HelloTriangleApplication::onWindowResized);

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