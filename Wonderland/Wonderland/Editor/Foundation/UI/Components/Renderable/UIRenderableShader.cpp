////////////////////////////////////////////////////////////////////////////////
// Filename: UIRenderableShader.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIRenderableShader.h"

#include <fstream>
using namespace std;

///////////////
// NAMESPACE //
///////////////

UIRenderableShader::UIRenderableShader()
{
}

UIRenderableShader::UIRenderableShader(const UIRenderableShader& other)
{
}

UIRenderableShader::~UIRenderableShader()
{
}

bool UIRenderableShader::Initialize()
{
	bool result;

	// Set the shard data
	m_VertexShard.SetData(LoadShardSourceFile("color.vs"));
	m_FragmentShard.SetData(LoadShardSourceFile("color.fs"));

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

bool UIRenderableShader::PrepareToRender()
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

#include "..\Frame\UIFrameComponent.h"
#include "..\..\..\ECS\ECS_System.h"

void UIRenderableShader::RenderAux(UIRenderableComponent* _object)
{
	unsigned int location;
	WMatrix4 localMatrix;

	// Get the frame component
	UIFrameComponent* frameComponent = (UIFrameComponent*)_object->GetEntityComponentById(UIFrameComponent::ClassComponentID());
	
	// Set the position and size
	Vector3 worldPosition = frameComponent->GetFramePosition();
	worldPosition.x /= 800.0f;
	worldPosition.y /= 600.0f;
	Vector3 worldSize = frameComponent->GetFrameSize();
	worldSize.x /= 800.0f;
	worldSize.y /= 600.0f;

	Vector3 position = Vector3::TransformToScreenPosition(worldPosition, worldSize);
	Vector3 size = Vector3::TransformToScreenSize(worldSize);

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

	// Set the view color
	location = m_ShaderProgram.GetUniformLocation("baseColor");
	if (location == -1)
	{
		return;
	}
	glUniform4f(location, _object->GetColor().x, _object->GetColor().y, _object->GetColor().z, _object->GetColor().w);

	// Render our frame object
	m_FrameObject.RenderFrame(GL_TRIANGLES, GL_UNSIGNED_INT);
}