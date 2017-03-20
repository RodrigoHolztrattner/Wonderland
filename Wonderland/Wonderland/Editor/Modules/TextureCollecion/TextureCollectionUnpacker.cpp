////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureCollectionUnpacker.h"

TextureCollection::TextureCollectionUnpacker::TextureCollectionUnpacker()
{
	// Set the initial data
	// ...
}

TextureCollection::TextureCollectionUnpacker::~TextureCollectionUnpacker()
{
}

std::vector<TextureCollection::TextureCollectionData>& TextureCollection::TextureCollectionUnpacker::UnpackCollection(std::vector<unsigned char>& _collectionData, bool& _result)
{
	// Clear the unpacked data
	m_UnpackedData.clear();

	// Set the initial position inside the data
	uint32_t currentDataPosition = 0;

	// Read the header
	currentDataPosition = m_HeaderData.Deserialize(_collectionData, currentDataPosition);

	// Calc the texture size
	uint32_t textureSize = m_HeaderData.width * m_HeaderData.height * 4;

	// For each texture
	for (int i = 0; i < m_HeaderData.totalTextures; i++)
	{
		// The new texture data
		TextureCollectionData textureData = {};

		// Set the data
		currentDataPosition = textureData.Deserialize(_collectionData, currentDataPosition);

		// Set the texture data location
		textureData.data = &_collectionData[currentDataPosition];
		currentDataPosition += textureSize;

		// Add the texture to the unpacked data
		m_UnpackedData.push_back(textureData);
	}

	// Set the result to true
	_result = true;

	return m_UnpackedData;
}