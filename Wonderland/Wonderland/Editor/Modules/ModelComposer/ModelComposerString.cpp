////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ModelComposerString.h"

ModelComposer::ModelComposerString::ModelComposerString()
{
	// Set the initial data
	// ...
}

ModelComposer::ModelComposerString::ModelComposerString(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

ModelComposer::ModelComposerString::~ModelComposerString()
{
}

void ModelComposer::ModelComposerString::operator =(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

void ModelComposer::ModelComposerString::SetString(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

void ModelComposer::ModelComposerString::SetString(const char* _string, uint32_t _stringSize)
{
	if ((_stringSize + 1) <= MaxStringSize) // Include the null terminator
	{
		// Copy the string
		memcpy(m_String, _string, sizeof(char) * (_stringSize));

		// Include the null terminator
		m_String[_stringSize] = 0;
	}
}

char* ModelComposer::ModelComposerString::GetString()
{
	return m_String;
}

bool ModelComposer::ModelComposerString::IsEqual(ModelComposerString& _string, uint32_t _stringSize)
{
	return IsEqual(_string.GetString(), _stringSize);
}

bool ModelComposer::ModelComposerString::IsEqual(const char* _string, uint32_t _stringSize)
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