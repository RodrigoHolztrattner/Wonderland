////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "..\..\NamespaceDefinitions.h"

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

aqui
/*
	- N�o usamos texturas sozinhas, usamos grupos, quando uma textura � solicitada ela obrigatoriamente pertence a um grupo (nem que ela seja sozinha) e este
	grupo � inteiramente carregado.
	- Quando criamos um grupo, cada nova textura adicionada a ele recebe um ID que ser� usado para referencia-la dentro do mesmo.
	- Um objeto que utiliza uma textura interna da engine dever� saber qual o grupo da textura e qual o seu ID para fazer uma solicita��o.
	- Podemos carregar uma textura fornecedo o seu grupo e o ID ou podemos pegar o grupo e ap�s isso pegar a textura desejada de dentro do mesmo.
	* Preciso ver o que fica armazenado no objeto, se � o ID da textura ou se � um ponteiro direto para ela ou o que...
	- Para carregar uma textura externa, devo utilizar o nome do grupo e o nome da textura, caso a textura n�o exista para esse grupo ela ser�
	carregada e colocada no mesmo.
	* Pensar a respeito da parte acima.
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: VWTextureManager
////////////////////////////////////////////////////////////////////////////////
class VWTextureManager
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureManager();
	~VWTextureManager();

//////////////////
// MAIN METHODS //
public: //////////


///////////////
// VARIABLES //
private: //////

	// The total number of worker threads we are using
	uint32_t m_TotalWorkerThreads;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)