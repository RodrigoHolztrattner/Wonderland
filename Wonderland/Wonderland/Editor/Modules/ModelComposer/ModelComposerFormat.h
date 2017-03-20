////////////////////////////////////////////////////////////////////////////////
// Filename: TextureCollectionFormat.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"
#include "..\Serialize.h"
#include "ModelComposerString.h"
#include <cstdint>
#include <vector>
#include <glm\glm.hpp>

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

// ModelComposer Module
NamespaceBegin(ModelComposer)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

typedef uint32_t ModelComposerIndexFormat;

struct ModelComposerVertexFormat
{
	ModelComposerVertexFormat() {}
	ModelComposerVertexFormat(glm::vec3 _position, glm::vec2 _textureCoordinates = glm::vec2(0, 0), glm::vec3 _normal = glm::vec3(1, 0, 0), glm::vec3 _binormal = glm::vec3(1, 0, 0))
	{
		position = _position;
		textureCoordinate = _textureCoordinates;
		normal = _normal;
		binormal = _binormal;
	}

	// The vertex position
	glm::vec3 position;

	// The vertex texture coordinate
	glm::vec2 textureCoordinate;

	// The vertex normals
	glm::vec3 normal;

	// The vertex binormal
	glm::vec3 binormal;
};

struct ModelComposerFormat : public Serialize::Serializable
{
	// The model name
	ModelComposerString name;

	// Total number of vertices
	uint32_t totalVertices;

	// Total number of indexes
	uint32_t totalIndexes;

	// The vertex vector
	std::vector<ModelComposerVertexFormat> vertices;

	// The index vector
	std::vector<ModelComposerIndexFormat> indexes;

	// Serialize this object
	std::vector<unsigned char> Serialize()
	{
		// The data to be serialized
		std::vector<unsigned char> byteArray;

		// The serialized
		Serialize::Serializer serializer(byteArray);

		// Pack the initial data
		serializer.PackData(name.GetString(), ModelComposerString::MaxStringSize);
		serializer.PackData(totalVertices);
		serializer.PackData(totalIndexes);
		serializer.PackData(vertices.data(), totalVertices);
		serializer.PackData(indexes.data(), totalIndexes);

		return byteArray;
	}

	// Deserialize this
	uint32_t Deserialize(std::vector<unsigned char>& _data, uint32_t _index)
	{
		// The deserializer object
		Serialize::Deserializer deserializer(_data, _index);

		// Unpack the initial data
		deserializer.UnpackData(name.GetString(), ModelComposerString::MaxStringSize);
		deserializer.UnpackData(totalVertices);
		deserializer.UnpackData(totalIndexes);

		// Alloc space for all vertex and index data
		vertices.resize(totalVertices);
		indexes.resize(totalIndexes);

		// Unpack the remaining data
		deserializer.UnpackData(vertices.data(), totalVertices);
		deserializer.UnpackData(indexes.data(), totalIndexes);

		return deserializer.GetIndex();
	}
};

// ModelComposer Module
NamespaceEnd(ModelComposer)