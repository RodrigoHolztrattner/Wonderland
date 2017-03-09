////////////////////////////////////////////////////////////////////////////////
// Filename: UIColorShader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"

#include "..\..\..\..\Shader\ShaderBase.h"
#include "..\..\..\..\Shader\ShaderFrame.h"
#include "UIColorComponent.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UIColorShader
////////////////////////////////////////////////////////////////////////////////
class UIColorShader : public ShaderBase<UIColorShader, UIColorComponent>
{
public:
	UIColorShader();
	UIColorShader(const UIColorShader&);
	~UIColorShader();

	////////////
	// GLOBAL //
	////////////

	////////////
	// MEMBER //
	////////////

	// Initialize the UI shader
	bool Initialize();

	// Prepare to render
	bool PrepareToRender();

protected:

	// Render all objects (aux)
	void RenderAux(UIColorComponent* _object);

private:

	// The shader files
	ShaderShard m_VertexShard;
	ShaderShard m_FragmentShard;

	// The program file
	ShaderProgram m_ShaderProgram;

	// The frame object
	ShaderFrame m_FrameObject;
};