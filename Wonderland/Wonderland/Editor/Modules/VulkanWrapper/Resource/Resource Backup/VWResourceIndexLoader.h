////////////////////////////////////////////////////////////////////////////////
// Filename: VWResourceIndexLoader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <map>
#include <type_traits>

#include "..\..\NamespaceDefinitions.h"
#include "VWResourceIndex.h"
#include "..\..\Packet\Packet.h"

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

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWContext;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWResourceIndexLoader
////////////////////////////////////////////////////////////////////////////////
//typedef VWResourceIndex IndexClass;

template <typename IndexClass>
class VWResourceIndexLoader
{
private:

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWResourceIndexLoader() 
	{
		//typename std::enable_if<std::is_base_of<VWResourceIndex, IndexClass>::value, void>::type;
	}
	~VWResourceIndexLoader() {}

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the index
	bool Initialize(Packet::Manager* _packetManager, const char* _indexFilePath)
	{
		// Load the index data
		if (!LoadIndexData(_packetManager, _indexFilePath))
		{
			return false;
		}

		return true;
	}

	// Add an index object (we must ensure we are on editor mode)
	void AddIndex(Packet::Manager* _packetManager, IndexClass& _indexObject)
	{
		// Check for the editor mode
		// ...

		// Find the file for the resource path inside this index object
		Packet::PacketFile* indexObjectResourceFile = _packetManager->FindFile(_indexObject.GetPath()->GetString(), false);
		if (!indexObjectResourceFile)
		{
			// Problem, cant locate an index object resource file
			return;
		}

		// Set the resource file index
		_indexObject.SetResourceIdentifier(indexObjectResourceFile->GetIdentifier());

		// Add the object
		m_IndexMap[_indexObject.GetIdentifier()] = _indexObject;
	}

	// Return a index using the identifier
	IndexClass* GetIndex(HashedStringIdentifier _identifier)
	{
		if (m_IndexMap.find(_identifier) == m_IndexMap.end())
		{
			return nullptr;
		}

		return &m_IndexMap[_identifier];
	}

	// Save the index data
	bool SaveIndexData(Packet::Manager* _packetManager)
	{	
		//TODO: fazer isso
		return false;

		/*
		// Create or find the index file
		Packet::PacketFile* indexFile = _packetManager->CreateFile(m_IndexFilePath);
		if (!indexFile)
		{
			// Ok the file dont exist, we should emit an alert but we are fine to continue
			return true;
		}
		*/
	}

private:

	// Load the index data
	bool LoadIndexData(Packet::Manager* _packetManager, const char* _indexFilePath)
	{
		// Save the index file path
		m_IndexFilePath = _indexFilePath;

		// Try to find the index file
		Packet::PacketFile* indexFile = _packetManager->FindFile(_indexFilePath, false);
		if (indexFile == nullptr)
		{
			// Ok the file dont exist, we should emit an alert but we are fine to continue
			return true;
		}

		// The byte array we will use to load the file
		std::vector<unsigned char> byteArray;

		// Load the file
		if (!_packetManager->LoadFile(indexFile, byteArray))
		{
			// Problem loading the index file!
			return false;
		}

		// The current position inside the byte array
		uint32_t byteArrayPosition = 0;

		// Until we reach the byte array end
		while (byteArrayPosition < byteArray.size())
		{
			// The new index object
			IndexClass newIndexObject;

			// Load the index object
			byteArrayPosition = newIndexObject.Deserialize(byteArray, byteArrayPosition);

			// Find the file for the resource path inside this index object
			Packet::PacketFile* indexObjectResourceFile = _packetManager->FindFile(newIndexObject.GetPath()->GetString(), false);
			if (!indexObjectResourceFile)
			{
				// Problem, cant locate an index object resource file
				return true;
			}

			// Set the resource file index
			newIndexObject.SetResourceIdentifier(indexObjectResourceFile->GetIdentifier());

			// Add it to the index map
			m_IndexMap[newIndexObject.GetIdentifier()] = newIndexObject;
		}

		return true;
	}

	

///////////////
// VARIABLES //
private: //////

	// The index file path
	const char* m_IndexFilePath;

	// Our mapped index data
	std::map<HashedStringIdentifier, IndexClass> m_IndexMap;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)