////////////////////////////////////////////////////////////////////////////////
// Filename: Texture2D.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <vector>

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
// Class name: Texture2D
////////////////////////////////////////////////////////////////////////////////
class Texture2D
{
public:
	Texture2D();
	Texture2D(const Texture2D&);
	~Texture2D();

	// Set the internal generation data
	void SetInternalGenerationData(GLenum _internalFormat, GLenum _format, GLenum _type, GLint _border);

	// Pre-create the texture
	void PreCreateTexture();

	// Create the Texture from a local file
	bool CreateTextureFromLocalFile(char* filename);

	// Create the Texture from memory
	bool CreateTextureFromMemory(unsigned int _width, unsigned int _height, void* _data);

	// Apply the texture parameters
	void ApplyTextureParameters(bool _generateMipmaps = true);

	// Apply a texture parameter from a lambda function
	void ApplyTextureParameters(void(*_func)());

	// Set a sub-image
	void SetSubImage(int _offsetX, int _offsetY, int _width, int _height, void* _data);

	// Set the parameters
	void SetParameter(GLenum _name, GLint _param);

	// Generate the mipmaps
	void GenerateMipmaps();

	// End the creation
	void EndCreation();

	// Bind the texture
	GLuint BindTexture(unsigned int _location)
	{
		glActiveTexture(GL_TEXTURE0 + _location);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
		return _location;
	}

private:

	// If the texture was loaded
	bool m_Loaded;

	// The opengl texture ID
	GLuint m_TextureId;

	// The internal data
	GLenum m_InternalFormat;
	GLenum m_Format;
	GLenum m_Type;
	GLint m_Border;

	// The parameter array
	std::vector<GLenum> m_NameArray;
	std::vector<GLint> m_Param;
};