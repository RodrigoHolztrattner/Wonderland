////////////////////////////////////////////////////////////////////////////////
// Filename: TextureCollectionFormat.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"
#include "..\Serialize.h"
#include "TextureCollectionString.h"
#include <cstdint>

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

// Texture Collection Module
NamespaceBegin(TextureCollection)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

struct TextureCollectionData : public Serialize::Serializable
{
	// The texture name
	TextureCollectionString name;

	// The texture width and height
	uint16_t width, height;

	// The texture data
	unsigned char* data;

	// Serialize this object
	std::vector<unsigned char> Serialize()
	{
		// The data to be serialized
		std::vector<unsigned char> byteArray;

		// The serialized
		Serialize::Serializer serializer(byteArray);

		// Pack the initial data
		serializer.PackData(name.GetString(), TextureCollectionString::MaxStringSize);
		serializer.PackData(width);
		serializer.PackData(height);

		return byteArray;
	}

	// Deserialize this
	uint32_t Deserialize(std::vector<unsigned char>& _data, uint32_t _index)
	{
		// The deserializer object
		Serialize::Deserializer deserializer(_data, _index);

		// Unpack the initial data
		deserializer.UnpackData(name.GetString(), TextureCollectionString::MaxStringSize);
		deserializer.UnpackData(width);
		deserializer.UnpackData(height);

		return deserializer.GetIndex();
	}
};

struct TextureCollectionHeader : public Serialize::Serializable
{
	// The texture collection name
	TextureCollectionString collectionName;

	// The total number of textures inside this collection
	uint16_t totalTextures;

	// The texture size used on this collection
	uint16_t width, height;

	// The texture format
	// ...

	// Serialize this object
	std::vector<unsigned char> Serialize()
	{
		// The data to be serialized
		std::vector<unsigned char> byteArray;

		// The serialized
		Serialize::Serializer serializer(byteArray);

		// Pack the initial data
		serializer.PackData(collectionName.GetString(), TextureCollectionString::MaxStringSize);
		serializer.PackData(totalTextures);
		serializer.PackData(width);
		serializer.PackData(height);

		return byteArray;
	}

	// Deserialize this
	uint32_t Deserialize(std::vector<unsigned char>& _data, uint32_t _index)
	{
		// The deserializer object
		Serialize::Deserializer deserializer(_data, _index);

		// Unpack the initial data
		deserializer.UnpackData(collectionName.GetString(), TextureCollectionString::MaxStringSize);
		deserializer.UnpackData(totalTextures);
		deserializer.UnpackData(width);
		deserializer.UnpackData(height);

		return deserializer.GetIndex();
	}
};

// Texture Collection Module
NamespaceEnd(TextureCollection)