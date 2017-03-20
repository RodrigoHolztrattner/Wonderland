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
#include "..\Reference.h"

#include "Resource\Texture\VWTexture.h"
#include "Resource\Texture\VWTextureGroup.h"
#include "Resource\Model\VWModel.h"

#include "Resource\Texture\VWTextureGroupManager.h"
#include "Resource\Model\VWModelManager.h"

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
	virtual void Update(float _timeElapsed, bool _horizontal, bool _vertical, bool _depth);

public:

	// Return our position/rotation/scale/alpha
	glm::vec3 GetPosition() { return m_Position; }
	glm::vec3 GetRotation() { return m_Rotation; }
	glm::vec3 GetScale() { return m_Scale; }
	float GetAlpha() { return m_Alpha; }

	// Set the position/rotation/scale/alpha
	virtual void SetPosition(glm::vec3 _position) { m_Position = _position; }
	virtual void SetRotation(glm::vec3 _rotation) { m_Rotation = _rotation; }
	virtual void SetScale(glm::vec3 _scale) { m_Scale = _scale; }
	virtual void SetAlpha(float _alpha) { m_Alpha = _alpha; }

	// Return our model object/texture group
	VWModel* GetModel() { return m_Model.GetResource(); }
	VWTextureGroup* GetTextureGroup() { return m_TextureGroup.GetResource(); }

	// Return our texture group reference
	VWTextureGroupReference& GetTextureGroupReference() { return m_TextureGroup; }

	// Return our model reference
	VWModelReference& GetModelReference() { return m_Model; }

	// Check if this renderable is valid to be used
	virtual bool IsValid();

private:

///////////////
// VARIABLES //
private: //////
	
	// Our diffuse texture
	VWTexture m_DiffuseTexture;

protected:

	// If we are loading a resource async (prevents this object being deleted until the resource is loaded into memory)
	bool m_IsWaitingForResource;

	// Our position/rotation/scale/alpha
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	float m_Alpha;

	// Our model reference
	VWModelReference m_Model;

	// Our texture group reference
	VWTextureGroupReference m_TextureGroup;

	// The update time
	float m_UpdateTime;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)