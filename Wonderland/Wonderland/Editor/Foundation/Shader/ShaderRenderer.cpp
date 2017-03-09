////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderRenderer.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderRenderer.h"

///////////////
// NAMESPACE //
///////////////

ShaderRenderer::ShaderRenderer(ShaderIndirection* _renderShader)
{
	// Set the initial data
	m_ShaderIndirection = _renderShader;
}

ShaderRenderer::ShaderRenderer(const ShaderRenderer& other)
{
}

ShaderRenderer::~ShaderRenderer()
{
}
