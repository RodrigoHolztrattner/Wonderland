////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWModelIndex.h"
#include "..\..\Context\VWContext.h"

VulkanWrapper::VWModelIndex::VWModelIndex()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWModelIndex::~VWModelIndex()
{
}

std::vector<unsigned char> VulkanWrapper::VWModelIndex::Serialize()
{
	// The main byte array
	std::vector<unsigned char> byteArray;

	// The serializer object
	Serialize::Serializer serializer(byteArray);

	// Pack the initial data
	serializer.PackData(m_ResourcePath.GetString(), Packet::PacketString::MaxStringSize);
	serializer.PackData(m_Identifier);

	return byteArray;
}

uint32_t VulkanWrapper::VWModelIndex::Deserialize(std::vector<unsigned char>& _data, uint32_t _index)
{
	// The deserializer object
	Serialize::Deserializer deserializer(_data, _index);

	// Unpack the initial data
	deserializer.UnpackData(m_ResourcePath.GetString(), Packet::PacketString::MaxStringSize);
	deserializer.UnpackData(m_Identifier);

	return deserializer.GetIndex();
}