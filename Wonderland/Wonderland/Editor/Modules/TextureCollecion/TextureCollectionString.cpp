////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureCollectionString.h"

TextureCollection::TextureCollectionString::TextureCollectionString()
{
	// Set the initial data
	// ...
}

TextureCollection::TextureCollectionString::TextureCollectionString(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

TextureCollection::TextureCollectionString::~TextureCollectionString()
{
}

void TextureCollection::TextureCollectionString::operator =(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

void TextureCollection::TextureCollectionString::SetString(const char* _string)
{
	if (strlen(_string) <= MaxStringSize)
		strcpy(m_String, _string);
}

void TextureCollection::TextureCollectionString::SetString(const char* _string, uint32_t _stringSize)
{
	if ((_stringSize + 1) <= MaxStringSize) // Include the null terminator
	{
		// Copy the string
		memcpy(m_String, _string, sizeof(char) * (_stringSize));

		// Include the null terminator
		m_String[_stringSize] = 0;
	}
}

char* TextureCollection::TextureCollectionString::GetString()
{
	return m_String;
}

bool TextureCollection::TextureCollectionString::IsEqual(TextureCollectionString& _string, uint32_t _stringSize)
{
	return IsEqual(_string.GetString(), _stringSize);
}

bool TextureCollection::TextureCollectionString::IsEqual(const char* _string, uint32_t _stringSize)
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