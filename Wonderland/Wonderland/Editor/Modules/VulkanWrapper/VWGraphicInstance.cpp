////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWGraphicInstance.h"
#include "VWSwapChain.h"
#include "VWWindow.h"
#include "VWGraphicAdapter.h"

VulkanWrapper::VWGraphicInstance::VWGraphicInstance()
{
	// Set the initial data
	m_VulkanDevice = VK_NULL_HANDLE;
	m_Surface = VK_NULL_HANDLE;
	m_GraphicsQueue.queue = VK_NULL_HANDLE;
	m_PresentQueue.queue = VK_NULL_HANDLE;
}

VulkanWrapper::VWGraphicInstance::~VWGraphicInstance()
{
}

bool VulkanWrapper::VWGraphicInstance::Initialize()
{
	return true;
}

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

std::vector<const char*> VulkanWrapper::VWGraphicInstance::deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

void VulkanWrapper::VWGraphicInstance::CreateSurface(VWGraphicAdapter* _adapter, VWWindow* _window)
{
	// Create the window surface
	VkInstance instance = _adapter->GetInstanceAdapter();
	VkResult result = glfwCreateWindowSurface(_adapter->GetInstanceAdapter(), _window->GetWindow(), nullptr, &m_Surface);
	if (glfwCreateWindowSurface(_adapter->GetInstanceAdapter(), _window->GetWindow(), nullptr, &m_Surface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface!");
	}
}

void VulkanWrapper::VWGraphicInstance::CreateSuitablePhysicalDevice(VWGraphicAdapter* _adapter)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(_adapter->GetInstanceAdapter(), &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(_adapter->GetInstanceAdapter(), &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (VWSwapChain::IsDeviceSuitable(device, this, m_Surface))
		{
			m_PhysicalDevice = device;
			break;
		}
	}

	if (m_PhysicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

void VulkanWrapper::VWGraphicInstance::CreateLogicalDevice(VWGraphicAdapter* _adapter)
{
	QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice, m_Surface);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

	float queuePriority = 1.0f;
	for (int queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = deviceExtensions.size();
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = validationLayers.size();
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_VulkanDevice) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(m_VulkanDevice, indices.graphicsFamily, 0, &m_GraphicsQueue.queue);
	vkGetDeviceQueue(m_VulkanDevice, indices.presentFamily, 0, &m_PresentQueue.queue);
	m_GraphicsQueue.index = indices.graphicsFamily;
	m_PresentQueue.index = indices.presentFamily;
}

void VulkanWrapper::VWGraphicInstance::CreateCommandPool(VWGraphicAdapter* _adapter)
{
	QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(m_PhysicalDevice, m_Surface);

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;

	if (vkCreateCommandPool(m_VulkanDevice, &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}

VulkanWrapper::VWGraphicInstance::QueueFamilyIndices VulkanWrapper::VWGraphicInstance::FindQueueFamilies(VkPhysicalDevice _device, VkSurfaceKHR _surface)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(_device, i, _surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}


bool VulkanWrapper::VWGraphicInstance::CheckDeviceExtensionSupport(VkPhysicalDevice m_VulkanDevice)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(m_VulkanDevice, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(m_VulkanDevice, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

//
// HELPERS
//

bool VulkanWrapper::VWGraphicInstance::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

std::vector<const char*> VulkanWrapper::VWGraphicInstance::GetRequiredExtensions()
{
	std::vector<const char*> extensions;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (unsigned int i = 0; i < glfwExtensionCount; i++) {
		extensions.push_back(glfwExtensions[i]);
	}

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	return extensions;
}
