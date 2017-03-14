////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroupIndex.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"

#include "VWTextureGroup.h"

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
// Class name: VWTextureGroupIndex
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupIndex
{
private:

	struct TextureGroupIndexInfo
	{
		// The texture group identifier
		HashedStringIdentifier identifier; // usado externamente quando alguem precisa deste grupo

		// Preciso ter um recurso aqui, pode ser o path, n�o tem problema, mas isso emplicar� na etapa abaixo:

		// Identificador do recurso, precisamos de uma etapa respons�vel por peg�-lo e armazen�-lo aqui, fazer isso apra todos os grupos, assim evitador comparar usando strings

		// Informa��es de tamanho, mipmaps, etc
		// etc...
	};

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroupIndex();
	~VWTextureGroupIndex();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the texture group index
	bool Initialize(const char* _textureGroupIndexFilename);

///////////////
// VARIABLES //
private: //////

};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)