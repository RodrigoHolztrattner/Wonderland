////////////////////////////////////////////////////////////////////////////////
// Filename: PacketLoader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"

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

// Packet data explorer
NamespaceBegin(Packet)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

enum class PacketMode
{
	Editor,		// We can add, remove and search for directories and files, we can use both identifiers and name paths
	Vault		// We can only search for directories and files, we can only use identifiers
};

// Packet data explorer
NamespaceEnd(Packet)