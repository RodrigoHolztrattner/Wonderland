////////////////////////////////////////////////////////////////////////////////
// Filename: VWRenderable.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "..\Misc\VWParameterHolder.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "..\Resource\VWBuffer.h"
#include "..\..\Reference.h"

#include "VWRenderableTransform.h"
#include "VWRenderableResource.h"

#include "..\Resource\Texture\VWTexture.h"
#include "..\Resource\Texture\VWTextureGroup.h"
#include "..\Resource\Model\VWModel.h"

#include "..\Resource\Texture\VWTextureGroupManager.h"
#include "..\Resource\Model\VWModelManager.h"

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
private: ConstantMap<__VA_ARGS__> dependencies;								\
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
class VWRenderable : public VWRenderableTransform, public VWRenderableResource, public VWParameterHolder
{
public:

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
	virtual bool Initialize(VWContext* _context);

	// Update our position
	virtual void Update(float _timeElapsed, bool _horizontal, bool _vertical, bool _depth);

public:

	// Return our alpha
	float GetAlpha() { return m_Alpha; }

	// Set the alpha
	virtual void SetAlpha(float _alpha) { m_Alpha = _alpha; }

	// Check if this renderable is valid to be used
	virtual bool IsValid();

///////////////
// VARIABLES //
private: //////
	
	// Our diffuse texture
	VWTexture m_DiffuseTexture;

protected:

	// Our alpha
	float m_Alpha;

	// The update time
	float m_UpdateTime;

	// If this renderable is valid to be used
	bool m_IsValid;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)