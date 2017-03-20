////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardString.h"

Hoard::HoardString::HoardString()
{
	// Set the initial data
	// ...
}

Hoard::HoardString::HoardString(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

Hoard::HoardString::~HoardString()
{
}

void Hoard::HoardString::operator =(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

void Hoard::HoardString::SetString(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

void Hoard::HoardString::SetString(const char* _string, uint32_t _stringSize)
{
	if ((_stringSize + 1) <= MaxStringSize) // Include the null terminator
	{
		// Copy the string
		memcpy(m_String, _string, sizeof(char) * (_stringSize));

		// Include the null terminator
		m_String[_stringSize] = 0;
	}
}

char* Hoard::HoardString::GetString()
{
	return m_String;
}

bool Hoard::HoardString::IsEqual(HoardString& _string, uint32_t _stringSize)
{
	return IsEqual(_string.GetString(), _stringSize);
}

bool Hoard::HoardString::IsEqual(const char* _string, uint32_t _stringSize)
{
	uint32_t currentSize = 0;
	while (currentSize < _stringSize)
	{
		if (m_String[currentSize] != _string[currentSize])
		{
			return false;
		}

		currentSize++;
	}

	return true;
}