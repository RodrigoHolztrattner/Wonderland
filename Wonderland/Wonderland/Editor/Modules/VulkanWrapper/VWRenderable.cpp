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
	// REMOVE THIS // We should set a model object here
	m_VertexObject = new VWVertexObject();
	m_VertexObject->Initialize();
	m_VertexObject->SetVertexSlots(VertexSlots::Position | VertexSlots::TextureCoordinate | VertexSlots::Color);
	m_VertexObject->CreateVertexBuffer(_context, vertices.data(), vertices.size());
	m_VertexObject->CreateIndexBuffer(_context, indices.data(), sizeof(indices[0]), indices.size());

	// Get our texture
	VWTexture* diffuseTexture = _context->GetTextureGroupManager()->GetTexture(_context, "images/teste.png", "dummy", _context->GetGraphicInstance()->GetCommandPool());

	// Set the diffure texture parameter
	SetTextureParameter("diffuseTexture", diffuseTexture);

	// Set our texture group
	m_TextureGroup = _context->GetTextureGroupManager()->GetTextureGroup("dummy");

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