///////////////////////////////////////////////////////////////////////////////
// Filename: FFileIO.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FFileIO.h"

// Declare the translated open modes
const char* FFileIO::TranslatedOpenMode[] =
{
	"rb",
	"wb"
};

FFileIO::FFileIO()
{
}

FFileIO::FFileIO(const FFileIO& other)
{
	m_FilePath = other.m_FilePath;
	m_File = other.m_File;
}

FFileIO::~FFileIO()
{
}

bool FFileIO::Open(OpenMode _openMode)
{
	// Open the file
	return Open(m_FilePath, _openMode);
}

bool FFileIO::Open(const char* _filePath, OpenMode _openMode)
{
	// Open the file in binary.
	int error = fopen_s(&m_File, _filePath, TranslatedOpenMode[_openMode]);
	if (error != 0)
	{
		return false;
	}

	return true;
}

bool FFileIO::Read(unsigned int _amount, void* _to)
{
	// Read from the file
	int count = fread(_to, _amount, 1, m_File);
	if (count != 1)
	{
		return false;
	}

	return true;
}

bool FFileIO::Close()
{
	// Close the file
	int error = fclose(m_File);
	if (error != 0)
	{
		return false;
	}

	return true;
}

void FFileIO::Seek(unsigned long _position)
{
	fseek(m_File, _position, SEEK_SET);
}