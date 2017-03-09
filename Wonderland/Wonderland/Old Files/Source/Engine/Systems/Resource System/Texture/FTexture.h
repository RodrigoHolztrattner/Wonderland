////////////////////////////////////////////////////////////////////////////////
// Filename: FTexture.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FTexture_H_
#define _FTexture_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\IResource.h"
#include "..\..\Support\Math\WMath.h"

/////////////
// DEFINES //
/////////////

/*
 *	=> Texture:
 *
 *	- É um recurso.
 *	- Pode possuir uma array com os pixels originais ou apenas o buffer de textura.
 *	- Por enquanto apenas suporta uma unica textura usando ou não um atlas.
 *	- É utilizado um formato interno proprio para armazenar a textura (another texture format (.atf)).
 *
 */

////////////////////////////////////////////////////////////////////////////////
// Class name: FTexture
////////////////////////////////////////////////////////////////////////////////
class FTexture : public IResource
{
private:

	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	FTexture();
	FTexture(const FTexture&);
	~FTexture();

	// Release this resource (remember always to call this when the resource is not needed anymore)
	void Release();

	// Set without loading a id handle for this texture
	void SetHandleWithoutLoading(unsigned int _handle)
	{
		m_TextureHandle = _handle;
	}

	// Return the texture handle
	unsigned int GetHandle()
	{
		return m_TextureHandle;
	}

	// Put this texture inside a shader program
	bool SetShaderTexture(unsigned int _shaderProgram, unsigned int _textureSlot, unsigned int _texturePosition, const char* _textureName);

	// Return the texture size
	WVector2 TextureSize()
	{
		return m_TextureSize;
	}

	// Return a pixel info for the given texture coordinate
	WVector4 PixelInfo(WVector2 _textureCoordinate);

protected:

	// Load this resource (protected because this will be called by the GetResource() method (and not by the user))
	void Load(unsigned char* _resourceData);

	// Update this resource
	void Update(float _time);

private:

	// Load a targe image
	bool LoadTarga(unsigned char* _resourceData, unsigned int _textureUnit);

private:

	// The texture handle
	unsigned int m_TextureHandle;

	// The texture size
	WVector2 m_TextureSize;

	// The texture raw data
	unsigned char* m_TextureRawData;
};

#endif
