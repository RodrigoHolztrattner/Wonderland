////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderFrame.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\Math.h"
#include "..\..\Support\Container\Array\Array.h"

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
// Class name: ShaderFrame
////////////////////////////////////////////////////////////////////////////////
class ShaderFrame
{
	// The vertex type
	struct VertexType
	{
		VertexType() {}
		VertexType(Vector3 _position, Vector2 _textureCoordinates)
		{
			position = _position;
			textureCoordinates = _textureCoordinates;
		}

		Vector3 position;
		Vector2 textureCoordinates;
	};

public:
	ShaderFrame();
	ShaderFrame(const ShaderFrame&);
	~ShaderFrame();

	// Add a vertex
	void AddVertex(Vector3 _position, Vector2 _textureCoordinates);
	void AddVertex(VertexType _vertex);

	// Add a index
	void AddIndex(unsigned int _index);

	// Make the frame
	bool MakeFrame();

	// Render this frame
	void RenderFrame(unsigned int _mode, unsigned int _type);

private:

	// The vertex array
	Array<VertexType> m_VertexArray;

	// The index array
	Array<unsigned int> m_IndexArray;

	// The vertex, index and buffer Ids
	unsigned int m_VertexArrayId;
	unsigned int m_VertexBufferId;
	unsigned int m_IndexBufferId;

private:



};