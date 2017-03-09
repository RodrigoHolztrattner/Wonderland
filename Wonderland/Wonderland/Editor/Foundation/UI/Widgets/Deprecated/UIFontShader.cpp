////////////////////////////////////////////////////////////////////////////////
// Filename: UIFontShader.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIFontShader.h"

#include <fstream>
using namespace std;

///////////////
// NAMESPACE //
///////////////

UIFontShader::UIFontShader()
{
}

UIFontShader::UIFontShader(const UIFontShader& other)
{
}

UIFontShader::~UIFontShader()
{
}

bool UIFontShader::Initialize()
{
	bool result;

	// Set the shard data
	m_VertexShard.SetData(LoadShardSourceFile("font.vs"));
	m_FragmentShard.SetData(LoadShardSourceFile("font.fs"));

	// Make the vertex shard
	result = m_VertexShard.MakeShard(GL_VERTEX_SHADER);
	if(!result)
	{
		return false;
	}

	// Make the fragment shard
	result = m_FragmentShard.MakeShard(GL_FRAGMENT_SHADER);
	if (!result)
	{
		return false;
	}

	// Make the shader program
	result = m_ShaderProgram.MakeProgram();
	if (!result)
	{
		return false;
	}

	// Attach the shards
	m_ShaderProgram.AttachShard(&m_VertexShard);
	m_ShaderProgram.AttachShard(&m_FragmentShard);

	// Set the program input variables
	m_ShaderProgram.SetInputVariable(0, "inputPosition");
	m_ShaderProgram.SetInputVariable(1, "texCoord");

	// Compile the shader program
	result = m_ShaderProgram.CompileProgram();
	if (!result)
	{
		return false;
	}
	
	return true;
}

bool UIFontShader::PrepareToRender()
{
	WMatrix4 worldMatrix;
	WMatrix4 viewMatrix;
	WMatrix4 projectionMatrix;
	unsigned int location;

	// Use our program
	m_ShaderProgram.UseProgram();
	
	// Set the matrices
	worldMatrix.BuildIdentity();
	viewMatrix.BuildView(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projectionMatrix.BuildOrtho(3.14159265358979323846f / 4.0f, 640, 480, 0.1, 1000.0f);
	projectionMatrix = viewMatrix = worldMatrix;

	// Set the world matrix in the vertex shader.
	location = m_ShaderProgram.GetUniformLocation("worldMatrix");
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, false, worldMatrix.v);

	// Set the view matrix in the vertex shader.
	location = m_ShaderProgram.GetUniformLocation("viewMatrix");
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, false, viewMatrix.v);

	// Set the projection matrix in the vertex shader.
	location = m_ShaderProgram.GetUniformLocation("projectionMatrix");
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, false, projectionMatrix.v);

	return true;
}

void UIFontShader::RenderAux(UITextBase* _object)
{
	unsigned int location;
	WMatrix4 localMatrix;
	Vector4 glyphTextureCoordinate;

	// Get the font object
	UIFont* font = _object->GetFontType();

	// Set texture
	location = m_ShaderProgram.GetUniformLocation("fontTexture");
	if (location == -1)
	{
		return;
	}
	GLuint texId = font->GetTexture()->BindTexture(0);
	glUniform1i(location, texId);

	int currentPos = 0;

	// For each char
	for (int i = 0; i < _object->GetText().size(); i++)
	{
		char currentChar = _object->GetText()[i].originalChar;

		// Set the position and size
		Vector3 position = Vector3::TransformToScreenPosition(_object->GetScreenFrame().position, _object->GetScreenFrame().size);
		Vector3 size = Vector3::TransformToScreenSize(_object->GetScreenFrame().size);

		position = _object->GetText()[i].position;
		size = _object->GetText()[i].size;

		// Make the local matrix
		localMatrix.BuildTransform(position, Vector3(0, 0, 0), size);
		localMatrix.s13 = position.x;
		localMatrix.s14 = position.y;

		// Set the local matrix
		location = m_ShaderProgram.GetUniformLocation("localMatrix");
		if (location == -1)
		{
			return;
		}
		glUniformMatrix4fv(location, 1, false, localMatrix.v);

		// Set the glyph texture coord vector
		glyphTextureCoordinate = font->GetGlyphData(currentChar)->texCoordinates;
		
		// Set glyph texture coordinates
		location = m_ShaderProgram.GetUniformLocation("glyphTextureCoord");
		if (location == -1)
		{
			return;
		}
		glUniform4f(location, glyphTextureCoordinate.x, glyphTextureCoordinate.y, glyphTextureCoordinate.z, glyphTextureCoordinate.w);

		// Render our frame object
		(font->GetGlyphFrame(currentChar))->RenderFrame(GL_TRIANGLES, GL_UNSIGNED_INT);

		currentPos += font->GetGlyphData(currentChar)->advance.x;
	}
}