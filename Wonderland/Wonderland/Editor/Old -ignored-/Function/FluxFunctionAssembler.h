////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionAssembler.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <vector>
#include "FluxFunction.h"
#include "..\VariableNameProvider.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxFunctionAssembler
////////////////////////////////////////////////////////////////////////////////
class FluxFunctionAssembler
{
/////////////
// DEFINES //
public: /////

	// 
	struct AssemblyBoxOutputVariable
	{
		// O id da vari�vel (para buscar no header da fun��o)
		unsigned int variableId;

		// O tipo da vari�vel
		std::string variableType;

		// Se � exec
		bool variableIsExec;

		// O nome atribuido � ela
		std::string variableGeneratedName;
	};

	// The assembly box
	struct AssemblyBox
	{
		// O componente da fun��o ao qual essa box est� associado
		FluxFunctionBody::FunctionComponent* functionComponent;

		// A array com as vari�veis de saida
		std::vector<AssemblyBoxOutputVariable> outputVariables;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxFunctionAssembler();
	~FluxFunctionAssembler();

//////////////////
// MAIN METHODS //
public: //////////

protected:

	// Cria um assembly box
	AssemblyBox* CreateAssemblyBox(FluxFunction* _fromFunction, FluxFunctionBody::FunctionComponent* _functionComponent);

	// Procura um assembly box por id
	AssemblyBox* FindAssemblyBox(unsigned int _functionCreationId);

	// Procura em um assembly box uma vari�vel de sa�da
	AssemblyBoxOutputVariable* FindOutputVariable(AssemblyBox* _inputBox, unsigned int _variableId);

private:

////////////////////
// INPUT / OUTPUT //
public: ////////////

///////////////
// VARIABLES //
protected: ////

	// Our assembly box array
	std::vector<AssemblyBox*> m_AssemblyBoxes;

	// The name provider
	VariableNameProvider m_NameProvider;

};