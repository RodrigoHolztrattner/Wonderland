////////////////////////////////////////////////////////////////////////////////
// Filename: ModelComposerUnpacker.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"
#include "ModelComposerFormat.h"

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
NamespaceBegin(ModelComposer)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelComposerUnpacker
////////////////////////////////////////////////////////////////////////////////
class ModelComposerUnpacker
{
private:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	ModelComposerUnpacker();
	~ModelComposerUnpacker();
	
	// Unpack texture collection
	ModelComposerFormat& UnpackModel(std::vector<unsigned char>& _collectionData, bool& _result);

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
private: //////

	// The unpacked data
	ModelComposerFormat m_UnpackedData;
};

// Texture Collection Module
NamespaceEnd(ModelComposer)