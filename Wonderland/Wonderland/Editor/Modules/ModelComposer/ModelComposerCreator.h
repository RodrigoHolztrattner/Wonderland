////////////////////////////////////////////////////////////////////////////////
// Filename: ModelComposerCreator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"
#include "ModelComposerFormat.h"
#include "ModelComposerString.h"

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

// ModelComposer Module
NamespaceBegin(ModelComposer)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelComposerCreator
////////////////////////////////////////////////////////////////////////////////
class ModelComposerCreator
{
private:

//////////////////
// CONSTRUCTORS //
public: //////////

	 // Constructor / destructor
	ModelComposerCreator();
	~ModelComposerCreator();

//////////////////
// MAIN METHODS //
public: //////////

	// Create from a given obj file
	bool CreateFromObjFile(const char* _objFileName);

	// Create from the current data
	bool CreateFromCurrentData();

	// Save the current model
	bool SaveModel(const char* _modelName, const char* _modelFileName);

public:

	// Add a vertex
	void AddVertex(ModelComposerVertexFormat _vertex, bool _addIndex = false);

	// Add an index
	void AddIndex(ModelComposerIndexFormat _index);

///////////////
// VARIABLES //
private: //////

	// The current model object
	ModelComposerFormat m_Model;

	// The current vertex array
	std::vector<ModelComposerVertexFormat> m_VertexArray;

	// The current index array
	std::vector<ModelComposerIndexFormat> m_IndexArray;
};

// ModelComposer Module
NamespaceEnd(ModelComposer)