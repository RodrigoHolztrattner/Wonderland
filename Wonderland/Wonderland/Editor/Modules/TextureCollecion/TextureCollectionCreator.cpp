////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureCollectionCreator.h"
#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

TextureCollection::TextureCollectionCreator::TextureCollectionCreator()
{
	// Set the initial data
	// ...
}

TextureCollection::TextureCollectionCreator::~TextureCollectionCreator()
{
	// Need to clear all texture data
	// ...
}

bool TextureCollection::TextureCollectionCreator::AddTextureFromData(const char* _textureName, uint16_t _width, uint16_t _height, unsigned char* _data)
{


	return true;
}

bool TextureCollection::TextureCollectionCreator::AddTextureFromDataUsingCoordinates(const char* _textureName, uint16_t _width, uint16_t _height, unsigned char* _data, float _fromX, float _fromY, float _toX, float _toY)
{


	return true;
}

bool TextureCollection::TextureCollectionCreator::AddTextureFromFile(const char* _textureName, const char* _textureFile)
{
	// Our controll variables
	int texWidth, texHeight, texChannels;

	// Load the image data
	stbi_uc* pixels = stbi_load(_textureFile, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

	// Set the image size
	uint32_t imageSize = texWidth * texHeight * 4;

	// Check if we loaded correctly
	if (!pixels)
	{
		throw std::runtime_error("failed to load texture image!");

		return false;
	}

	// Set the texture data
	TextureCollectionData textureData = {};
	textureData.name.SetString(_textureName);
	textureData.width = texWidth;
	textureData.height = texHeight;
	textureData.data = new unsigned char[imageSize];
	memcpy(textureData.data, pixels, imageSize);

	// Free the image
	stbi_image_free(pixels);

	// Insert the texture data
	m_TextureData.push_back(textureData);

	//
	m_Width = textureData.width;
	m_Height = textureData.height;

	return true;
}

bool TextureCollection::TextureCollectionCreator::SaveTextureCollection(const char* _collectionName, const char* _collectionFileName)
{
	// Check if we have at last one texture to save
	if (!m_TextureData.size())
	{
		// We need at last one texture!
		return false;
	}

	// Create the byte array we will use to put all data
	std::vector<unsigned char> byteArray;

	// Set the collection header data
	TextureCollectionHeader headerData = {};
	headerData.collectionName.SetString(_collectionName);
	headerData.width = m_Width;
	headerData.height = m_Height;
	headerData.totalTextures = m_TextureData.size();

	// Set the texture size
	uint32_t textureSize = m_Width * m_Height * 4;
	
	// Serialize the header data
	headerData.SerializeAndAppend(byteArray);

	// For each texture
	for (int i = 0; i < m_TextureData.size(); i++)
	{
		// Serialize the texture data and append
		m_TextureData[i].SerializeAndAppend(byteArray);

		// Increment the vector size
		byteArray.resize(byteArray.size() + textureSize);

		// Copy the data
		memcpy(&byteArray.data()[byteArray.size() - textureSize], m_TextureData[i].data, textureSize);
	}

	// Create the file
	std::ofstream collectionFile(_collectionFileName, std::ios::out | std::ios::binary);
	if (!collectionFile.is_open())
	{
		// Error creating the file
		return false;
	}

	// Write the data
	collectionFile.write((char*)byteArray.data(), byteArray.size());

	// Close the file
	collectionFile.close();

	return true;
}