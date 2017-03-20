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
#include "..\..\..\Hoard\Hoard.h"

#include "..\..\Misc\VWDescriptorSetCreator.h"
#include "VWTextureGroup.h"
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
class VWTextureGroupManager : public VWDescriptorSetCreator, public Hoard::Supply::Manager<VWTextureGroup, VWTextureGroupIndex>
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

	// Create the descriptor layout
	void CreateDescriptorLayout(VWContext* _graphicContext);

	// Release this image
	void Release() override;

	// Create a new supply object and request the resource loading
	VWTextureGroup* CreateAndRequestObject(Hoard::ResourceManager* _resourceManager, uint32_t _resourceIdentifier) override;

///////////////
// VARIABLES //
private: //////

	// The context reference
	VWContext* m_ContextReference;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)