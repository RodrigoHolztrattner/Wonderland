////////////////////////////////////////////////////////////////////////////////
// Filename: PacketLoader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"

#include "ModelComposerFormat.h"
#include "ModelComposerString.h"
#include "ModelComposerUnpacker.h"
#include "ModelComposerCreator.h"

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

// Texture Collection Module
NamespaceBegin(ModelComposer)

typedef ModelComposerFormat			Format;
typedef ModelComposerString			String;
typedef ModelComposerUnpacker		Unpacker;
typedef ModelComposerCreator		Creator;
typedef ModelComposerIndexFormat	IndexFormat;
typedef ModelComposerVertexFormat	VertexFormat;

// Texture Collection Module
NamespaceEnd(ModelComposer)