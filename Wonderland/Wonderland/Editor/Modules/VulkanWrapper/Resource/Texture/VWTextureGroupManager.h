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