////////////////////////////////////////////////////////////////////////////////
// Filename: VWRenderableTransform.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
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

////////////
// MACROS //
////////////

///////////////
// NAMESPACE //
///////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWRenderableTransform
////////////////////////////////////////////////////////////////////////////////
class VWRenderableTransform
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWRenderableTransform();
	~VWRenderableTransform();

//////////////////
// MAIN METHODS //
public: //////////

	// Return our position/rotation/scale
	glm::vec3 GetPosition() { return m_Position; }
	glm::vec3 GetRotation() { return m_Rotation; }
	glm::vec3 GetScale() { return m_Scale; }

	// Set the position/rotation/scale
	virtual void SetPosition(glm::vec3 _position) { m_Position = _position; }
	virtual void SetRotation(glm::vec3 _rotation) { m_Rotation = _rotation; }
	virtual void SetScale(glm::vec3 _scale) { m_Scale = _scale; }

///////////////
// VARIABLES //
protected: ////

	// Our position/rotation/scale
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)