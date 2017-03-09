////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWVertexObject.h"
#include "..\VWBuffer.h"

VulkanWrapper::VWVertexObject::VWVertexObject()
{
	// Set the initial data
	m_RuntimeId = 0;
	m_IndexCount = 0;
	m_VertexSlots = VertexSlots::Invalid;
}

VulkanWrapper::VWVertexObject::~VWVertexObject()
{
}

bool VulkanWrapper::VWVertexObject::Initialize()
{
	// Alloc space for the vertex and index buffers
	m_VertexBuffer = new VWBuffer();
	m_IndexBuffer = new VWBuffer();

	return true;
}

bool VulkanWrapper::VWVertexObject::CreateVertexBuffer(VWContext* _context, const void* _data, uint32_t _totalVertices)
{
	// Create the vertex position buffer
	VkDeviceSize bufferSize = m_VertexUnitSize * _totalVertices;
	
	m_VertexBuffer->Create(_context, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, _data, bufferSize);

	return true;
}

bool VulkanWrapper::VWVertexObject::CreateIndexBuffer(VWContext* _context, const void* _data, uint32_t _indexUnitSize, uint32_t _totalIndexes)
{
	VkDeviceSize bufferSize = _indexUnitSize * _totalIndexes;

	// Set the index count
	m_IndexCount = _totalIndexes;

	// Create the index buffer
	m_IndexBuffer->Create(_context, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, _data, bufferSize);

	return true;
}

void VulkanWrapper::VWVertexObject::SetVertexSlots(uint32_t _vertexSlots)
{
	// Set the vertex slots and zero the vertex unit size
	m_VertexSlots = _vertexSlots;
	m_VertexUnitSize = 0;

	// Calc the unit size
	if (m_VertexSlots & VertexSlots::Position)
	{
		m_VertexUnitSize += sizeof(glm::vec3);
	}
	if (m_VertexSlots & VertexSlots::Color)
	{
		m_VertexUnitSize += sizeof(glm::vec3);
	}
	if (m_VertexSlots & VertexSlots::TextureCoordinate)
	{
		m_VertexUnitSize += sizeof(glm::vec2);
	}
	if (m_VertexSlots & VertexSlots::Normal)
	{
		m_VertexUnitSize += sizeof(glm::vec3);
	}
	if (m_VertexSlots & VertexSlots::Binormal)
	{
		m_VertexUnitSize += sizeof(glm::vec3);
	}
	if (m_VertexSlots & VertexSlots::Tangents)
	{
		m_VertexUnitSize += sizeof(glm::vec3);
	}
}