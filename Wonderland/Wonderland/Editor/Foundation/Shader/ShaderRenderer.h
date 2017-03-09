////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderRenderer.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\Math.h"
#include "..\Shader\ShaderBase.h"

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
// Class name: ShaderRenderer
////////////////////////////////////////////////////////////////////////////////
class ShaderRenderer
{
public:
	

public:
	ShaderRenderer(ShaderIndirection* _renderShader);
	ShaderRenderer(const ShaderRenderer&);
	~ShaderRenderer();

	///////////////
	// UTILITIES //
protected: ////////

	// Render this UI object on the next frame
	template<typename ObjectType>
	void RenderOnNextFrame()
	{
		// Temp
		ObjectType* temp = (ObjectType*)this;

		// Check if we should use the default UI shader
		if (m_ShaderIndirection != nullptr)
		{
			m_ShaderIndirection->RenderOnThisFrame(temp);
		}
	}

private:

	// The indirection
	ShaderIndirection* m_ShaderIndirection;
};