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
		// Compara o id de criação
		if (m_AssemblyBoxes[i]->functionComponent->creationId == _functionCreationId)
		{
			return m_AssemblyBoxes[i];
		}
	}

	// Não achamos!
	return nullptr;
}

FluxFunctionAssembler::AssemblyBoxOutputVariable* FluxFunctionAssembler::FindOutputVariable(AssemblyBox* _inputBox, unsigned int _variableId)
{
	// Para cada saída da box
	for (int i = 0; i < _inputBox->outputVariables.size(); i++)
	{
		// Compara o id da variável
		if (_inputBox->outputVariables[i].variableId == _variableId)
		{
			return &_inputBox->outputVariables[i];
		}
	}

	// Não achamos!
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
		// Pega o parâmetro
		FluxFunctionHeader::FunctionParameter functionParameter = function->GetOutputParameter(i);

		// Cria uma output variable
		AssemblyBoxOutputVariable outputVariable;

		// Verifica qual é o tipo
		if (FluxType::Compare(functionParameter.parameterType, FluxType::ExecutionVariable)) //  != FluxFunctionBody::FunctionLinkType::Execution
		{
			// Ajusta como exec
			outputVariable.variableIsExec = true;
		}
		else
		{
			// Ajusta como variável normal
			outputVariable.variableIsExec = false;
			outputVariable.variableGeneratedName = m_NameProvider.GetValidVariableName(); // Gera um nome válido para esta variável de saída
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