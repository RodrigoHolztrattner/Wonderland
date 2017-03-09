////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceSystem.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "System.h"

#include "Resource.h"
#include "ResourceLocator.h"
#include "ResourceCache.h"
#include "ResourceWorkerThread.h"
#include "ResourceRequestQueue.h"
#include "ResourceFactory.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

/*

	=> Resource workers:

		- S�o respons�veis por carregar recursos asynch.
		- De vez em quando devem fazer uma verifica��o do uso de mem�ria pelas partes internas do sistema.
		- Devem entrar em contato sempre com a ResourceRequestQueue que � onde fica as requests de recursos.

	=> Resource request queue

		- � onde ficam armazenadas as requests de cria��o asynch.
		- � acessada por fora na hora de adicionar um novo pedido e de dentro pelos worker threads quando um pedido � encaminhado.
		- � um ring-buffer.
*/

/*
	=> Resource � solicitado

		- Ou ele existe e j� � encaminhado (n�o pode estar sofrendo dele��o pois isso acarretaria em dele��o de um resource em uso)
		- Ou ele � encaminhado para cria��o (o resource precisa existir j� a partir deste momento pois o objeto que o carrega pode ser deletado logo a seguir
		causando com que se perca a referencia. � preciso criar o Resource base e incrementar uma referencia.

	=> Resource � liberado

		- Deve-se verificar quantas referencias o resource ainda tem, caso n�o possua alguma ele deve ser movido para a mem�ria cache.
		- Um resource s� pode ser movido caso ele n�o esteja sendo liberado para alguma call solicitante (ver o problema acima) aonde o contador de referencia
		ainda n�o foi incrementado.

	=> Resource � deletado

		- Resource n�o pode estar sendo movido da cache para a mem�ria atual pois isso acarretaria em deletarmos um Resource usado e, logo, ptr inv�lido.

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	=> Lista de dele��o

		- Criar uma lista de dele��o, onde todo recurso que por algum motivo atingiu zero referencias ser� adicionado.
		- Sempre no inicio do update devemos (worker thread) verificar quais destes recursos realmente precisam ser deletados, isso em uma fase onde N�O � poss�vel
		criar ou destruir recursos, logo, aqui poderemos decidir o que fazer com os recursos sem interven��o de outras threads alterando referencias.
		- A thread em quest�o passar� todos os objetos que realmente n�o s�o mais necess�rios para a mem�ria cache.
		- Sempre que passar um recurso para a mem�ria cache implicar na dele��o de um j� existente na posi��o a ser ocupada, este recurso deve ser retirado da cache
		e colocado em uma lista de dele��o final, onde, por threads auxiliares (resource worker threads) o objeto ser� finalmente deletado.

		- Determinamos que o Resource System necessita de uma etapa de synch, onde s�o feita as movimenta��es de localiza��o dos recursos.

	=> Solicita��o de recurso

		- � verificado se o recurso j� est� em uso, em caso afirmativo o numero de referencias deve ser incrementado e o recurso retornado.
		
		- Caso o recurso n�o esteja em uso, dever� ser aberto um chamado e uma call deve ser adicionada em uma queue list.

		AQUI EXISTE UM PROBLEMA POIS EU QUERO QUE AS WORKER THREADS FIQUEM PESCANDO CHAMADOS E CRIANDO OS RECURSOS FALTANTES.
		ISSO FERE COM TUDO DEFINIDO AT� AGORA POIS EU QUERIA UM SISTEMA QUE EU N�O PRECISASSE FICAR SINCRONIZANDO E TAL.
		PRECISO REPENSAR ISSO!



	=> BEGIN FRAME UPDATE

		----- System Synch

		-> Spawn Threads

			-> Synch Resource System

		-> Join Threads

		----- Game Logic

		-> Spawn Threads

			-> Game Logic

		-> Join Threads

		----- Game Rendering

		-> Spawn Threads

			-> Rendering

		-> Join Threads

	=> END FRAME UPDATE
*/

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: ResourceSystem
////////////////////////////////////////////////////////////////////////////////
class ResourceSystem : public System
{
public:
	ResourceSystem();
	ResourceSystem(const ResourceSystem&);
	~ResourceSystem();

	// Initialize the resource system
	bool Initialize(EngineConfig _engineConfig);

	// Checks if a resource exists on memory, on cache or try to load it
	// <multiple access from outside threads>
	template<typename ResourceClass>
	IndirectionPointer<Resource>* GetResource(FHashId _hashId)
	{
		// Get the resource index
		unsigned int resourceIndex = m_ResourceMetadata.GetResourceIndex(_hashId); // Multiple access, ok!
		if (resourceIndex == -1)
		{
			return nullptr;
		}

		// Get the indirection pointer for our resource
		IndirectionPointer<Resource>* resourceIndirectionPointer = m_ResourceLocator.GetResourceIndirectionPointer(resourceIndex);

		// Check if the pointer is valid

		// Set the resource allocation method
		m_ResourceLocator.SetResourceAllocationFunctor(resourceIndex, ResourceFactory<ResourceClass>::CreateInstance); // Multiple access, ok!
		
		// Make a request to this resource
		// ...  // Multiple access, we will deal with it later, fine!

		// Return the indirection pointer for this resource
		return resourceIndirectionPointer;
	}

	// Shutdown the source system
	void Shutdown();

private:

	// The resource metadata
	ResourceMetadata m_ResourceMetadata;

	// Our resource locator
	ResourceLocator m_ResourceLocator;

	// The resource cache
	ResourceCache m_ResourceCache;

	// All the resource worker threads
	ResourceWorkerThread* m_ResourceWorkers;

	// Our resource request queue
	ResourceRequestQueue m_ResourceRequestQueue;
};