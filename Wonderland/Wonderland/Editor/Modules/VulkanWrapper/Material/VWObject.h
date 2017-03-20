////////////////////////////////////////////////////////////////////////////////
// Filename: VWObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "..\Resource\VWBuffer.h"

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

////////////////////////////////////////////////////////////////////////////////
// Class name: VWObject
////////////////////////////////////////////////////////////////////////////////
class VWObject
{
public:

	struct Texture
	{
		std::string sTextureBindingName;
	};

	struct MaterialParameter
	{

	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWObject();
	~VWObject();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this render shard object
	bool Initialize(VWContext* _graphicContext);

	void SetCustomParameter(std::string _parameterName, void* _parameterPtr, uint32_t _parameterSize);
	void SetScalarParameter(std::string _parameterName, float _scalarValue);
	void SetVector2Parameter(std::string _parameterName, float _x, float _y);
	void SetVector3Parameter(std::string _parameterName, float _x, float _y, float _z);
	void SetVector4Parameter(std::string _parameterName, float _x, float _y, float _z, float _w);

///////////////
// VARIABLES //
private: //////

	std::map<std::string, Texture> m_TextureMap;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)