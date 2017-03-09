////////////////////////////////////////////////////////////////////////////////
// Filename: BoxBody.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "Box.h"

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
// Class name: BoxBody
////////////////////////////////////////////////////////////////////////////////
class BoxBody
{
	// The execution flow
	struct ExecutionFlow
	{
		// The next box building
		BoxBody* nextBox;
	};

	// The type flow
	struct TypeFlow
	{
		/*
		
			: Linkada com:

			- Variávei gerada por uma box
			- Uma variável de uma classe
			- Uma variável de uma função
			- Um valor pré estabelecido <no momento não suportado>
		
		*/

		// 
	};

	// The internal variable type
	struct InternalVariable
	{
		// The generated variable name
		std::string generatedVariableName;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	BoxBody();
	BoxBody(Flux::Box* _boxReference);
	~BoxBody();

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
private: //////

	// Our box reference
	Flux::Box* m_BoxReference;

	// Execution output sockets
	std::vector<ExecutionFlow> m_SocketExecutionOutputs;

	// Input sockets
	std::vector<TypeFlow> m_SocketTypeInputs;

	// Output sockets
	std::vector<TypeFlow> m_SocketTypeOutputs;

	// The output generated variables
	std::vector<InternalVariable> m_GeneratedOutputVariables;
};

// Flux workspace
NamespaceEnd(Flux)