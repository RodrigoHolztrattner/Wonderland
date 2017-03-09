////////////////////////////////////////////////////////////////////////////////
// Filename: FResourceManager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FResourceManager_H_
#define _FResourceManager_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <unordered_map>
#include "Containers\Array\TArray.h"
#include "File\FFileIO.h"
#include "String\FHashedString.h"

/////////////
// DEFINES //
/////////////

/*

	=> The resource manager controls all the resource headers.

*/

// We know the IResource class
class IResource;

////////////////////////////////////////////////////////////////////////////////
// Class name: FResourceManager
////////////////////////////////////////////////////////////////////////////////
class FResourceManager
{
	// IResource is a friend class
	friend IResource;

public:

	// The resource manager header
	struct ResourceManagerHeader
	{
		// The number of resources
		unsigned int numberResources;

		// The number of resource datas
		unsigned int numberResourceDatas;
	};

	// The resource header type
	struct ResourceHeader
	{
		ResourceHeader(const char* _resourcePath)
		{
			strcpy(resourceName, _resourcePath);
			isLocal = true;
			dataIndex = -1;
			dataPosition = 0;
			resourceCompressedSize = 0;
			resourceSize = 0;
		}
		ResourceHeader()
		{
			isLocal = false;
		}
		ResourceHeader(const ResourceHeader& other)
		{
			strcpy(resourceName, other.resourceName);
			hashedString = other.hashedString;
			dataIndex = other.dataIndex;
			dataPosition = other.dataPosition;
			resourceCompressedSize = other.resourceCompressedSize;
			resourceSize = other.resourceSize;
			isLocal = other.isLocal;
		}

		// The resource name
		char resourceName[31];

		// If this is a local resource
		bool isLocal;

		// The resource hashed string
		size_t hashedString;

		// The data index that we can find the resource
		unsigned int dataIndex;

		// The position inside the data resource
		unsigned long dataPosition;

		// The compressed size (zero if not compressed)
		unsigned int resourceCompressedSize;

		// The resource size (decompressed)
		unsigned int resourceSize;
	};

private:

	FResourceManager();
	FResourceManager(const FResourceManager&);
	~FResourceManager();

	// Initialize the resource manager
	bool Initialize(const char* _mainResourceHeader);

	// Return a resource header by name (the name will be converted to a hashed string)
	ResourceHeader* GetResourceHeader(FHashedString _resourceName);

private:

	// The resource manager header
	ResourceManagerHeader m_ManagerHeader;

	// The unordered map that we will use to store the resource headers
	std::unordered_map<size_t, ResourceHeader> m_ResourceHeaders;

};

#endif
