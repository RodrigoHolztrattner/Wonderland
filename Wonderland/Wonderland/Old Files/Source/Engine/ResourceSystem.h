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

		- São responsáveis por carregar recursos asynch.
		- De vez em quando devem fazer uma verificação do uso de memória pelas partes internas do sistema.
		- Devem entrar em contato sempre com a ResourceRequestQueue que é onde fica as requests de recursos.

	=> Resource request queue

		- É onde ficam armazenadas as requests de criação asynch.
		- É acessada por fora na hora de adicionar um novo pedido e de dentro pelos worker threads quando um pedido é encaminhado.
		- É um ring-buffer.
*/

/*
	=> Resource é solicitado

		- Ou ele existe e já é encaminhado (não pode estar sofrendo deleção pois isso acarretaria em deleção de um resource em uso)
		- Ou ele é encaminhado para criação (o resource precisa existir já a partir deste momento pois o objeto que o carrega pode ser deletado logo a seguir
		causando com que se perca a referencia. É preciso criar o Resource base e incrementar uma referencia.

	=> Resource é liberado

		- Deve-se verificar quantas referencias o resource ainda tem, caso não possua alguma ele deve ser movido para a memória cache.
		- Um resource só pode ser movido caso ele não esteja sendo liberado para alguma call solicitante (ver o problema acima) aonde o contador de referencia
		ainda não foi incrementado.

	=> Resource é deletado

		- Resource não pode estar sendo movido da cache para a memória atual pois isso acarretaria em deletarmos um Resource usado e, logo, ptr inválido.

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	=> Lista de deleção

		- Criar uma lista de deleção, onde todo recurso que por algum motivo atingiu zero referencias será adicionado.
		- Sempre no inicio do update devemos (worker thread) verificar quais destes recursos realmente precisam ser deletados, isso em uma fase onde NÃO é possível
		criar ou destruir recursos, logo, aqui poderemos decidir o que fazer com os recursos sem intervenção de outras threads alterando referencias.
		- A thread em questão passará todos os objetos que realmente não são mais necessários para a memória cache.
		- Sempre que passar um recurso para a memória cache implicar na deleção de um já existente na posição a ser ocupada, este recurso deve ser retirado da cache
		e colocado em uma lista de deleção final, onde, por threads auxiliares (resource worker threads) o objeto será finalmente deletado.

		- Determinamos que o Resource System necessita de uma etapa de synch, onde são feita as movimentações de localização dos recursos.

	=> Solicitação de recurso

		- É verificado se o recurso já está em uso, em caso afirmativo o numero de referencias deve ser incrementado e o recurso retornado.
		
		- Caso o recurso não esteja em uso, deverá ser aberto um chamado e uma call deve ser adicionada em uma queue list.

		AQUI EXISTE UM PROBLEMA POIS EU QUERO QUE AS WORKER THREADS FIQUEM PESCANDO CHAMADOS E CRIANDO OS RECURSOS FALTANTES.
		ISSO FERE COM TUDO DEFINIDO ATÉ AGORA POIS EU QUERIA UM SISTEMA QUE EU NÃO PRECISASSE FICAR SINCRONIZANDO E TAL.
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