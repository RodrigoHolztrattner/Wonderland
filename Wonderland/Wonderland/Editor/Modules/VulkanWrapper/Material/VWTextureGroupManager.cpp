////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroupManager.h"
#include "..\VWContext.h"
#include "VWTexture.h"
#include "..\..\LogSystem.h"
#include "..\..\Peon\Peon.h"

VulkanWrapper::VWTextureGroupManager::VWTextureGroupManager()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWTextureGroupManager::~VWTextureGroupManager()
{
}

bool VulkanWrapper::VWTextureGroupManager::Initialize(VWContext* _graphicContext, uint32_t _totalWorkerThreads)
{
	// Set the total worker threads
	m_TotalWorkerThreads = _totalWorkerThreads;

	// Alloc the resource requests
	m_TextureGroupRequests = new std::vector<VWTextureGroupRequest>[_totalWorkerThreads];

	// Initialize the texture group vault
	if (!m_TextureGroupVault.Initialize())
	{
		return false;
	}

	// Add our layout descriptors
	AddDescriptorSetLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VWTextureGroup::MaximumTexturePerGroup, VK_SHADER_STAGE_FRAGMENT_BIT);

	// Create the descriptor pool
	CreateDescriptorPool(_graphicContext, VWTextureGroup::MaximumTextureGroups);

	// Create the set layout
	CreateDescriptorSetLayout(_graphicContext);

	return true;
}

void VulkanWrapper::VWTextureGroupManager::Release()
{

}

void VulkanWrapper::VWTextureGroupManager::RequestTextureGroup(Reference::Blob<VWTextureGroup>* _textureGroupReference, HashedStringIdentifier _groupIdentifier)
{
	// Get the current worker index
	uint32_t currentWorkerIndex = Peon::GetCurrentWorkerIndex();

	// Create a new resource request
	VWTextureGroupRequest newRequest = {};
	newRequest.Create(_textureGroupReference, _groupIdentifier);

	// Insert into the queue
	m_TextureGroupRequests[currentWorkerIndex].push_back(newRequest);
}

void VulkanWrapper::VWTextureGroupManager::ProcessTextureGroupRequestQueues()
{
	// Process our wake list first
	// ProcessWakeList();

	// Process and clear all request queues
	for (int i = 0; i < m_TotalWorkerThreads; i++)
	{
		// Process all requests for this queue
		for (auto& resourceRequest : m_TextureGroupRequests[i])
		{
			// Process this request
			ProcessTextureGroupRequest(resourceRequest);
		}

		// Clear this request queue
		m_TextureGroupRequests[i].clear();
	}

	// Commit all resource requests for loading
	// m_ResourceLoader.CommitLoadQueues();
}


void VulkanWrapper::VWTextureGroupManager::ProcessTextureGroupRequest(VWTextureGroupRequest& _textureGroupRequest)
{
	// Check if the texture group is inside the vault
	VWTextureGroup* textureGroup = m_TextureGroupVault.IsTextureGroupLoaded(_textureGroupRequest.GetRequestIdentifier());
	if (textureGroup != nullptr)
	{
		// Increment the texture group reference counter
		// resource->IncrementReferenceCount();

		// Set the resource ptr
		_textureGroupRequest.GetRequestReference()->ValidateResourceReference(textureGroup);

		return;
	}

	// Create a new resource object
	VWTextureGroup* newTextureGroup = new VWTextureGroup();

	// Append this new resource to the wake list
	// newResource->next = m_ResourceWakeList;
	// m_ResourceWakeList = newResource;

	// Initialize the new texture group
	newTextureGroup->Initialize();

	// Queue the resource load
	// m_ResourceLoader.QueueExternalResourceLoad(_resourceRequest.GetResourceReference(), _resourceRequest.GetRequestPath(), _resourceRequest.GetProcessMethod());

	// Insert the texture group into the vault
	m_TextureGroupVault.InsertTextureGroup(newTextureGroup, _textureGroupRequest.GetRequestIdentifier());

	// Set the resource ptr
	_textureGroupRequest.GetRequestReference()->ValidateResourceReference(newTextureGroup);
}

/*
void VulkanWrapper::VWTextureGroupManager::RequestTextureGroup(VWTextureGroupReference* _textureGroupReference, uint32_t _groupIdentifier, std::function<void()> _onLoadCallback)
{
	// Get the current worker index
	uint32_t currentWorkerIndex = Peon::GetCurrentWorkerIndex();

	// Create a new resource request
	VWResourceRequest newRequest = {};
	newRequest.CreateFromId(_resourceReference, _resourceIdentifier, _onLoadCallback);

	// Insert into the queue
	m_ResourceRequests[currentWorkerIndex].push_back(newRequest);
}

void VulkanWrapper::VWTextureGroupManager::RequestTextureGroup(VWTextureGroupReference* _textureGroupReference, std::string _groupName, std::function<void()> _onLoadCallback)
{

}
*/
/*
VulkanWrapper::VWTexture* VulkanWrapper::VWTextureGroupManager::GetTexture(VWContext* _graphicContext, std::string _textureName, std::string _textureGroup)
{
	// Check if the texture group exists
	VulkanWrapper::VWTextureGroup* textureGroup = FindTextureGroup(_textureGroup);
	if (textureGroup == nullptr)
	{
		// Create a new texture group
		textureGroup = &m_TextureGroups[_textureGroup];
		if(!textureGroup->Create(_graphicContext, m_DescriptorPool, m_DescriptorSetLayout))
		{
			throw std::runtime_error("failed to create texture group!");
		}
	}

	// Check if the texture already exists
	VWTexture* texture = textureGroup->FindTexture(_textureName);
	if (texture == nullptr)
	{
		// Create a new texture
		texture = CreateTexture(_graphicContext, _textureName, _graphicContext->GetGraphicInstance()->GetCommandPool());
		if(texture == nullptr)
		{
			throw std::runtime_error("failed to create texture!");
		}

		// Insert the created texture into the group
		if (!textureGroup->InsertTexture(_graphicContext, texture, _textureName))
		{
			throw std::runtime_error("failed to insert texture into group!");
		}
	}

	return texture;
}

VulkanWrapper::VWTextureGroup* VulkanWrapper::VWTextureGroupManager::FindTextureGroup(std::string _textureGroup)
{
	// Check if the texture group exist
	if (m_TextureGroups.find(_textureGroup) == m_TextureGroups.end())
	{
		return nullptr;
	}

	return &m_TextureGroups[_textureGroup];
}

VulkanWrapper::VWTexture* VulkanWrapper::VWTextureGroupManager::CreateTexture(VWContext* _graphicContext, std::string _textureName, VkCommandPool _commandPool)
{
	VWTexture* newTexture = new VWTexture();

	newTexture->Create(_graphicContext, _commandPool, (char*)_textureName.c_str()); //TODO: Use a better method (creation command)

	return newTexture;
}
*/