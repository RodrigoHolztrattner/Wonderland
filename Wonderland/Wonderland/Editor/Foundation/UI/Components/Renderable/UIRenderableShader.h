////////////////////////////////////////////////////////////////////////////////
// Filename: UIRenderableShader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\Support\Container\Array\Array.h"

#include "..\..\..\Shader\ShaderBase.h"
#include "..\..\..\Shader\ShaderFrame.h"
#include "UIRenderableComponent.h"

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
// Class name: UIRenderableShader
////////////////////////////////////////////////////////////////////////////////
class UIRenderableShader : public ShaderBase<UIRenderableShader, UIRenderableComponent>
{
public:
	UIRenderableShader();
	UIRenderableShader(const UIRenderableShader&);
	~UIRenderableShader();

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
	void RenderAux(UIRenderableComponent* _object);

private:

	// The shader files
	ShaderShard m_VertexShard;
	ShaderShard m_FragmentShard;

	// The program file
	ShaderProgram m_ShaderProgram;

	// The frame object
	ShaderFrame m_FrameObject;
};