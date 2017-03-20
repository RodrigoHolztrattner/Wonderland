////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWRenderableTransform.h"

VulkanWrapper::VWRenderableTransform::VWRenderableTransform()
{
	// Set the initial data
	m_Position = glm::vec3(0, 0, 0);
	m_Rotation = glm::vec3(0, 0, 0);
	m_Scale = glm::vec3(1, 1, 1);
}

VulkanWrapper::VWRenderableTransform::~VWRenderableTransform()
{
}