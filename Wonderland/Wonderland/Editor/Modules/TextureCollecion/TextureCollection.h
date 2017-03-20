////////////////////////////////////////////////////////////////////////////////
// Filename: PacketLoader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"

#include "TextureCollectionCreator.h"
#include "TextureCollectionFormat.h"
#include "TextureCollectionString.h"
#include "TextureCollectionUnpacker.h"

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

//////////////////
// DEPENDENCIES //
//////////////////

//////////////
// TYPEDEFS //
//////////////


#include "TextureCollectionCreator.h"
#include "TextureCollectionFormat.h"
#include "TextureCollectionString.h"
#include "TextureCollectionUnpacker.h"

// Texture Collection Module
NamespaceBegin(TextureCollection)

typedef TextureCollectionCreator			Creator;
typedef TextureCollectionData				TextureData;
typedef TextureCollectionHeader				CollectionHeader;
typedef TextureCollectionString				String;
typedef TextureCollectionUnpacker			Unpacker;

// Texture Collection Module
NamespaceEnd(TextureCollection)