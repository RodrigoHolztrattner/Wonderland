////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWModelManager.h"
#include "VWModel.h"
#include "VWModelIndex.h"
#include "..\..\Context\VWContext.h"
#include "..\..\..\LogSystem.h"
#include "..\..\..\Peon\Peon.h"

VulkanWrapper::VWModelManager::VWModelManager()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWModelManager::~VWModelManager()
{
}

void VulkanWrapper::VWModelManager::Release()
{

}

VulkanWrapper::VWModel* VulkanWrapper::VWModelManager::CreateAndRequestObject(Hoard::ResourceManager* _resourceManager, uint32_t _resourceIdentifier)
{
	// Create a new object
	VWModel* newObject = new VWModel();

	// Initialize the new object
	newObject->Initialize();

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