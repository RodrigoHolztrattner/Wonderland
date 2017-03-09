////////////////////////////////////////////////////////////////////////////////
// Filename: FunctionBody.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "..\Box.h"
#include "FunctionFlow.h"

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

// Flux workspace
NamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// Class name: FunctionBody
////////////////////////////////////////////////////////////////////////////////
class FunctionBody
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FunctionBody();
	FunctionBody(Flux::Box* _boxReference);
	~FunctionBody();

//////////////////
// MAIN METHODS //
public: //////////

	// Fun��o para validar o body (verifica os handles das fun��es, ve se aconteceu alguma altera��o, verifica se as altera��o impedem de compilar, etc)
	// ...

	// Return the initial flow
	Flux::FunctionFlow* GetInitialFlow();

	// Return a flow by id
	Flux::FunctionFlow* GetFlowById(unsigned int _flowId);

///////////////
// VARIABLES //
private: //////

	// Our box reference handle
	Flux::Handle*						m_BoxReferenceHandle;

	// Our start and end flows
	Flux::FunctionFlow					m_StartFlow;
	Flux::FunctionFlow					m_EndFlow;

	// All flow array
	std::vector<FunctionFlow*>			m_FlowArray;

	// Referencia ao function head para acessar as vari�veis locais
	// ...


};

// Flux workspace
NamespaceEnd(Flux)