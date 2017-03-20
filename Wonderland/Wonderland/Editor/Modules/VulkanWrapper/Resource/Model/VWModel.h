////////////////////////////////////////////////////////////////////////////////
// Filename: VWModel.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\..\Material\VWDescriptorSetCreator.h"
#include "..\..\..\Reference.h"
#include "..\..\..\HashedString.h"
#include "..\..\..\Hoard\Hoard.h"
#include "..\..\VWBuffer.h"

#include <vector>
#include <map>
#include <array>
#include <list>
#include <atomic>

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
class VWModelManager;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWModel
////////////////////////////////////////////////////////////////////////////////
class VWModel : public Hoard::Supply::Object
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWModel();
	~VWModel();

//////////////////
// MAIN METHODS //
public: //////////

	// Process the internal resource
	bool ProcessResource(VWContext* _graphicContext);

	// Return the index count
	uint32_t GetIndexCount() { return m_IndexCount; }

	// Return the vertex buffer
	VWBuffer* GetVertexBuffer() { return &m_VertexBuffer; }

	// Return the index buffer
	VWBuffer* GetIndexBuffer() { return &m_IndexBuffer; }

	// Return the model identificator
	HashedStringIdentifier GetModelIdentificator() { return m_ModelIdentificator; }

	// Check if this object is valid
	bool IsValid() override;

///////////////
// VARIABLES //
private: //////

	// The model identifier
	HashedStringIdentifier m_ModelIdentificator;

	// The vertex buffer
	VWBuffer m_VertexBuffer;

	// The index buffer
	VWBuffer m_IndexBuffer;

	// The total number of indexes
	uint32_t m_IndexCount;
};

typedef Reference::Blob<VWModel> VWModelReference;

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)