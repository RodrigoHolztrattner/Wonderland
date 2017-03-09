////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionAssembler.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionAssembler.h"
#include "FluxFunctionValidator.h"
#include "FluxFunctionRegister.h"

FluxFunctionAssembler::FluxFunctionAssembler()
{
    // Set the initial data
	// ...
}

FluxFunctionAssembler::~FluxFunctionAssembler()
{
}

FluxFunctionAssembler::AssemblyBox* FluxFunctionAssembler::FindAssemblyBox(unsigned int _functionCreationId)
{
	// Para cada assembly box
	for (int i = 0; i < m_AssemblyBoxes.size(); i++)
	{
		// Compara o id de cria��o
		if (m_AssemblyBoxes[i]->functionComponent->creationId == _functionCreationId)
		{
			return m_AssemblyBoxes[i];
		}
	}

	// N�o achamos!
	return nullptr;
}

FluxFunctionAssembler::AssemblyBoxOutputVariable* FluxFunctionAssembler::FindOutputVariable(AssemblyBox* _inputBox, unsigned int _variableId)
{
	// Para cada sa�da da box
	for (int i = 0; i < _inputBox->outputVariables.size(); i++)
	{
		// Compara o id da vari�vel
		if (_inputBox->outputVariables[i].variableId == _variableId)
		{
			return &_inputBox->outputVariables[i];
		}
	}

	// N�o achamos!
	return nullptr;
}


FluxFunctionAssembler::AssemblyBox* FluxFunctionAssembler::CreateAssemblyBox(FluxFunction* _fromFunction, FluxFunctionBody::FunctionComponent* _functionComponent)
{
	AssemblyBox* newAssemblyBox = new AssemblyBox;

	// Set the assembly function
	newAssemblyBox->functionComponent = _functionComponent;

	// Get the function object
	FluxFunction* function = FluxFunctionRegister::GetFunction(_functionComponent->functionData.functionName);
	if (function == nullptr)
	{
		return nullptr;
	}

	// For each output variable
	int variableId = 0;
	for (int i = 0; i < function->GetOutputSize(); i++)
	{
		// Pega o par�metro
		FluxFunctionHeader::FunctionParameter functionParameter = function->GetOutputParameter(i);

		// Cria uma output variable
		AssemblyBoxOutputVariable outputVariable;

		// Verifica qual � o tipo
		if (FluxType::Compare(functionParameter.parameterType, FluxType::ExecutionVariable)) //  != FluxFunctionBody::FunctionLinkType::Execution
		{
			// Ajusta como exec
			outputVariable.variableIsExec = true;
		}
		else
		{
			// Ajusta como vari�vel normal
			outputVariable.variableIsExec = false;
			outputVariable.variableGeneratedName = m_NameProvider.GetValidVariableName(); // Gera um nome v�lido para esta vari�vel de sa�da
		}

		// Ajusta os dados
		outputVariable.variableId = variableId++; // functionParameter.parameterId;
		outputVariable.variableType = functionParameter.parameterType;

		// Adiciona
		newAssemblyBox->outputVariables.push_back(outputVariable);
	}
	
	// Adiciona a box
	m_AssemblyBoxes.push_back(newAssemblyBox);

	return newAssemblyBox;
}