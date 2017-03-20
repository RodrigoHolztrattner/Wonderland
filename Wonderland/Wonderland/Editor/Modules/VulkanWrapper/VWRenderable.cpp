////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWRenderable.h"
#include "VWContext.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

VulkanWrapper::VWRenderable::VWRenderable()
{
	// Set the initial data
	m_UpdateTime = 0;
	m_Position = glm::vec3(0, 0, 0);
}

VulkanWrapper::VWRenderable::~VWRenderable()
{
}

bool VulkanWrapper::VWRenderable::Initialize(VWContext* _context)
{
	// Get the model manager
	VWModelManager* modelManager = _context->GetModelManager();

	// Get the texture group manager
	VWTextureGroupManager* textureGroupManager = _context->GetTextureGroupManager();

	//

	// Request our model object
	modelManager->RequestObject(&GetModelReference(), "square");

	// Get the texture group
	textureGroupManager->RequestObject(&GetTextureGroupReference(), "textureGroupSky");

	//

	// Get our texture
	m_DiffuseTexture.CreateWithTextureGroup(&m_TextureGroup, "Ground");

	// Set the texture parameter
	SetTextureParameter("diffuseTexture", &m_DiffuseTexture);

	return true;
}

bool VulkanWrapper::VWRenderable::IsValid()
{
	// Check if the texture group is valid
	if (!m_TextureGroup.IsValid())
	{
		return false;
	}

	// Check if the model is valid
	if (!m_Model.IsValid())
	{
		return false;
	}
	
	// Check if the diffuse texture is valid
	if (!m_DiffuseTexture.IsValid())
	{
		return false;
	}

	return true;
}

void VulkanWrapper::VWRenderable::Update(float _timeElapsed, bool _horizontal, bool _vertical, bool _depth)
{
	// Increment the time elapsed
	m_UpdateTime += _timeElapsed;

	// Set the amount
	float amount = 3;

	// Set the position
	m_Position = glm::vec3(std::cos(m_UpdateTime) * _horizontal * amount, std::sin(m_UpdateTime) * _vertical * amount, std::cos(m_UpdateTime) * std::sin(m_UpdateTime) * _depth * amount);
}