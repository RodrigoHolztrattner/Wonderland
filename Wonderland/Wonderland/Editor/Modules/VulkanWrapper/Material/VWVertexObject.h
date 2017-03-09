////////////////////////////////////////////////////////////////////////////////
// Filename: VWVertexObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"

#include <map>
#include <string>
#include <glm/glm.hpp>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWContext;
class VWBuffer;

enum VertexSlots
{
	Invalid				= 0,
	Position			= 1 << 0,
	TextureCoordinate	= 1 << 1,
	Color				= 1 << 2,
	Normal				= 1 << 3,
	Binormal			= 1 << 4,
	Tangents			= 1 << 5
};

////////////////////////////////////////////////////////////////////////////////
// Class name: VWVertexObject
////////////////////////////////////////////////////////////////////////////////
class VWVertexObject
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWVertexObject();
	~VWVertexObject();

//////////////////
// MAIN METHODS //
public: //////////

	// Set our vertex slots
	void SetVertexSlots(uint32_t _vertexSlots);

public:

	bool Initialize();
	bool CreateVertexBuffer(VWContext* _context, const void* _data, uint32_t _totalVertices);
	bool CreateIndexBuffer(VWContext* _context, const void* _data, uint32_t _indexUnitSize, uint32_t _totalIndexes);

	//
	//
	//

	// Return our vertex slots
	uint32_t GetVertexSlots() { return m_VertexSlots; }

	// Return the vertex/index buffer
	VWBuffer* GetVertexBuffer() { return m_VertexBuffer; }
	VWBuffer* GetIndexBuffer() { return m_IndexBuffer; }

	// Return the index count
	uint32_t GetIndexCount() { return m_IndexCount; }

	// Return the runtime id
	uint32_t GetId() { return m_RuntimeId; }

private:

///////////////
// VARIABLES //
private: //////

	// Our runtime id
	uint32_t m_RuntimeId;

	// Our vertex slots
	uint32_t m_VertexSlots;

	// Our vertex and index buffers
	VWBuffer* m_VertexBuffer;
	VWBuffer* m_IndexBuffer;

	// The vertex unit size
	uint32_t m_VertexUnitSize;

	// The index count
	uint32_t m_IndexCount;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)