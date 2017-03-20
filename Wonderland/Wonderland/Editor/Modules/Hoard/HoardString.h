////////////////////////////////////////////////////////////////////////////////
// Filename: HoardString.h
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

// Hoard Resource Module
NamespaceBegin(Hoard)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardString
////////////////////////////////////////////////////////////////////////////////
class HoardString
{
public:

	static const int MaxStringSize = 63;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardString();
	HoardString(const char* _string);
	~HoardString();

//////////////////
// MAIN METHODS //
public: //////////

	void operator =(const char* _string);

	void SetString(const char* _string);

	void SetString(const char* _string, uint32_t _stringSize);

	char* GetString();

	bool IsEqual(HoardString& _string, uint32_t _stringSize = -1);

	bool IsEqual(const char* _string, uint32_t _stringSize = -1);

///////////////
// VARIABLES //
private: //////

	// The internal string
	char m_String[MaxStringSize];
};

// Hoard Resource Module
NamespaceEnd(Hoard)