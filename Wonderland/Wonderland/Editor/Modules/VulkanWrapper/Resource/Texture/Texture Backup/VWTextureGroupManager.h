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
	- Temos o texture group index, onde ficam todas as informa��es de como cada texture group � formado (quais imagens, tamanhos, mipmaps, informa��es de cria��o, etc).
	- Quando queremos um group, usamos a hashed string do nome do mesmo.
	- Verificamos primeiro se ele se encontra na mem�ria, caso afirmativo seguimos pegando a referencia do vault e tal...
	- Caso n�o esteja, procuramos o index referente ao grupo e solicitamos o recurso (ou os recursos).

	- Como foi definido que usaremos um map para o texture group, podemos ler os dados do index do disco e criar novos em runtime.
*/

/*
	- Varias solicita��es de texture group s�o feitas por v�rios objetos durante o update de uma instancia de App
	- No final do update, essas requisi��es s�o enfileiradas e s�o processadas:

		: Caso o texture group j� esteja na mem�ria :

			- Apenas alteramos a refer�ncia e aumentamos o contador de referencia.

		: Caso o texture group n�o esteja na mem�ria :

			- Ou o texture group ainda n�o fez nada.							-> O mesmo � criado, � adicionado na mem�ria, � feita a solicita��o de carregamento do recurso e � adicionado na lista para ser gerado.
			- Ou o texture group est� esperando o carregamento do recurso.		-> Adicionamos um wake call para o recurso apontando para a referencia solicitante.
			- Ou o texture group est� na lista de espera para ser gerado.		-> Em algum momento no update faremos a verifica��o que ele pode ser gerado e 
			- Ou o texture group est� sendo gerado.


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