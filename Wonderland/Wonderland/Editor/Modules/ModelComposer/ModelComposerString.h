////////////////////////////////////////////////////////////////////////////////
// Filename: ModelComposerString.h
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

// ModelComposer Module
NamespaceBegin(ModelComposer)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelComposerString
////////////////////////////////////////////////////////////////////////////////
class ModelComposerString
{
public:

	static const int MaxStringSize = 63;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	ModelComposerString();
	ModelComposerString(const char* _string);
	~ModelComposerString();

//////////////////
// MAIN METHODS //
public: //////////

	void operator =(const char* _string);

	void SetString(const char* _string);

	void SetString(const char* _string, uint32_t _stringSize);

	char* GetString();

	bool IsEqual(ModelComposerString& _string, uint32_t _stringSize = -1);

	bool IsEqual(const char* _string, uint32_t _stringSize = -1);

///////////////
// VARIABLES //
private: //////

	// The internal string
	char m_String[MaxStringSize];
};

// ModelComposer Module
NamespaceEnd(ModelComposer)