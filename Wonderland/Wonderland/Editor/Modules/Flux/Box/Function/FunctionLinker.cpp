////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionLinker.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FunctionLinker.h"
#include "DynamicFunction\DynamicFunction.h"
#include "DynamicMemberFunction\DynamicMemberFunction.h"
#include "..\..\Class\Class.h"
#include "..\..\Class\ClassRegister.h"

Flux::FunctionLinker::FunctionLinker(Flux::Box* _boxReference, Flux::FunctionBody* _functionBodyReference)
{
	// Set the initial data
	m_BoxReference = _boxReference;
	m_FunctionBodyReference = _functionBodyReference;
}

Flux::FunctionLinker::~FunctionLinker()
{
}

bool Flux::FunctionLinker::CreateLinkerFlow()
{
	// Get the initial function flow from our body reference
	Flux::FunctionFlow* initialFunctionFlow = m_FunctionBodyReference->GetInitialFlow();

	// Call the helper function
	return CreateLinkerFlowHelper(&m_StartLinkerFlow, initialFunctionFlow);
}

bool Flux::FunctionLinker::CreateLinkerFlowHelper(Flux::FunctionLinkerFlow* _currentLinkerFlow, Flux::FunctionFlow* _fromFunctionFlow)
{
	// We assume the _currentLinkerFlow is always created and free for use //
	// We get our data from the _fromFunctionFlow //

	// Insert the linker flow inside our controll array
	m_LinkerFlows.push_back(_currentLinkerFlow);

	// Set the current linker flow data
	_currentLinkerFlow->functionFlowIdReference = _fromFunctionFlow->flowId;
	_currentLinkerFlow->functionFlowReference = _fromFunctionFlow;

	// For each flow output
	for (int i = 0; i < _fromFunctionFlow->flowOutputs.size(); i++)
	{
		// Create another function linker flow object
		Flux::FunctionLinkerFlow* newFunctionLinkerFlow = new Flux::FunctionLinkerFlow();

		// Insert into the output linker flow
		_currentLinkerFlow->flowOutputs.push_back(newFunctionLinkerFlow);

		// Call our helper function
		CreateLinkerFlowHelper(newFunctionLinkerFlow, _fromFunctionFlow->flowOutputs[i]);
	}

	return true;
}

bool Flux::FunctionLinker::ProcessVariableNames()
{
	return ProcessVariableNamesHelper(&m_StartLinkerFlow);
}

bool Flux::FunctionLinker::ProcessVariableNamesHelper(Flux::FunctionLinkerFlow* _currentLinkerFlow)
{
	// Get a short variable for out function flow reference
	Flux::FunctionFlow* functionFlowReference = _currentLinkerFlow->functionFlowReference;

	// For each input variable inside our function flow reference
	for (int i = 0; i < functionFlowReference->flowInputVariables.size(); i++)
	{
		// Get a short variable for our input variable
		Flux::FunctionFlow::FlowVariableObject* currentVariable = &functionFlowReference->flowInputVariables[i];

		// Our variable name
		std::string currentVariableName;

		// Get the variable name from the flow data
		bool result = GetVariableNameFromFlowData(functionFlowReference, currentVariable, currentVariableName);
		if (!result)
		{
			return false;
		}

		// Our linker variable object
		Flux::FunctionLinkerFlow::LinkerVariableObject currentLinkerVariable;

		// Set the linker variable data
		currentLinkerVariable.variableName = currentVariableName;

		// Insert the variable into the linker flow
		_currentLinkerFlow->flowInputVariables.push_back(currentLinkerVariable);
	}

	// For each output variable inside our function flow reference
	for (int i = 0; i < functionFlowReference->flowOutputVariables.size(); i++)
	{
		// Get a short variable for our output variable
		Flux::FunctionFlow::FlowVariableObject* currentVariable = &functionFlowReference->flowOutputVariables[i];

		// Our variable name
		std::string currentVariableName;

		// Get the variable name from the flow data
		bool result = GetVariableNameFromFlowData(functionFlowReference, currentVariable, currentVariableName);
		if (!result)
		{
			return false;
		}

		// Our linker variable object
		Flux::FunctionLinkerFlow::LinkerVariableObject currentLinkerVariable;

		// Set the linker variable data
		currentLinkerVariable.variableName = currentVariableName;

		// Insert the variable into the linker flow
		_currentLinkerFlow->flowOutputVariables.push_back(currentLinkerVariable);
	}

	// For each flow
	for (int i = 0; i < _currentLinkerFlow->flowOutputs.size(); i++)
	{
		// Process the variable names for this flow
		ProcessVariableNamesHelper(_currentLinkerFlow->flowOutputs[i]);
	}

	return true;
}

bool Flux::FunctionLinker::GetVariableNameFromFlowData(Flux::FunctionFlow* _currentFunctionFlow, Flux::FunctionFlow::FlowVariableObject* _flowVariableData, std::string& _variableName)
{
	// Null
	_variableName = "null";

	// Check the variable type
	if (_flowVariableData->variableType == Flux::FunctionFlow::FlowVariableType::None)
	{
		// We have a problem!
		return false;
	}
	// Local function variable
	else if (_flowVariableData->variableType == Flux::FunctionFlow::FlowVariableType::LocalVariable)
	{
		// Check if the reference box is a dynamic function
		if (m_BoxReference->GetType() != Flux::Box::BoxType::DynamicFunction)
		{
			// Invalid type
			return false;
		}

		// Cast to a dynamic function
		Flux::DynamicFunction* function = static_cast<Flux::DynamicFunction*>(m_BoxReference);

		// Get the local variable definition from the function
		Flux::Variable* localVariable = function->GetLocalVariable(_flowVariableData->variableHandle);
		if (localVariable == nullptr)
		{
			return false;
		}

		// Set the variable name
		_variableName = localVariable->GetName();
	}
	// Class member variable
	else if (_flowVariableData->variableType == Flux::FunctionFlow::FlowVariableType::MemberVariable)
	{
		// Check if the reference box is a class function (dynamic member function)
		if (m_BoxReference->GetType() != Flux::Box::BoxType::DynamicMemberFunction)
		{
			// Invalid type
			return false;
		}

		// Cast to a dynamic member function
		Flux::DynamicMemberFunction* function = static_cast<Flux::DynamicMemberFunction*>(m_BoxReference);

		// Get the class owner handle
		Flux::Handle classOwnerHandle = function->GetClassOwner();

		// Get the class object from the class handle
		Flux::Class* classOwner = ClassRegister::GetInstance()->GetClass(classOwnerHandle);
		if (classOwner == nullptr)
		{
			return false;
		}

		// Get the member variable definition from the class
		Flux::MemberVariable* memberVariable = classOwner->GetMemberVariable(_flowVariableData->variableHandle);
		if (memberVariable == nullptr)
		{
			return false;
		}

		// Set the variable name
		_variableName = memberVariable->GetName();
	}
	// Global variable declared outside our scope
	else if (_flowVariableData->variableType == Flux::FunctionFlow::FlowVariableType::GlobalVariable)
	{
		// Check if the we have a variable with this handle inside the global defitions
		// ...

		// Generate the variable name
		// ...
	}
	// Return from a function
	else if (_flowVariableData->variableType == Flux::FunctionFlow::FlowVariableType::FunctionReturn)
	{
		// Get the function flow we should look for the variable
		Flux::FunctionFlow* originFlow = m_FunctionBodyReference->GetFlowById(_flowVariableData->flowReturnId);
		if (originFlow == nullptr)
		{
			return false;
		}

		// Find the linker flow by cross reference with the origin flow
		Flux::FunctionLinkerFlow* originLinkerFlow = FindLinkerFlowByCrossReference(originFlow);
		if (originLinkerFlow == nullptr)
		{
			return false;
		}

		// For each output variable inside the original flow
		bool found = false;
		Flux::FunctionLinkerFlow::LinkerVariableObject* linkerVariable = nullptr;
		for (int i = 0; i < originFlow->flowOutputVariables.size(); i++)
		{
			// Compare the handles
			if (originFlow->flowOutputVariables[i].variableHandle.CompareHandle(_flowVariableData->variableHandle))
			{
				// Set the variable
				linkerVariable = &originLinkerFlow->flowOutputVariables[i];

				// Set that we found the variable
				found = true;
			}
		}

		// Check if we found the variable
		if (!found)
		{
			return false;
		}

		// Check if the variable was set
		// ...
	
		// Set the variable name
		_variableName = linkerVariable->variableName;
	}
	else
	{
		// Invalid enum!
		return false;
	}

	return true;
}

Flux::FunctionLinkerFlow* Flux::FunctionLinker::FindLinkerFlowByCrossReference(Flux::FunctionFlow* _functionFlow)
{
	// For each linker flows
	for (int i = 0; i < m_LinkerFlows.size(); i++)
	{
		// Compare the id references
		if (m_LinkerFlows[i]->functionFlowIdReference == _functionFlow->flowId && m_LinkerFlows[i]->functionFlowReference == _functionFlow)
		{
			return m_LinkerFlows[i];
		}
	}

	return nullptr;
}

/*

- O que falta agora é criar uma classe de linker que irá iniciar o processo de linkagem, essa classe deve ter um gerador de nome e funções práticas de localização
de nome de variáveis por exemplo, além de facilitadores na hora de lidar com os objetos do tipo FlowObject.
- Essa classe incorporará muita coisa parecida desta mas isso é esperado, teremos que armazenar os nomes criados na hora da linkagem então precisaremos de uma
estrutura parecida com a qual foi utilizada aqui.
- Talvez seja bom ter um enum na box que indique de que tipo a mesma é, pois assim poderemos fazer um safe cast eficiente.

*/

// aqui ^