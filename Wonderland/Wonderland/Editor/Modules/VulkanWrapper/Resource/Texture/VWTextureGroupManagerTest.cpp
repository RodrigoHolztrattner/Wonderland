////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroupManagerTest.h"
#include "..\..\VWContext.h"
#include "..\..\..\LogSystem.h"
#include "..\..\..\Peon\Peon.h"

VulkanWrapper::VWTextureGroupManagerTest::VWTextureGroupManagerTest()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWTextureGroupManagerTest::~VWTextureGroupManagerTest()
{
}

void VulkanWrapper::VWTextureGroupManagerTest::Release()
{

}

VulkanWrapper::VWTextureGroup* VulkanWrapper::VWTextureGroupManagerTest::CreateAndRequestObject(Hoard::ResourceManager* _resourceManager, uint32_t _resourceIdentifier)
{
	// Create a new object
	VWTextureGroup* newObject = new VWTextureGroup();

	// Initialize the new object
	newObject->Initialize();

	// Create the descriptor set
	newObject->CreateDescriptorSet(m_ContextReference, m_DescriptorPool, m_DescriptorSetLayout);

	// Request the new resource
	_resourceManager->RequestResource(newObject->GetResourceReference(), _resourceIdentifier, []() {}, [=]() 
	{
		// Create the texture group
		newObject->ProcessResource(m_ContextReference);

		// Finish the loading process
		newObject->FinishLoadingProcess();
	});
	
	return newObject;
}

void VulkanWrapper::VWTextureGroupManagerTest::CreateDescriptorLayout(VWContext* _graphicContext)
{
	// Set the context reference
	m_ContextReference = _graphicContext;

	// Add our layout descriptors
	AddDescriptorSetLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT); // VWTextureGroup::MaximumTexturePerGroup

	// Create the descriptor pool
	CreateDescriptorPool(_graphicContext, VWTextureGroup::MaximumTextureGroups);

	// Create the set layout
	CreateDescriptorSetLayout(_graphicContext);
}