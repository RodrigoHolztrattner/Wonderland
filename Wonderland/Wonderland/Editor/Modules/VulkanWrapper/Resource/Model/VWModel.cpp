////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWModel.h"
#include "..\..\Context\VWContext.h"
#include "..\..\..\LogSystem.h"
#include "..\..\..\ModelComposer\ModelComposer.h"

VulkanWrapper::VWModel::VWModel()
{
	// Set the initial data
	m_IndexCount = 0;
}

VulkanWrapper::VWModel::~VWModel()
{
}

bool VulkanWrapper::VWModel::ProcessResource(VWContext* _graphicContext)
{
	// Get the resource reference
	Reference::Blob<Hoard::HoardResource>* resourceReference = GetResourceReference();

	// Get the resource itself
	Hoard::HoardResource* resource = resourceReference->GetResource();

	// Get the resource byte array
	std::vector<unsigned char>& byteArray = resource->GetByteArrayData();

	// The model unpacker we will use to unpack the data
	ModelComposer::Unpacker modelUnpacker;

	// Unpack the model data
	bool unpackResult;
	ModelComposer::Format modelData = modelUnpacker.UnpackModel(byteArray, unpackResult);
	if (!unpackResult)
	{
		return false;
	}

	// Set the model identificator
	m_ModelIdentificator = HashedString(modelData.name.GetString()).Hash();

	// Set the index count
	m_IndexCount = modelData.indexes.size();

	// Create the vertex buffer
	m_VertexBuffer.Create(_graphicContext, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, modelData.vertices.data(), sizeof(ModelComposer::VertexFormat) * modelData.vertices.size());

	// Create the index buffer
	m_IndexBuffer.Create(_graphicContext, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, modelData.indexes.data(), sizeof(ModelComposer::IndexFormat) * modelData.indexes.size());

	return true;
}

bool VulkanWrapper::VWModel::IsValid()
{
	// Check our current status
	if (GetStatus() != Hoard::Supply::Object::Status::Initialized)
	{
		return false;
	}

	// Get the resource reference
	Reference::Blob<Hoard::HoardResource>* resourceReference = GetResourceReference();
	if (!resourceReference->IsValid())
	{
		return false;
	}

	// Get the resource itself
	Hoard::HoardResource* resource = resourceReference->GetResource();
	if (resource->GetStatus() != Hoard::Resource::ResourceStatus::Initialized)
	{
		return false;
	}

	return true;
}