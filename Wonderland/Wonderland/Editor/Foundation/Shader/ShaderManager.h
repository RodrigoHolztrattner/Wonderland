////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\Math.h"
#include "..\..\Support\Container\Array\Array.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "ShaderFileLoader.h"
#include "ShaderShard.h"
#include "ShaderProgram.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////
#include "..\..\Support\Container\Array\Array.h"

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManager
////////////////////////////////////////////////////////////////////////////////
class ShaderManager
{

public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	/////////////////////
	// VIRTUAL METHODS //
public: /////////////////

	// Initialize the UI shader
	virtual bool Initialize() = 0;

	// Prepare to render
	virtual bool PrepareToRender() = 0;

	// Render all objects
	virtual void Render() = 0;

//////////////////////
// STATIC FUNCTIONS //
public: //////////////

	// Process the global render
	static void ProcessGlobalRenderPhase();

//////////////////////
// STATIC VARIABLES //
//////////////////////

	// The global shader array
	static Array<ShaderManager*> s_GlobalShaderArray;

};