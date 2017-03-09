////////////////////////////////////////////////////////////////////////////////
// Filename: UIFontShader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"

#include "..\..\..\..\Shader\ShaderBase.h"
#include "..\..\..\..\Shader\ShaderFrame.h"
#include "UITextComponent.h"

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
// Class name: UIFontShader
////////////////////////////////////////////////////////////////////////////////
class UIFontShader : public ShaderBase<UIFontShader, UITextComponent>
{
public:
	UIFontShader();
	UIFontShader(const UIFontShader&);
	~UIFontShader();

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
	void RenderAux(UITextComponent* _object);

private:

	// The shader files
	ShaderShard m_VertexShard;
	ShaderShard m_FragmentShard;

	// The program file
	ShaderProgram m_ShaderProgram;

	// The frame object
	ShaderFrame m_FrameObject;
};