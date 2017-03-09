///////////////////////////////////////////////////////////////////////////////
// Filename: FResourceLoader.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FResourceLoader.h"
#include "IResource.h"
#include <assert.h>     /* assert */

FResourceLoader::FResourceLoader()
{
}

FResourceLoader::FResourceLoader(const FResourceLoader& other)
{
}

FResourceLoader::~FResourceLoader()
{
}

bool FResourceLoader::Initialize()
{
	return true;
}

void FResourceLoader::UpdateResourceQueue(float _time)
{
}

void FResourceLoader::LoadHelper(FResourceManager::ResourceHeader* _resourceHeader)
{
	IResource* currentResource;
	unsigned char* resourceData;
	std::ifstream::pos_type fileSize;
	FFileIO dataIO;

	// Check if this resource is local
	if (_resourceHeader->isLocal)
	{
		// Get the current resource
		currentResource = m_CurrentLocalResource;

		// Pre-Open the resource data
		dataIO.PreOpen(_resourceHeader->resourceName);

		// Get the file size
		fileSize = dataIO.FileSize();

		// Alloc space for the resource data
		resourceData = new unsigned char[fileSize];

		// Open the resource data
		if (!dataIO.Open(FFileIO::OpenMode::ReadMode))
		{
			// ASSERT
			return;
		}

		// Get the data
		if (!dataIO.Read(fileSize, resourceData))
		{
			// ASSERT
			return;
		}

		// Close the file
		if (!dataIO.Close())
		{
			// ASSERT
			return;
		}
	}
	else
	{
		// Get the current resource
		IResource* currentResource = m_ResourceData[_resourceHeader->dataIndex].currentResource;

		// Get the resource size
		fileSize = _resourceHeader->resourceCompressedSize ? _resourceHeader->resourceCompressedSize : _resourceHeader->resourceSize;

		// Alloc space for the resource data
		resourceData = new unsigned char[fileSize];

		// Get the data IO for this thread
		dataIO = m_ResourceData[_resourceHeader->dataIndex].dataIO;

		// Seek to the data position inside the file
		dataIO.Seek(_resourceHeader->dataPosition);

		// Read the resource data
		dataIO.Read(fileSize, resourceData);
	}

	// Check if we need to decompress the data
	if (_resourceHeader->resourceCompressedSize)
	{
		// Decompress the data
		// ...

		// Call the resource load function
		// ...

		// Delete the temproary decompressed data
		// ...
	}
	else
	{
		// Call the resource load function
		currentResource->Load(resourceData);
	}

	// Delete the temporary resource data
	delete [] resourceData;
}