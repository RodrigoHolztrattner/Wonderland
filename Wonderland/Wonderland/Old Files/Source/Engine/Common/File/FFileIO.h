////////////////////////////////////////////////////////////////////////////////
// Filename: FFileIO.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FFileIO_H_
#define _FFileIO_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <fstream>
#include <stdio.h>

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FFileIO
////////////////////////////////////////////////////////////////////////////////
class FFileIO
{
public:

	// The open modes
	enum OpenMode
	{
		ReadMode = 0,
		WriteMode = 1
	};

private:

	// The translated open modes
	static const char* TranslatedOpenMode[];

public:
	FFileIO();
	FFileIO(const FFileIO&);
	~FFileIO();

	// Pre-open a file
	void PreOpen(const char* _filePath)
	{
		m_FilePath = _filePath;
	}

	// Return the file size
	std::ifstream::pos_type FileSize()
	{
		std::ifstream in(m_FilePath, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	// Try to open a file from the standard paths
	bool Open(OpenMode _openMode);

	// Open a file from the given path
	bool Open(const char* _filePath, OpenMode _openMode);

	// Close the file
	bool Close();

	// Read x bytes from the file
	bool Read(unsigned int _amount, void* _to);

	// Write x bytes to the file
	bool Write(unsigned int _amount, void* _from);

	// Seek to the x position inside the file
	void Seek(unsigned long _position);

private:

	// The file path that we will open (used at PreOpen)
	const char* m_FilePath;

	// The FILE object
	FILE* m_File;
};

#endif
