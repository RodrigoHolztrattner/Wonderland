////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ModelComposerCreator.h"
#include <iostream>
#include <fstream>

ModelComposer::ModelComposerCreator::ModelComposerCreator()
{
	// Set the initial data
	// ...
}

ModelComposer::ModelComposerCreator::~ModelComposerCreator()
{
	// Need to clear model data
	// ...
}

bool ModelComposer::ModelComposerCreator::CreateFromObjFile(const char* _objFileName)
{
	return false; //TODO: implementar
}

bool ModelComposer::ModelComposerCreator::CreateFromCurrentData()
{
	// Check if we have at last one vertex and index
	if (!m_VertexArray.size() || !m_IndexArray.size())
	{
		return false;
	}

	// Set the model data
	m_Model.vertices = m_VertexArray;
	m_Model.indexes = m_IndexArray;
	m_Model.totalVertices = m_VertexArray.size();
	m_Model.totalIndexes = m_IndexArray.size();

	return true;
}

bool ModelComposer::ModelComposerCreator::SaveModel(const char* _modelName, const char* _modelFileName)
{
	// Create the byte array we will use to put all data
	std::vector<unsigned char> byteArray;

	// Set the remaining model data
	m_Model.name.SetString(_modelName);

	// Serialize the model data
	m_Model.SerializeAndAppend(byteArray);

	// Create the file
	std::ofstream collectionFile(_modelFileName, std::ios::out | std::ios::binary);
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

void ModelComposer::ModelComposerCreator::AddVertex(ModelComposerVertexFormat _vertex, bool _addIndex)
{
	m_VertexArray.push_back(_vertex);
	if(_addIndex) m_IndexArray.push_back(m_IndexArray.size());
}

void ModelComposer::ModelComposerCreator::AddIndex(ModelComposerIndexFormat _index)
{
	m_IndexArray.push_back(_index);
}