////////////////////////////////////////////////////////////////////////////////
// Filename: VWRenderable.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\NamespaceDefinitions.h"
#include "Material\VWShaderParameterHolder.h"
#include "Material\VWVertexObject.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "VWBuffer.h"
#include "Material\VWTexture.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////
// MACROS //
////////////

/**
*	Generate an unique ID for the class
*/
#define AddComponentUniqueID()												\
private:																	\
static int GetClassComponentPrivateID()										\
{																			\
	return __LINE__;														\
}																			\
public:																		\
static const unsigned int ClassComponentID()								\
{																			\
	return reinterpret_cast<size_t>(GetClassComponentPrivateID);			\
}

/**
*	Register the dependencies for this component
*/
#define RegisterClassDependencies(...)										\
private: ConstantMap<__VA_ARGS__> dependencies;							\
public: template <typename ClassType>										\
ClassType* GetDependency()													\
{																			\
	ClassType* dummy = 0;													\
	return dependencies[dummy];												\
}																			\
																			\
public: template <typename ClassType>										\
ClassType* RegisterDependency(ClassType* _object)							\
{																			\
	ClassType* dummy = 0;													\
	dependencies.storageCount--;											\
	return *(dependencies << dummy) = _object;								\
}																			\
																			\
public: bool IsDirty()														\
{																			\
	return (dependencies.storageCount);										\
}

// Add a unique ID to this component class
// AddComponentUniqueID();


///////////////
// NAMESPACE //
///////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWContext;
class VWTextureGroup;

/*
	- Only one thread should initialize this renderable and queue any resource needed.
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: VWRenderable
////////////////////////////////////////////////////////////////////////////////
class VWRenderable : public VWShaderParameterHolder
{
public:

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;
		glm::vec2 texCoord;
	};

	const std::vector<Vertex> vertices = {
		{ { -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		{ { 0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { -0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } }
	};

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWRenderable();
	~VWRenderable();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this render shard object
	bool Initialize(VWContext* _context);

	// Update our position
	void Update(float _timeElapsed, bool _horizontal, bool _vertical, bool _depth);

	// Return our position
	glm::vec3 GetPosition() { return m_Position; }

	// Return our vertex object
	VWVertexObject* GetVertexObject() { return m_VertexObject; }
	
	// Return the texture group reference
	VWTextureGroup* GetTextureGroup() { return m_TextureGroup; }

private:

///////////////
// VARIABLES //
private: //////
	
	// Our vertex object reference
	VWVertexObject* m_VertexObject;

	// Our texture group reference
	VWTextureGroup* m_TextureGroup;

protected:

	// If we are loading a resource async (prevents this object being deleted until the resource is loaded into memory)
	bool m_IsWaitingForResource;
	// resource counter

	// Our alpha value (needed for sorting)

	// Our position
	glm::vec3 m_Position;

	// The update time
	float m_UpdateTime;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)