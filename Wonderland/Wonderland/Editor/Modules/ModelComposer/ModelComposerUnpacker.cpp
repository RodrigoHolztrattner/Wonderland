////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ModelComposerUnpacker.h"

ModelComposer::ModelComposerUnpacker::ModelComposerUnpacker()
{
	// Set the initial data
	// ...
}

ModelComposer::ModelComposerUnpacker::~ModelComposerUnpacker()
{
}

ModelComposer::ModelComposerFormat& ModelComposer::ModelComposerUnpacker::UnpackModel(std::vector<unsigned char>& _collectionData, bool& _result)
{
	// Set the initial position inside the data
	uint32_t currentDataPosition = 0;

	// Read the model data
	currentDataPosition = m_UnpackedData.Deserialize(_collectionData, currentDataPosition);

	// Set the result to true
	_result = true;

	return m_UnpackedData;
}