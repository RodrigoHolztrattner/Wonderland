///////////////////////////////////////////////////////////////////////////////
// Filename: FTexture.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FTexture.h"
#include "..\..\Video\FGraphic.h"
#include "..\..\Support\File\FDataSeeker.h"

FTexture::FTexture()
{

}

FTexture::FTexture(const FTexture& other)
{
}

FTexture::~FTexture()
{
}

void FTexture::Release()
{
	// Call the base function
	IResource::Release();
}

void FTexture::Load(unsigned char* _resourceData)
{
	bool result;

	// Load the targa image
	result = LoadTarga(_resourceData, 0); // _textureUnit ?
	if (!result)
	{
		// ASSERT
		return;
	}

	return;
}

void FTexture::Update(float _time)
{
	// ...
	// ...
}

bool FTexture::LoadTarga(unsigned char* _resourceData, unsigned int _textureUnit)
{
	FDataSeeker dataSeeker;
	int width, height, bpp, imageSize;
	unsigned int count;
	TargaHeader targaFileHeader;

	// Get the file header.
	dataSeeker.Get(sizeof(TargaHeader), _resourceData, &targaFileHeader);

	// Get the important information from the header.
	width = (int)targaFileHeader.width;
	height = (int)targaFileHeader.height;
	bpp = (int)targaFileHeader.bpp;

	// Set the texture size
	m_TextureSize.x = width;
	m_TextureSize.y = height;

	// Check that it is 32 bit and not 24 bit.
	if (bpp != 32)
	{
		return false;
	}

	// Calculate the size of the 32 bit image data.
	imageSize = width * height * 4;

	// Get space for the raw data
	m_TextureRawData = new unsigned char[imageSize];

	// Read in the targa image data.
	dataSeeker.Get(imageSize, _resourceData, m_TextureRawData);

	// Set the unique texture unit in which to store the data.
	glActiveTexture(GL_TEXTURE0 + _textureUnit);

	// Generate an ID for the texture.
	glGenTextures(1, &m_TextureHandle);

	// Bind the texture as a 2D texture.
	glBindTexture(GL_TEXTURE_2D, m_TextureHandle);

	// Load the image data into the texture unit.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_TextureRawData);

	// Set the texture color to either wrap around or clamp to the edge.
	if (true)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	// Set the texture filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Generate mipmaps for the texture.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set that the texture is loaded.
//	m_Loaded = true;

	return true;
}

bool FTexture::SetShaderTexture(unsigned int _shaderProgram, unsigned int _textureSlot, unsigned int _texturePosition, const char* _textureName)
{
	unsigned int location;

	// Set the active texture and bind it
	glActiveTexture(_textureSlot);
	glBindTexture(GL_TEXTURE_2D, GetHandle());

	// Set the texture in the pixel shader to use the data from the first texture unit.
	location = glGetUniformLocation(_shaderProgram, _textureName);
	if (location == -1)
	{
		return false;
	}
	glUniform1i(location, _texturePosition);

	return true;
}

WVector4 FTexture::PixelInfo(WVector2 _textureCoordinate)
{
	WVector2 coordinates;
	unsigned int pixelIndex;

	// Get the real coordinates
	coordinates.x = Lerp(0.0f, m_TextureSize.x, _textureCoordinate.x);
	coordinates.y = Lerp(0.0f, m_TextureSize.y, _textureCoordinate.y);

	// Set the pixel index
	pixelIndex = (coordinates.y * m_TextureSize.y * 4) + coordinates.x * 4; // Maybe is the inverse order

	// Return the pixel info
	return WVector4(m_TextureRawData[pixelIndex + 0] / 256.0f, m_TextureRawData[pixelIndex + 1] / 256.0f, m_TextureRawData[pixelIndex + 2] / 256.0f, m_TextureRawData[pixelIndex + 3] / 256.0f);
}