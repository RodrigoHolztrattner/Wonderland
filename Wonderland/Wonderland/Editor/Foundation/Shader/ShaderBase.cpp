////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderBase.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderBase.h"

/*

ShaderBase::ShaderBase()
{
}

ShaderBase::ShaderBase(const ShaderBase& other)
{
}

ShaderBase::~ShaderBase()
{
}

*/

/*

bool ShaderBase::SetShaderParameters(float* worldMatrix, float* viewMatrix, float* projectionMatrix)
{
	unsigned int location;


	// Set the world matrix in the vertex shader.
	location = glGetUniformLocation(m_shaderProgram, "worldMatrix");
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, false, worldMatrix);

	// Set the view matrix in the vertex shader.
	location = glGetUniformLocation(m_shaderProgram, "viewMatrix");
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, false, viewMatrix);

	// Set the projection matrix in the vertex shader.
	location = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, false, projectionMatrix);

	return true;
}

*/