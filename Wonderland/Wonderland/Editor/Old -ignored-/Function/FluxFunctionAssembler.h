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
		// O id da variável (para buscar no header da função)
		unsigned int variableId;

		// O tipo da variável
		std::string variableType;

		// Se é exec
		bool variableIsExec;

		// O nome atribuido à ela
		std::string variableGeneratedName;
	};

	// The assembly box
	struct AssemblyBox
	{
		// O componente da função ao qual essa box está associado
		FluxFunctionBody::FunctionComponent* functionComponent;

		// A array com as variáveis de saida
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

	// Procura em um assembly box uma variável de saída
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