////////////////////////////////////////////////////////////////////////////////
// Filename: UIBorderShader.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIBorderShader.h"
#include "..\..\..\..\Context\Context.h"

#include <fstream>
using namespace std;

///////////////
// NAMESPACE //
///////////////

UIBorderShader::UIBorderShader()
{
}

UIBorderShader::UIBorderShader(const UIBorderShader& other)
{
}

UIBorderShader::~UIBorderShader()
{
}

bool UIBorderShader::Initialize()
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
	m_FrameObject.AddVertex(Vector3(0, 0, 0), Vector2(0, 0));
	m_FrameObject.AddVertex(Vector3(1, 1, 0), Vector2(1, 1));

	// Add the indexes
	m_FrameObject.AddIndex(0);
	m_FrameObject.AddIndex(1);

	// Make the frame object
	result = m_FrameObject.MakeFrame();
	if (!result)
	{
		return false;
	}

	return true;
}

bool UIBorderShader::PrepareToRender()
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

void UIBorderShader::RenderAux(UIBorderComponent* _object)
{
	unsigned int location;
	WMatrix4 localMatrix;

	// Get the frame component
	UIFrameComponent* frameComponent = (UIFrameComponent*)_object->GetEntityComponentById(UIFrameComponent::ClassComponentID());
	UIStateComponent* stateComponent = (UIStateComponent*)_object->GetEntityComponentById(UIStateComponent::ClassComponentID());

	// Get the base frame
	Vector4 baseFrame = Vector4(frameComponent->GetFramePosition(), frameComponent->GetFrameSize());

	// Set the line width
	glLineWidth(_object->GetBorderSize());

	// Set the half border size
	unsigned int halfBorderSize = _object->GetBorderSize() / 2;

	// Set the view color
	location = m_ShaderProgram.GetUniformLocation("baseColor");
	if (location == -1)
	{
		return;
	}
	glUniform4f(location, _object->GetBorderColor().x, _object->GetBorderColor().y, _object->GetBorderColor().z, _object->GetBorderColor().w);
	
	// We have 4 lines to draw
	Vector3 positions[4];
	Vector3 sizes[4];

	// 1
	positions[0] = Vector3(baseFrame.x + halfBorderSize, baseFrame.y, 0);
	sizes[0] = Vector3(0, baseFrame.height-1 , 1);

	// 2
	positions[1] = Vector3(baseFrame.x + baseFrame.width - halfBorderSize, baseFrame.y, 0);
	sizes[1] = Vector3(0, baseFrame.height-1, 1);

	// 3
	positions[2] = Vector3(baseFrame.x+1, baseFrame.y + halfBorderSize, 0);
	sizes[2] = Vector3(baseFrame.width-1, 0, 1);

	// 4
	positions[3] = Vector3(baseFrame.x+1, baseFrame.y + baseFrame.height - halfBorderSize, 0);
	sizes[3] = Vector3(baseFrame.width-1, 0, 1);

	// For each line
	for (int i = 0; i < 4; i++)
	{
		// Set the position and the size
		positions[i].x /= Context::GetInstance()->GetScreenWidth();
		positions[i].y /= Context::GetInstance()->GetScreenHeight();
		sizes[i].x /= Context::GetInstance()->GetScreenWidth();
		sizes[i].y /= Context::GetInstance()->GetScreenHeight();
		Vector3 position = Vector3::TransformToScreenPosition(positions[i], sizes[i]);
		Vector3 size = Vector3::TransformToScreenSize(sizes[i]);

		// Set the depth order
		position.z = stateComponent->GetDepthOrder() - 0.0001;

		// Make the local matrix
		localMatrix.BuildTransform(position, Vector3(0, 0, 0), size);

		// Set the local matrix
		location = m_ShaderProgram.GetUniformLocation("localMatrix");
		if (location == -1)
		{
			return;
		}
		glUniformMatrix4fv(location, 1, false, localMatrix.v);

		// Render our frame object
		m_FrameObject.RenderFrame(GL_LINES, GL_UNSIGNED_INT);
	}
}