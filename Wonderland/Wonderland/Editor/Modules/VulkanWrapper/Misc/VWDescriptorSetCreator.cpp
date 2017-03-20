////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWDescriptorSetCreator.h"
#include "..\Context\VWContext.h"

VulkanWrapper::VWDescriptorSetCreator::VWDescriptorSetCreator()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWDescriptorSetCreator::~VWDescriptorSetCreator()
{
}

void VulkanWrapper::VWDescriptorSetCreator::CreateDescriptorPool(VWContext* _graphicContext, uint32_t _maxSets)
{
	std::vector<VkDescriptorPoolSize> poolSizes;
	for (auto layoutBinding : m_DescriptorSetLayoutBindings)
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = layoutBinding.descriptorType;
		poolSize.descriptorCount = layoutBinding.descriptorCount;

		poolSizes.push_back(poolSize);
	}

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = poolSizes.size();
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = _maxSets;

	if (vkCreateDescriptorPool(_graphicContext->GetGraphicInstance()->GetDevice(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void VulkanWrapper::VWDescriptorSetCreator::AddDescriptorSetLayoutBinding(uint32_t _binding, VkDescriptorType _type, uint32_t _count, VkShaderStageFlags _flags, const VkSampler* _immutableSamplers)
{
	VkDescriptorSetLayoutBinding bindingInfo = {};
	bindingInfo.binding = _binding;
	bindingInfo.descriptorType = _type;
	bindingInfo.descriptorCount = _count;
	bindingInfo.stageFlags = _flags;
	bindingInfo.pImmutableSamplers = _immutableSamplers;

	m_DescriptorSetLayoutBindings.push_back(bindingInfo);
}

void VulkanWrapper::VWDescriptorSetCreator::CreateDescriptorSetLayout(VWContext* _graphicContext, VkDescriptorSetLayoutCreateFlags _flags)
{
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = m_DescriptorSetLayoutBindings.size();
	layoutInfo.pBindings = m_DescriptorSetLayoutBindings.data();
	layoutInfo.flags = _flags;

	if (vkCreateDescriptorSetLayout(_graphicContext->GetGraphicInstance()->GetDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}