////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResourceContext.h"
#include "..\..\Peon\Peon.h"

VulkanWrapper::VWResourceContext::VWResourceContext()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWResourceContext::~VWResourceContext()
{
}

bool VulkanWrapper::VWResourceContext::Initialize(VWGraphicAdapter* _adapter, Packet::Manager* _packetManager)
{
	bool result;

	// Initialize our resource manager
	result = m_ResourceManager.Initialize(Peon::GetTotalWorkers());
	if (!result)
	{
		return false;
	}

	// Initialize the texture group index loader
	result = m_TextureGroupIndexLoader.Initialize(_packetManager, "TextureGroup/Index");
	if (!result)
	{
		return false;
	}

	// Initialize the model index loader
	result = m_ModelIndexLoader.Initialize(_packetManager, "Model/Index");
	if (!result)
	{
		return false;
	}

	return true;
}

void VulkanWrapper::VWResourceContext::ProcessResourceRequests()
{
	m_ResourceManager.ProcessResourceRequestQueues();
}