////////////////////////////////////////////////////////////////////////////////
// Filename: TextureCollectionCreator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"
#include "TextureCollectionFormat.h"
#include "TextureCollectionString.h"

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

///////////////
// NAMESPACE //
///////////////

// Texture Collection Module
NamespaceBegin(TextureCollection)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureCollectionCreator
////////////////////////////////////////////////////////////////////////////////
class TextureCollectionCreator
{
private:

//////////////////
// CONSTRUCTORS //
public: //////////

	 // Constructor / destructor
	TextureCollectionCreator();
	~TextureCollectionCreator();

//////////////////
// MAIN METHODS //
public: //////////

	// Add a texture from data
	bool AddTextureFromData(const char* _textureName, uint16_t _width, uint16_t _height, unsigned char* _data);

	// Add a texture from data using texture coordinates
	bool AddTextureFromDataUsingCoordinates(const char* _textureName, uint16_t _width, uint16_t _height, unsigned char* _data, float _fromX, float _fromY, float _toX, float _toY);

	// Add a texture from file
	bool AddTextureFromFile(const char* _textureName, const char* _textureFile);

	// Save the current texture collection
	bool SaveTextureCollection(const char* _collectionName, const char* _collectionFileName);

	/*
	
		criar a partir de texturas ou
		criar a partir de texture coordinates em um atlas ou
		manusear um grupo ja existente

	*/

///////////////
// VARIABLES //
private: //////

	// The texture data
	std::vector<TextureCollectionData> m_TextureData;

	// The collection dimension
	uint16_t m_Width, m_Height;
};

// Texture Collection Module
NamespaceEnd(TextureCollection)