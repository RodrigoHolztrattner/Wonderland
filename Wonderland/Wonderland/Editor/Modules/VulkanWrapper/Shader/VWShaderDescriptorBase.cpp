////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWShaderDescriptorBase.h"
#include "..\Core\VWGraphicAdapter.h"
#include "..\Core\VWSwapChain.h"
#include "..\Core\VWGraphicInstance.h"
#include "..\Renderable\VWRenderable.h"
#include "..\Context\VWContext.h"

VulkanWrapper::VWShaderDescriptorBase::VWShaderDescriptorBase()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWShaderDescriptorBase::~VWShaderDescriptorBase()
{
}

void VulkanWrapper::VWShaderDescriptorBase::AddDescriptorSetLayoutBinding(uint32_t _binding, VkDescriptorType _type, uint32_t _count, VkShaderStageFlags _flags, const VkSampler* _immutableSamplers)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = _binding;
	uboLayoutBinding.descriptorType = _type;
	uboLayoutBinding.descriptorCount = _count;
	uboLayoutBinding.stageFlags = _flags;
	uboLayoutBinding.pImmutableSamplers = _immutableSamplers;

	m_DescriptorSetLayoutBindings.push_back(uboLayoutBinding);
}

VkDescriptorSetLayout VulkanWrapper::VWShaderDescriptorBase::CreateDescriptorSetLayout(VWGraphicInstance* _graphicInstance, VkDescriptorSetLayoutCreateFlags _flags)
{
	VkDescriptorSetLayout descriptorSetLayout = {};
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = m_DescriptorSetLayoutBindings.size();
	layoutInfo.pBindings = m_DescriptorSetLayoutBindings.data();
	layoutInfo.flags = _flags;

	if (vkCreateDescriptorSetLayout(_graphicInstance->GetDevice(), &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}

	return descriptorSetLayout;
}