////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWShaderRenderingBase.h"
#include "..\Core\VWGraphicAdapter.h"
#include "..\Core\VWSwapChain.h"
#include "..\Core\VWGraphicInstance.h"
#include "..\Renderable\VWRenderable.h"
#include "..\Context\VWContext.h"

VulkanWrapper::VWShaderRenderingBase::VWShaderRenderingBase()
{
	// Set the initial data
	m_IgnoreTextureChanges = false;
	m_IgnoreModelChanges = false;
}

VulkanWrapper::VWShaderRenderingBase::~VWShaderRenderingBase()
{
}

void VulkanWrapper::VWShaderRenderingBase::AddRenderable(VWRenderable* _renderable)
{
	// Check if this renderable is valid to be used
	if (!_renderable->IsValid())
	{
		// Ignore this renderable
		return;
	}

	// Add this renderable
	m_Renderables.push_back(_renderable);
}

void VulkanWrapper::VWShaderRenderingBase::RenderOpaqueGeometry(VWContext* _graphicContext, int _swapchainImageIndex)
{
	// Update the instance data
	UpdateInstanceData(_graphicContext, m_Renderables);

	// Begin the rendering process
	BeginRender(_graphicContext, _swapchainImageIndex);

	// Reset the texture and vertex object identificators
	uint32_t currentTextureIdentificator = -1;
	uint32_t currentVertexObjectId = -1;

	// Start the current instance counter and the index count
	int lastInstance = 0;
	int instanceCounter = 0;
	uint32_t indexCount = 0;

	// For each renderable
	for (int i = 0; i < m_Renderables.size(); i++)
	{
		// Get the current object
		VWRenderable* currentObject = m_Renderables[i];

		// Get the object vertex object and texture group
		VWModel* model = currentObject->GetModel();
		VWTextureGroup* textureGroup = currentObject->GetTextureGroup();
		
		// Get the texture group and vertex identificators for the current object
		uint32_t textureIdentificator = textureGroup->GetTextureGroupIdentificator();
		uint32_t vertexIdentificator = model->GetModelIdentificator();

		// Check if the next object should be threated as a new object
		if ((!m_IgnoreTextureChanges && textureIdentificator != currentTextureIdentificator) || (!m_IgnoreModelChanges && vertexIdentificator != currentVertexObjectId))
		{
			// Verify if we have at last one instance to be rendered
			if (instanceCounter)
			{
				// Issue a draw call
				RenderCall(lastInstance, indexCount, instanceCounter);

				// Zero the instance counter and set the last instance
				instanceCounter = 0;
				lastInstance = i;
			}

			// Check if we should update the vertex data
			if (!m_IgnoreModelChanges && vertexIdentificator != currentVertexObjectId)
			{
				// Update the model
				UpdateModel(currentObject, indexCount);

				// Set the new vertex object id
				currentVertexObjectId = vertexIdentificator;
			}

			// Check if we should update the texture
			if (!m_IgnoreTextureChanges && textureIdentificator != currentTextureIdentificator)
			{
				// Update the textures
				UpdateTextures(currentObject);

				// Set the new texture identificator
				currentTextureIdentificator = textureIdentificator;
			}
		}

		// Increment the instance counter
		instanceCounter++;
	}

	// If we have at last one instance
	if (instanceCounter)
	{
		// Issue a draw call
		RenderCall(lastInstance, indexCount, instanceCounter);
	}

	// Clear all renderables
	m_Renderables.clear();

	// End the rendering process
	EndRender();
}

void VulkanWrapper::VWShaderRenderingBase::RenderTransparentGeometry()
{
}

void VulkanWrapper::VWShaderRenderingBase::UpdateInstanceData(VWContext* _context, std::vector<VWRenderable*>& _renderables)
{
}

void VulkanWrapper::VWShaderRenderingBase::UpdateTextures(VWRenderable* _instance)
{
}

void VulkanWrapper::VWShaderRenderingBase::UpdateModel(VWRenderable* _instance, uint32_t& _indexCount)
{
}

void VulkanWrapper::VWShaderRenderingBase::RenderCall(uint32_t _globalInstanceCount, uint32_t _indexCount, uint32_t _instanceCount)
{
}