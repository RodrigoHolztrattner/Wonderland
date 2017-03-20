////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroupManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\..\..\HashedString.h"
#include "..\..\..\Reference.h"
#include "..\..\Resource\HoardResourceManager.h"
#include "..\..\Resource\HoardResourceIndexLoader.h"

#include "..\..\Material\VWDescriptorSetCreator.h"
#include "VWTextureGroup.h"
#include "VWTextureGroupRequest.h"
#include "VWTextureGroupVault.h"
#include "VWTextureGroupIndex.h"

#include <vector>
#include <map>
#include <array>
#include <list>
#include <functional>

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
class VWTexture;

////////////////
// STRUCTURES //
////////////////

/*
	- Temos o texture group index, onde ficam todas as informações de como cada texture group é formado (quais imagens, tamanhos, mipmaps, informações de criação, etc).
	- Quando queremos um group, usamos a hashed string do nome do mesmo.
	- Verificamos primeiro se ele se encontra na memória, caso afirmativo seguimos pegando a referencia do vault e tal...
	- Caso não esteja, procuramos o index referente ao grupo e solicitamos o recurso (ou os recursos).

	- Como foi definido que usaremos um map para o texture group, podemos ler os dados do index do disco e criar novos em runtime.
*/

/*
	- Varias solicitações de texture group são feitas por vários objetos durante o update de uma instancia de App
	- No final do update, essas requisições são enfileiradas e são processadas:

		: Caso o texture group já esteja na memória :

			- Apenas alteramos a referência e aumentamos o contador de referencia.

		: Caso o texture group não esteja na memória :

			- Ou o texture group ainda não fez nada.							-> O mesmo é criado, é adicionado na memória, é feita a solicitação de carregamento do recurso e é adicionado na lista para ser gerado.
			- Ou o texture group está esperando o carregamento do recurso.		-> Adicionamos um wake call para o recurso apontando para a referencia solicitante.
			- Ou o texture group está na lista de espera para ser gerado.		-> Em algum momento no update faremos a verificação que ele pode ser gerado e 
			- Ou o texture group está sendo gerado.


*/

////////////////////////////////////////////////////////////////////////////////
// Class name: VWTextureGroupManager
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupManager : public VWDescriptorSetCreator
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroupManager();
	~VWTextureGroupManager();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize(VWContext* _graphicContext, HoardResourceIndexLoader<VWTextureGroupIndex>* _textureGroupIndexLoaderRef, uint32_t _totalWorkerThreads);

	// Release this image
	void Release();

public:

	// Request a texture group
	void RequestTextureGroup(Reference::Blob<VWTextureGroup>* _textureGroupReference, HashedStringIdentifier _groupIdentifier);

	// Process texture group requests
	void ProcessTextureGroupRequestQueues(HoardResourceManager* _resourceManager);

private:

	// Process a texture group request
	void ProcessTextureGroupRequest(HoardResourceManager* _resourceManager, VWTextureGroupRequest& _textureGroupRequest);

///////////////
// VARIABLES //
private: //////

	// The total number of worker threads we are using
	uint32_t m_TotalWorkerThreads;

	// Our texture group requests
	std::vector<VWTextureGroupRequest>* m_TextureGroupRequests;

	// Our texture group vault
	VWTextureGroupVault m_TextureGroupVault;

	// The texture index loader reference
	HoardResourceIndexLoader<VWTextureGroupIndex>* m_TextureGroupIndexLoader;

	// Our texture groups
	// std::map<std::string, VWTextureGroup> m_TextureGroups;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)