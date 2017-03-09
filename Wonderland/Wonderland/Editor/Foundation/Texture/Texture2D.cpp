////////////////////////////////////////////////////////////////////////////////
// Filename: Texture2D.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Texture2D.h"

///////////////
// NAMESPACE //
///////////////

Texture2D::Texture2D()
{
	// Set the initial data
	m_InternalFormat = GL_RGBA;
	m_Format = GL_BGRA;
	m_Type = GL_UNSIGNED_BYTE;
	m_Border = 0;
	m_Loaded = false;
}

Texture2D::Texture2D(const Texture2D& other)
{
}

Texture2D::~Texture2D()
{
}

void Texture2D::SetInternalGenerationData(GLenum _internalFormat, GLenum _format, GLenum _type, GLint _border)
{
	// Set the internal data
	m_InternalFormat = _internalFormat;
	m_Format = _format;
	m_Type = _type;
	m_Border = _border;
}

void Texture2D::PreCreateTexture()
{
	// Set the unique texture unit in which to store the data.
	glActiveTexture(GL_TEXTURE0);

	// Generate an ID for the texture.
	glGenTextures(1, &m_TextureId);

	// Bind the texture as a 2D texture.
	glBindTexture(GL_TEXTURE_2D, m_TextureId);

}

bool Texture2D::CreateTextureFromLocalFile(char* filename)
{
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

	int error, width, height, bpp, imageSize;
	FILE* filePtr;
	unsigned int count;
	TargaHeader targaFileHeader;
	unsigned char* targaImage;

	// Open the targa file for reading in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Get the important information from the header.
	width = (int)targaFileHeader.width;
	height = (int)targaFileHeader.height;
	bpp = (int)targaFileHeader.bpp;

	// Check that it is 32 bit and not 24 bit.
	if (bpp != 32)
	{
		return false;
	}

	// Calculate the size of the 32 bit image data.
	imageSize = width * height * 4;

	// Allocate memory for the targa image data.
	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return false;
	}

	// Read in the targa image data.
	count = fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Load the image data into the texture unit.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, targaImage);

	// Set the texture color to either wrap around or clamp to the edge.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set the texture filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Generate mipmaps for the texture.
	glGenerateMipmap(GL_TEXTURE_2D);

	// End
	glBindTexture(GL_TEXTURE_2D, 0);

	// Release the targa image data.
	delete[] targaImage;
	targaImage = 0;

	return true;
}

bool Texture2D::CreateTextureFromMemory(unsigned int _width, unsigned int _height, void* _data)
{
	// Create the texture
	glTexImage2D(GL_TEXTURE_2D, m_Border, m_InternalFormat, _width, _height, 0, m_Format, m_Type, _data);

	return true;
}

void Texture2D::ApplyTextureParameters(bool _generateMipmaps)
{
	// Check if we should generate the mipmaps
	if (_generateMipmaps)
	{
		// Generate the mipmaps
		GenerateMipmaps();
	}

	// Check if we have a param list
	if (m_NameArray.size())
	{
		// For each param
		for (int i = 0; i < m_NameArray.size(); i++)
		{
			// Apply the param
			glTexParameteri(GL_TEXTURE_2D, m_NameArray[i], m_Param[i]);
		}
	}
	// Use the default param list
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		_generateMipmaps ? glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) : glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

void Texture2D::ApplyTextureParameters(void(*_func)())
{
	_func();
}

void Texture2D::SetSubImage(int _offsetX, int _offsetY, int _width, int _height, void* _data)
{
	glTexSubImage2D(GL_TEXTURE_2D, 0, _offsetX, _offsetY, _width, _height, m_Format, m_Type, _data);
}

void Texture2D::GenerateMipmaps()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::SetParameter(GLenum _name, GLint _param)
{
	m_NameArray.push_back(_name);
	m_Param.push_back(_param);
}

void Texture2D::EndCreation()
{
	// End
	glBindTexture(GL_TEXTURE_2D, 0);

	// Set that the texture is loaded.
	m_Loaded = true;
}