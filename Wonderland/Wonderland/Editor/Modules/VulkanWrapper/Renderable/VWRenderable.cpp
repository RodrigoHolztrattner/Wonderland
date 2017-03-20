////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWRenderable.h"
#include "..\Context\VWContext.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

VulkanWrapper::VWRenderable::VWRenderable()
{
	// Set the initial data
	m_UpdateTime = 0;
	m_Position = glm::vec3(0, 0, 0);
	m_Rotation = glm::vec3(0, 0, 0);
	m_Scale = glm::vec3(1, 1, 1);
	m_Alpha = 1.0f;
	m_IsValid = false;
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
	m_DiffuseTexture.CreateWithTextureGroup(&GetTextureGroupReference(), "Ground");

	// Set the texture parameter
	SetTextureParameter("diffuseTexture", &m_DiffuseTexture);

	return true;
}

bool VulkanWrapper::VWRenderable::IsValid()
{
	// Fast check if we are valid
	if (m_IsValid)
	{
		return true;
	}

	// Check if the texture group reference is valid
	if (!IsResourceReferenceValid(GetTextureGroupReference()))
	{
		return false;
	}

	// Check if the model reference is valid
	if (!IsResourceReferenceValid(GetModelReference()))
	{
		return false;
	}

	// Set that we are valid to be used
	m_IsValid = true;

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