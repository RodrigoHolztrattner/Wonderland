////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderFrame.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderFrame.h"
#include <stdexcept>

ShaderFrame::ShaderFrame()
{
}

ShaderFrame::ShaderFrame(const ShaderFrame& other)
{
}

ShaderFrame::~ShaderFrame()
{
}

void ShaderFrame::AddVertex(Vector3 _position, Vector2 _textureCoordinates)
{
	m_VertexArray.Add(VertexType(_position, _textureCoordinates));
}

void ShaderFrame::AddVertex(VertexType _vertex)
{
	m_VertexArray.Add(_vertex);
}

void ShaderFrame::AddIndex(unsigned int _index)
{
	m_IndexArray.Add(_index);
}

bool ShaderFrame::MakeFrame()
{
	VertexType* vertices;
	unsigned int* indices;

	// Alocate space for all vertices and indexes
	vertices = new VertexType[m_VertexArray.Size()];
	indices = new unsigned int[m_IndexArray.Size()];

	// Set the vertices
	for (int i = 0; i < m_VertexArray.Size(); i++)
	{
		// Set vertice
		vertices[i] = m_VertexArray[i];
	}

	// Set the indexes
	for (int i = 0; i < m_IndexArray.Size(); i++)
	{
		// Set the index
		indices[i] = m_IndexArray[i];
	}

	// Allocate an OpenGL vertex array object.
	glGenVertexArrays(1, &m_VertexArrayId);

	// Bind the vertex array object to store all the buffers and vertex attributes we create here.
	glBindVertexArray(m_VertexArrayId);

	// Generate an ID for the vertex buffer.
	glGenBuffers(1, &m_VertexBufferId);

	// Bind the vertex buffer and load the vertex (position and color) data into the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_VertexArray.Size() * sizeof(VertexType), vertices, GL_STATIC_DRAW);

	// Enable the two vertex array attributes.
	glEnableVertexAttribArray(0);  // Vertex position.
	glEnableVertexAttribArray(1);  // Vertex coordinates.

	// Specify the location and format of the position portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

	// Specify the location and format of the color portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char*)NULL + (3 * sizeof(float)));

	// Generate an ID for the index buffer.
	glGenBuffers(1, &m_IndexBufferId);

	// Bind the index buffer and load the index data into it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexArray.Size() * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Now that the buffers have been loaded we can release the array data.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ShaderFrame::RenderFrame(unsigned int _mode, unsigned int _type)
{
	// Error check
	GLenum error = glGetError();
	if (error != 0)
	{
		throw std::runtime_error("Render Frame chegou com erro!");
	}

	// Bind the vertex array object that stored all the information about the vertex and index buffers.
	glBindVertexArray(m_VertexArrayId);

	// Render the vertex buffer using the index buffer.
	glDrawElements(_mode, m_IndexArray.Size(), _type, 0);

	// Error check
	error = glGetError();
	if (error != 0)
	{
		throw std::runtime_error("Render Frame deu erro!");
	}
}