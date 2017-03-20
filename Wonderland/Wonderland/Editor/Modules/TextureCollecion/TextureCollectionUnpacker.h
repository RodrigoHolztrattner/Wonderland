////////////////////////////////////////////////////////////////////////////////
// Filename: TextureCollectionUnpacker.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"
#include "TextureCollectionFormat.h"

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
// Class name: TextureCollectionUnpacker
////////////////////////////////////////////////////////////////////////////////
class TextureCollectionUnpacker
{
private:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	TextureCollectionUnpacker();
	~TextureCollectionUnpacker();
	
	// Unpack texture collection
	std::vector<TextureCollectionData>& UnpackCollection(std::vector<unsigned char>& _collectionData, bool& _result);

	// Return the header data
	TextureCollectionHeader& GetCollectionHeader() { return m_HeaderData; }

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
private: //////

	// The header data
	TextureCollectionHeader m_HeaderData;

	// The unpacked data
	std::vector<TextureCollectionData> m_UnpackedData;
};

// Texture Collection Module
NamespaceEnd(TextureCollection)