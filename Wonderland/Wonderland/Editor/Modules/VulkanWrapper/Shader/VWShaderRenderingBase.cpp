////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWShaderRenderingBase.h"
#include "..\VWGraphicAdapter.h"
#include "..\VWSwapChain.h"
#include "..\VWGraphicInstance.h"
#include "..\VWRenderable.h"
#include "..\VWContext.h"

VulkanWrapper::VWShaderRenderingBase::VWShaderRenderingBase()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWShaderRenderingBase::~VWShaderRenderingBase()
{
}

void VulkanWrapper::VWShaderRenderingBase::AddRenderable(VWRenderable* _renderable)
{
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

		// Check if the next object should be threated as a new object
		if (currentObject->GetTextureIdentificator() != currentTextureIdentificator || currentObject->GetVertexObject()->GetId() != currentVertexObjectId)
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
			if (currentObject->GetVertexObject()->GetId() != currentVertexObjectId)
			{
				// Update the vertices
				UpdateVertices(currentObject, indexCount);

				// Set the new vertex object id
				currentVertexObjectId = currentObject->GetVertexObject()->GetId();
			}

			// Check if we should update the texture
			if (currentObject->GetTextureIdentificator() != currentTextureIdentificator)
			{
				// Update the textures
				UpdateTextures(currentObject);

				// Set the new texture identificator
				currentTextureIdentificator = currentObject->GetTextureIdentificator();
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

void VulkanWrapper::VWShaderRenderingBase::UpdateVertices(VWRenderable* _instance, uint32_t& _indexCount)
{
}

void VulkanWrapper::VWShaderRenderingBase::RenderCall(uint32_t _globalInstanceCount, uint32_t _indexCount, uint32_t _instanceCount)
{
}