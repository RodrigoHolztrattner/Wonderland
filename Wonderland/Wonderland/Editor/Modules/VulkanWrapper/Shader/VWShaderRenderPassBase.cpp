////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWShaderRenderPassBase.h"
#include "..\Context\VWContext.h"

VulkanWrapper::VWShaderRenderPassBase::VWShaderRenderPassBase()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWShaderRenderPassBase::~VWShaderRenderPassBase()
{
}

VulkanWrapper::VWShaderRenderPassBase::RenderPass VulkanWrapper::VWShaderRenderPassBase::StartRenderPass()
{
	// Prepare the return render pass
	RenderPass renderPassIdentifier = {};
	renderPassIdentifier.id = m_RenderPasses.size();

	// Set the initial data
	RenderPassInternal newRenderPass = {};

	// Insert into the array
	m_RenderPasses.push_back(newRenderPass);

	return renderPassIdentifier;
}

VulkanWrapper::VWShaderRenderPassBase::SubPass VulkanWrapper::VWShaderRenderPassBase::StartSubPass(RenderPass _renderPass, VkPipelineBindPoint _bindPoint, VkSubpassDescriptionFlags _flags)
{
	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_renderPass.id];

	// Prepare the return sub pass
	SubPass subPassIdentifier = {};
	subPassIdentifier.id = renderPass.subPasses.size();
	subPassIdentifier.isExternal = false;
	subPassIdentifier.renderPassId = _renderPass.id;

	// Set the sub pass data
	SubPassInternal newSubPass = {};
	newSubPass.description.pipelineBindPoint = _bindPoint;
	newSubPass.description.flags = _flags;

	// Add to the renderpass
	renderPass.subPasses.push_back(newSubPass);

	return subPassIdentifier;
}

void VulkanWrapper::VWShaderRenderPassBase::AddDependency(RenderPass _renderPass, SubPass _srcSubpass, SubPass _dstSubpass, VkPipelineStageFlags _srcStageMask, VkPipelineStageFlags _dstStageMask, VkAccessFlags _srcAcessFlags, VkAccessFlags _dstAcessFlags)
{
	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_renderPass.id];

	VkSubpassDependency dependency = {};
	if (_srcSubpass.isExternal)
	{
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	}
	else
	{
		dependency.srcSubpass = _srcSubpass.id;
	}
	dependency.dstSubpass = _dstSubpass.id;
	dependency.srcStageMask = _srcStageMask;
	dependency.srcAccessMask = _dstStageMask;
	dependency.dstStageMask = _srcAcessFlags;
	dependency.dstAccessMask = _dstAcessFlags;

	renderPass.dependencies.push_back(dependency);
}

void VulkanWrapper::VWShaderRenderPassBase::AddInputAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout)
{
	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_subPass.renderPassId];

	// Get the internal sub pass
	SubPassInternal& subPass = renderPass.subPasses[_subPass.id];

	// Prepare the attachment
	VkAttachmentReference attachmentRef = {};
	attachmentRef.attachment = _attachment.id;
	attachmentRef.layout = _layout;

	subPass.inputAttachmentReference.push_back(attachmentRef);
}

void VulkanWrapper::VWShaderRenderPassBase::AddColorAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout)
{
	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_subPass.renderPassId];

	// Get the internal sub pass
	SubPassInternal& subPass = renderPass.subPasses[_subPass.id];

	// Prepare the attachment
	VkAttachmentReference attachmentRef = {};
	attachmentRef.attachment = _attachment.id;
	attachmentRef.layout = _layout;

	subPass.colorAttachmentReference.push_back(attachmentRef);
}

void VulkanWrapper::VWShaderRenderPassBase::AddResolveAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout)
{
	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_subPass.renderPassId];

	// Get the internal sub pass
	SubPassInternal& subPass = renderPass.subPasses[_subPass.id];

	// Prepare the attachment
	VkAttachmentReference attachmentRef = {};
	attachmentRef.attachment = _attachment.id;
	attachmentRef.layout = _layout;

	subPass.resolveAttachmentReference.push_back(attachmentRef);
}

void VulkanWrapper::VWShaderRenderPassBase::SetDepthAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout)
{
	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_subPass.renderPassId];

	// Get the internal sub pass
	SubPassInternal& subPass = renderPass.subPasses[_subPass.id];

	// Prepare the attachment
	VkAttachmentReference attachmentRef = {};
	attachmentRef.attachment = _attachment.id;
	attachmentRef.layout = _layout;

	subPass.depthAtencilAttachmentReference = attachmentRef;
}

bool VulkanWrapper::VWShaderRenderPassBase::CreateSubpass(SubPassInternal& subPass)
{
	// Set the descriptor data
	subPass.description.inputAttachmentCount = subPass.inputAttachmentReference.size();
	subPass.description.pInputAttachments = subPass.inputAttachmentReference.data();
	subPass.description.colorAttachmentCount = subPass.colorAttachmentReference.size();
	subPass.description.pColorAttachments = subPass.colorAttachmentReference.data();
	subPass.description.pResolveAttachments = subPass.resolveAttachmentReference.data();
	subPass.description.pDepthStencilAttachment = &subPass.depthAtencilAttachmentReference;
	subPass.description.preserveAttachmentCount = subPass.preserveAttachments.size();
	subPass.description.pPreserveAttachments = subPass.preserveAttachments.data();

	// Check if all the subpass data is valid
	// ...

	return true;
}

VulkanWrapper::VWShaderRenderPassBase::ColorAttachmentDescription VulkanWrapper::VWShaderRenderPassBase::CreateColorAttachmentDescriptor(RenderPass _renderPass, VkFormat _format, VkSampleCountFlagBits _samples, VkAttachmentLoadOp _loadOp, VkAttachmentStoreOp _storeOp, VkImageLayout _initialLayout, VkImageLayout _finalLayout)
{
	// Create the new attachment descriptor
	uint32_t attachmentId = AddAttachmentDescriptor(_renderPass, _format, _samples, _loadOp, _storeOp, VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE, _initialLayout, _finalLayout);

	// Create the new attachment
	AttachmentDescription newAttachmentDescription = {};
	newAttachmentDescription.id = attachmentId;

	return newAttachmentDescription;
}

VulkanWrapper::VWShaderRenderPassBase::DepthAttachmentDescription VulkanWrapper::VWShaderRenderPassBase::CreateDepthAttachmentDescriptor(RenderPass _renderPass, VkFormat _format, VkSampleCountFlagBits _samples, VkAttachmentLoadOp _loadOp, VkAttachmentStoreOp _storeOp, VkAttachmentLoadOp _stencilLoadOp, VkAttachmentStoreOp _stencilStoreOp, VkImageLayout _initialLayout, VkImageLayout _finalLayout)
{
	// Create the new attachment descriptor
	uint32_t attachmentId = AddAttachmentDescriptor(_renderPass, _format, _samples, _loadOp, _storeOp, _stencilLoadOp, _stencilStoreOp, _initialLayout, _finalLayout);

	// Create the new attachment
	AttachmentDescription newAttachmentDescription = {};
	newAttachmentDescription.id = attachmentId;

	return newAttachmentDescription;
}

uint32_t VulkanWrapper::VWShaderRenderPassBase::AddAttachmentDescriptor(RenderPass _renderPass, VkFormat _format, VkSampleCountFlagBits _samples, VkAttachmentLoadOp _loadOp, VkAttachmentStoreOp _storeOp, VkAttachmentLoadOp _stencilLoadOp, VkAttachmentStoreOp _stencilStoreOp, VkImageLayout _initialLayout, VkImageLayout _finalLayout)
{
	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_renderPass.id];

	VkAttachmentDescription attachment = {};
	attachment.format = _format;
	attachment.samples = _samples;
	attachment.loadOp = _loadOp;
	attachment.storeOp = _storeOp;
	attachment.stencilLoadOp = _stencilLoadOp;
	attachment.stencilStoreOp = _stencilStoreOp;
	attachment.initialLayout = _initialLayout;
	attachment.finalLayout = _finalLayout;

	renderPass.attachmentDescriptors.push_back(attachment);

	return renderPass.attachmentDescriptors.size() - 1;
}

VkRenderPass VulkanWrapper::VWShaderRenderPassBase::CreateRenderPass(VWGraphicInstance* _graphicInstance, RenderPass _renderPass)
{
	VkRenderPass renderPassObject = {};

	// Get the internal render pass
	RenderPassInternal& renderPass = m_RenderPasses[_renderPass.id];

	// Create each sub pass
	for (int i = 0; i < renderPass.subPasses.size(); i++)
	{
		// Create this subpass
		bool result = CreateSubpass(renderPass.subPasses[i]);
		if (!result)
		{
			throw std::runtime_error("failed to create render pass!");
		
			// Error!
			return renderPassObject;
		}
	}

	// Prepare the subpass data
	std::vector<VkSubpassDescription> subPassDescriptions;
	for (auto& subPassData : renderPass.subPasses)
	{
		subPassDescriptions.push_back(subPassData.description);
	}

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = renderPass.attachmentDescriptors.size();
	renderPassInfo.pAttachments = renderPass.attachmentDescriptors.data();
	renderPassInfo.subpassCount = subPassDescriptions.size();
	renderPassInfo.pSubpasses = subPassDescriptions.data();
	renderPassInfo.dependencyCount = renderPass.dependencies.size();
	renderPassInfo.pDependencies = renderPass.dependencies.data();

	// Create the new render pass
	if (vkCreateRenderPass(_graphicInstance->GetDevice(), &renderPassInfo, nullptr, &renderPassObject) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create render pass!");
	}

	return renderPassObject;
}