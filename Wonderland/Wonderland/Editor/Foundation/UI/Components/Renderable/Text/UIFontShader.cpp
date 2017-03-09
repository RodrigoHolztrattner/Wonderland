////////////////////////////////////////////////////////////////////////////////
// Filename: UIFontShader.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIFontShader.h"
#include "..\..\..\..\Context\Context.h"

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
	
	// Add the vertices
	m_FrameObject.AddVertex(Vector3(0, 1, 0), Vector2(0, 0));
	m_FrameObject.AddVertex(Vector3(1, 1, 0), Vector2(1, 0));
	m_FrameObject.AddVertex(Vector3(0, 0, 0), Vector2(0, 1));
	m_FrameObject.AddVertex(Vector3(1, 0, 0), Vector2(1, 1));

	// Add the indexes
	m_FrameObject.AddIndex(0);
	m_FrameObject.AddIndex(1);
	m_FrameObject.AddIndex(2);
	m_FrameObject.AddIndex(2);
	m_FrameObject.AddIndex(1);
	m_FrameObject.AddIndex(3);

	// Make the frame object
	result = m_FrameObject.MakeFrame();
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
	worldMatrix			= Context::GetInstance()->GetWorldMatrix();
	viewMatrix			= Context::GetInstance()->GetViewMatrix();
	projectionMatrix	= Context::GetInstance()->GetOrthoMatrix();

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

#include "..\..\Frame\UIFrameComponent.h"
#include "..\..\State\UIStateComponent.h"
#include "..\..\..\..\ECS\ECS_System.h"

void UIFontShader::RenderAux(UITextComponent* _object)
{
	unsigned int location;
	WMatrix4 localMatrix;
	Vector4 glyphTextureCoordinate;

	// Enable scissor
	glEnable(GL_SCISSOR_TEST);

	// Get the frame and state components
	UIFrameComponent* frameComponent = (UIFrameComponent*)_object->GetEntityComponentById(UIFrameComponent::ClassComponentID());
	UIStateComponent* stateComponent = (UIStateComponent*)_object->GetEntityComponentById(UIStateComponent::ClassComponentID());

	// Get the screen frame
	Vector4 screenFrame = frameComponent->GetScreenFrame();

	// Set the position and the size
	Vector3 position = Vector3::TransformToScreenPosition(Vector2(screenFrame.x, screenFrame.y), Vector2(screenFrame.width, screenFrame.height));
	Vector3 size = Vector3::TransformToScreenSize(Vector2(screenFrame.width, screenFrame.height));
	position.z = stateComponent->GetDepthOrder();

	// Set the scissor area
	Vector4 frameValue = frameComponent->GetFrame();
	glScissor(frameValue.x, Context::GetInstance()->GetScreenHeight() - frameValue.y - frameValue.height, frameValue.width, frameValue.height);
	
	// Get the font object
	UIFont* font = _object->GetFont();

	// Set texture
	location = m_ShaderProgram.GetUniformLocation("fontTexture");
	if (location == -1)
	{
		return;
	}
	GLuint texId = font->GetTexture()->BindTexture(0);
	glUniform1i(location, texId);

	// Set the font color
	location = m_ShaderProgram.GetUniformLocation("baseColor");
	if (location == -1)
	{
		return;
	}
	glUniform4f(location, _object->GetTextColor().x, _object->GetTextColor().y, _object->GetTextColor().z, _object->GetTextColor().w);

	// The current char pos
	int currentPos = 0;

	// For each char
	for (int i = 0; i < _object->GetText().size() + (_object->IsCursorActive() ? 1 : 0); i++)
	{
		UIChar currentChar;

		// Check if we are rendering the cursor
		if (i == _object->GetText().size())
		{
			// Get the cursor data
			currentChar = _object->GetCursorData();

			// Set the position and the size
			position = currentChar.position;
			size = currentChar.size;
			position.z = stateComponent->GetDepthOrder() - 0.0002;
		}
		else
		{
			// Get the current char
			currentChar = _object->GetText()[i];

			// Set the position and the size
			position = currentChar.position;
			size = currentChar.size;
			position.z = stateComponent->GetDepthOrder() - 0.0001;
		}

		// Make the local matrix
		localMatrix.BuildTransform(position, Vector3(0, 0, 0), size);
		
		// Set the local matrix
		location = m_ShaderProgram.GetUniformLocation("localMatrix");
		if (location == -1)
		{
			return;
		}
		glUniformMatrix4fv(location, 1, false, localMatrix.v);

		// Set the glyph texture coord vector
		glyphTextureCoordinate = font->GetGlyphData(currentChar.originalChar)->texCoordinates;

		// Set glyph texture coordinates
		location = m_ShaderProgram.GetUniformLocation("glyphTextureCoord");
		if (location == -1)
		{
			return;
		}
		glUniform4f(location, glyphTextureCoordinate.x, glyphTextureCoordinate.y, glyphTextureCoordinate.z, glyphTextureCoordinate.w);

		// Render our frame object
		(font->GetGlyphFrame(currentChar.originalChar))->RenderFrame(GL_TRIANGLES, GL_UNSIGNED_INT);

		// Increment the current pos
		currentPos += font->GetGlyphData(currentChar.originalChar)->advance.x;
	}

	// Disable scissor
	glDisable(GL_SCISSOR_TEST);
}