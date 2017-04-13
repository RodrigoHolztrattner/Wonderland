////////////////////////////////////////////////////////////////////////////////
// Filename: VWShaderRenderPassBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "..\Core\VWGraphicAdapter.h"
#include "..\Renderable\VWRenderable.h"

#include "..\Resource\VWBuffer.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWContext;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWShaderRenderPassBase
////////////////////////////////////////////////////////////////////////////////
class VWShaderRenderPassBase
{
public:

	struct RenderPass;
	struct SubPass;
	struct AttachmentDescription;

	struct SubPass
	{
		SubPass() { isExternal = false; id = 0; };
		SubPass(bool _isExternal) { isExternal = _isExternal; id = 0;}

	protected:
		friend VWShaderRenderPassBase;

		// The subpass id
		uint32_t id;

		// If this subpass is external
		bool isExternal;

		// The render pass id
		uint32_t renderPassId;
	};

	struct AttachmentDescription
	{
	protected:
		friend VWShaderRenderPassBase;

		// The id
		uint32_t id;
	};

	struct RenderPass
	{
		// The render pass id
		uint32_t id;
	};

	const SubPass SubPassExternal = SubPass(true);
	const SubPass SubPassNull = SubPass();
	typedef AttachmentDescription ColorAttachmentDescription;
	typedef AttachmentDescription DepthAttachmentDescription;


private:

	struct SubPassInternal
	{
		SubPassInternal() { isExternal = false; };
		SubPassInternal(bool _isExternal) { isExternal = _isExternal; }

		// The subpass description
		VkSubpassDescription description;

		// Add input/color/resolve attachment references
		std::vector<VkAttachmentReference> inputAttachmentReference;
		std::vector<VkAttachmentReference> colorAttachmentReference;
		std::vector<VkAttachmentReference> resolveAttachmentReference;

		// The depth stencil attachment reference
		VkAttachmentReference depthAtencilAttachmentReference;

		// All attachments to preserve
		std::vector<uint32_t> preserveAttachments;

		// If this subpass is external
		bool isExternal;
	};

	struct RenderPassInternal
	{
		// All the subpasses
		std::vector<SubPassInternal> subPasses;

		// All the dependencies
		std::vector<VkSubpassDependency> dependencies;

		// Attachment descriptors
		std::vector<VkAttachmentDescription> attachmentDescriptors;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWShaderRenderPassBase();
	~VWShaderRenderPassBase();

///////////////////////
// PIPELINE CREATION //
protected: ////////////

//////////////////////
// SUBPASS CREATION //
//////////////////////

	// Start a render pass
	RenderPass StartRenderPass();

	// Create a subpass
	SubPass StartSubPass(RenderPass _renderPass, VkPipelineBindPoint _bindPoint, VkSubpassDescriptionFlags _flags = 0);

	// Add a dependency
	void AddDependency(RenderPass _renderPass, SubPass _srcSubpass, SubPass _dstSubpass, VkPipelineStageFlags _srcStageMask, VkPipelineStageFlags _dstStageMask, VkAccessFlags _srcAcessFlags, VkAccessFlags _dstAcessFlags);

	// Create a render pass
	VkRenderPass CreateRenderPass(VWGraphicInstance* _graphicInstance, RenderPass _renderPass);

	// Add an attachment reference
	void AddInputAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout);
	void AddColorAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout);
	void AddResolveAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout);
	void SetDepthAttachmentReference(SubPass& _subPass, AttachmentDescription _attachment, VkImageLayout _layout);

	// Create a color/depth attachment description
	ColorAttachmentDescription CreateColorAttachmentDescriptor(RenderPass _renderPass, VkFormat _format, VkSampleCountFlagBits _samples, VkAttachmentLoadOp _loadOp, VkAttachmentStoreOp _storeOp, VkImageLayout _initialLayout, VkImageLayout _finalLayout);
	DepthAttachmentDescription CreateDepthAttachmentDescriptor(RenderPass _renderPass, VkFormat _format, VkSampleCountFlagBits _samples, VkAttachmentLoadOp _loadOp, VkAttachmentStoreOp _storeOp, VkAttachmentLoadOp _stencilLoadOp, VkAttachmentStoreOp _stencilStoreOp, VkImageLayout _initialLayout, VkImageLayout _finalLayout);


///////////////////
// OTHER METHODS //
protected: ////////

	// Create a subpass
	bool CreateSubpass(SubPassInternal& _subPass);

	// Add an attachment desceiptor
	uint32_t AddAttachmentDescriptor(RenderPass _renderPass, VkFormat _format, VkSampleCountFlagBits _samples, VkAttachmentLoadOp _loadOp, VkAttachmentStoreOp _storeOp, VkAttachmentLoadOp _stencilLoadOp, VkAttachmentStoreOp _stencilStoreOp, VkImageLayout _initialLayout, VkImageLayout _finalLayout);



///////////////
// VARIABLES //
private: //////

	// All render passes
	std::vector<RenderPassInternal> m_RenderPasses;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)