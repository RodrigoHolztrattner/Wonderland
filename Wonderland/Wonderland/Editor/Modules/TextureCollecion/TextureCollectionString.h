////////////////////////////////////////////////////////////////////////////////
// Filename: TextureCollectionString.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>

#include "..\NamespaceDefinitions.h"

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

// TextureCollection Resource Module
NamespaceBegin(TextureCollection)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureCollectionString
////////////////////////////////////////////////////////////////////////////////
class TextureCollectionString
{
public:

	static const int MaxStringSize = 63;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	TextureCollectionString();
	TextureCollectionString(const char* _string);
	~TextureCollectionString();

//////////////////
// MAIN METHODS //
public: //////////

	void operator =(const char* _string);

	void SetString(const char* _string);

	void SetString(const char* _string, uint32_t _stringSize);

	char* GetString();

	bool IsEqual(TextureCollectionString& _string, uint32_t _stringSize = -1);

	bool IsEqual(const char* _string, uint32_t _stringSize = -1);

///////////////
// VARIABLES //
private: //////

	// The internal string
	char m_String[MaxStringSize];
};

// TextureCollection Resource Module
NamespaceEnd(TextureCollection)