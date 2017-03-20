////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWGraphicAdapter.h"
#include "VWSwapChain.h"
#include "VWWindow.h"
#include "VWGraphicInstance.h"

VulkanWrapper::VWGraphicAdapter::VWGraphicAdapter()
{
	// Set the initial data
	m_VulkanInstance = VK_NULL_HANDLE;
	callback = VK_NULL_HANDLE;
}

VulkanWrapper::VWGraphicAdapter::~VWGraphicAdapter()
{
}

bool VulkanWrapper::VWGraphicAdapter::Initialize()
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

VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

bool VulkanWrapper::VWGraphicAdapter::CreateVulkanInstance(const char* _applicationName, const char* _engineName, uint32_t _applicationVersion, uint32_t _engineVersion)
{
	if (enableValidationLayers && !CheckValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	// Set the app info
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = _applicationName;
	appInfo.applicationVersion = _applicationVersion;
	appInfo.pEngineName = _engineName;
	appInfo.engineVersion = _engineVersion;
	appInfo.apiVersion = VK_API_VERSION_1_0;

	// Set the create info
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = GetRequiredExtensions();
	createInfo.enabledExtensionCount = extensions.size();
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidationLayers) 
	{
		createInfo.enabledLayerCount = validationLayers.size();
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&createInfo, nullptr, &m_VulkanInstance) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create instance!");
	}

	return true;
}

void VulkanWrapper::VWGraphicAdapter::SetupDebugCallback()
{
	if (!enableValidationLayers) return;

	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = debugCallback;

	if (CreateDebugReportCallbackEXT(m_VulkanInstance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug callback!");
	}
}

//
// HELPERS
//

bool VulkanWrapper::VWGraphicAdapter::CheckValidationLayerSupport()
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

std::vector<const char*> VulkanWrapper::VWGraphicAdapter::GetRequiredExtensions()
{
	std::vector<const char*> extensions;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (unsigned int i = 0; i < glfwExtensionCount; i++) { // acessa isso sem ter iniciado a window
		extensions.push_back(glfwExtensions[i]);
	}

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	return extensions;
}
