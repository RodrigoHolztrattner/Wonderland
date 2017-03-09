////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionBody.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionBody.h"
#include "FluxFunctionRegister.h"
#include <json.hpp>
#include <fstream>

FluxFunctionBody::FluxFunctionBody(FluxFunctionHeader* _header)
{
    // Set the initial data
    m_HeaderReference = _header;
	m_CreationId = 0;


}

FluxFunctionBody::~FluxFunctionBody()
{
}

bool FluxFunctionBody::CreateNewBody()
{
	return true;
}

unsigned int FluxFunctionBody::CreateNewFunctionComponent(FluxFunctionHeader* _functionHeader)
{
    // Create the new function component
    FunctionComponent functionComponent;

    // Set the data
    functionComponent.functionData.functionName = _functionHeader->GetFunctionName();
    functionComponent.functionData.functionId = _functionHeader->GetFunctionId();
    functionComponent.functionData.functionVersion = _functionHeader->GetCurrentVersion();
    functionComponent.creationId = m_CreationId++;

    // Add to the array
    m_ComponentFunctions.push_back(functionComponent);

	// Increment the current version
	m_HeaderReference->IncrementVersion();

    // Return the creation id
    return functionComponent.creationId;
}

bool FluxFunctionBody::CreateNewLink(unsigned int _fromFunctionComponentId, unsigned int _toFunctionComponentId, unsigned int _fromParameterId, unsigned int _toParameterId)
{
	// Localiza a função de entrada e a de saida
	FunctionComponent* inputFunction = FindFunctionComponent(_fromFunctionComponentId);
	FunctionComponent* outputFunction = FindFunctionComponent(_toFunctionComponentId);

	// Verifica se os resultados estão válidos
	if (inputFunction == nullptr || outputFunction == nullptr)
	{
		// Erro, não achamos uma das funções!
		return false;
	}
	
	// Get the input function
	FluxFunctionHeader* inputFunctionHeader = FluxFunctionRegister::GetFunction(inputFunction->functionData.functionName);
	if (inputFunction == nullptr)
	{
		// Erro!
		return false;
	}

	// Pega o parâmetro de saida
	FluxFunctionHeader::FunctionParameter outputParameter = inputFunctionHeader->GetOutputParameter(_fromParameterId);
	
	// Descobre o tipo de link
	FunctionLinkType functionLinkType;
	if (FluxType::Compare(outputParameter.parameterType, FluxType::ExecutionVariable))
	{
		// Execution
		functionLinkType = FunctionLinkType::Execution;
	}
	// Can only be function
	else
	{
		// Function
		functionLinkType = FunctionLinkType::Function;
	}

	// Create the new link
	FunctionLink functionLink;

	// Verifica se o link é do tipo de execução
	if (functionLinkType == FunctionLinkType::Execution)
	{
		// Set the data
		functionLink.linkType = FunctionLinkType::Execution;
		functionLink.toComponentFunctionId = _toFunctionComponentId; // Apenas armazenamos esse valor pois estamos nos referindo para qual função seguiremos o fluxo
		functionLink.toParameterId = _toParameterId; // Não usado afinal cada função tem apenas uma entrada

		// Adiciona na input function
		inputFunction->functionOutputs.push_back(functionLink);
	}
	// Verifica se é do tipo função
	else if (functionLinkType == FunctionLinkType::Function)
	{
		// Set the data
		functionLink.linkType = FunctionLinkType::Function;
		functionLink.fromComponentFunctionId = _fromFunctionComponentId;
		functionLink.fromParameterId = _fromParameterId;
		functionLink.toParameterId = _toParameterId;

		// Adiciona na output function
		outputFunction->functionInputs.push_back(functionLink);
	}

	// Increment the current version
	m_HeaderReference->IncrementVersion();

	return true;
}

bool FluxFunctionBody::CreateNewLink(FluxVariable* _fromVariable, unsigned int _toFunctionComponentId, unsigned int _toParameterId)
{
	// Localiza a função de saida
	FunctionComponent* outputFunction = FindFunctionComponent(_toFunctionComponentId);

	// Create the new link
	FunctionLink functionLink;

	// Set the data
	functionLink.linkType = FunctionLinkType::Variable;
	functionLink.toParameterId = _toParameterId;
	functionLink.fromVariable.variableName = _fromVariable->GetName();
	functionLink.fromVariable.variableType = _fromVariable->GetType().GetName();
	functionLink.fromVariable.variableOrigin = VariableOriginType::Local;

	// Adiciona na output function
	outputFunction->functionInputs.push_back(functionLink);

	// Increment the current version
	m_HeaderReference->IncrementVersion();

	return true;
}

bool FluxFunctionBody::SaveFunctionBody(std::string _fileName)
{
	// Create the file
	std::ofstream ifs(_fileName);

	// create an empty structure (null)
	nlohmann::json j;

	/*

	// Set the json data
	j["fbodycreationid"] = m_CreationId;
	j["ftotalcomponents"] = m_ComponentFunctions.size();
	j["ftotallinks"] = m_FunctionLinks.size();
	
	// For each component function
	for (int i = 0; i < m_ComponentFunctions.size(); i++)
	{
		// Make the function component name
		std::string paramName = "functioncomponent" + std::to_string(i);

		// Save the function component data
		j[paramName]["name"] = m_ComponentFunctions[i].functionName;
		j[paramName]["id"] = m_ComponentFunctions[i].functionId;
		j[paramName]["version"] = m_ComponentFunctions[i].functionVersion;
		j[paramName]["creationid"] = m_ComponentFunctions[i].creationId;
	}
	for (int i = 0; i < m_FunctionLinks.size(); i++)
	{
		// Make the param name
		std::string paramName = "functionlink" + std::to_string(i);
		
		// Save the type and input slot
		j[paramName]["type"] = (int)m_FunctionLinks[i].linkType;
		j[paramName]["inputslot"] = m_FunctionLinks[i].toInputSlot;

		// Check the type
		if (m_FunctionLinks[i].linkType == FunctionLinkType::Function)
		{
			// Save the function data
			j[paramName]["functionslot"] = m_FunctionLinks[i].fromOutputSlot;
			j[paramName]["functionoutputid"] = m_FunctionLinks[i].fromFunctionOutputId;
			j[paramName]["functionoutputname"] = m_FunctionLinks[i].fromFunctionOutputName;
			j[paramName]["functionname"] = m_FunctionLinks[i].targetFunction.functionName;
			j[paramName]["functionid"] = m_FunctionLinks[i].targetFunction.functionId;
			j[paramName]["functionversion"] = m_FunctionLinks[i].targetFunction.functionVersion;
			j[paramName]["functioncreationid"] = m_FunctionLinks[i].targetFunction.creationId;
		}
		else
		{
			// Save the variable data
			j[paramName]["variablename"] = m_FunctionLinks[i].fromVariable.variableName;
			j[paramName]["variabletype"] = m_FunctionLinks[i].fromVariable.variableType;
			j[paramName]["variableorigin"] = (int)m_FunctionLinks[i].fromVariable.variableOrigin;
		}
	}

	*/

	// Save the data
	ifs << j;

	// Close the file
	ifs.close();

	return true;
}

bool FluxFunctionBody::LoadFunctionBody(std::string _fileName)
{
	// Open the file
	std::ifstream file(_fileName);

	// Check if the file exist
	if (!file.is_open())
	{
		return false;
	}

	// Create an empty structure (null)
	nlohmann::json j;

	// Create the structure
	file >> j;

	// Get the json data
	m_CreationId = j["fbodycreationid"].get<unsigned int>();
	unsigned int totalComponentFunctions = j["ftotalcomponents"].get<int>();
	unsigned int totalFunctionLinks = j["ftotallinks"].get<int>();

	/*
	// Read all input parameters
	for (int i = 0; i < totalComponentFunctions; i++)
	{
		// Make the function component name
		std::string paramName = "functioncomponent" + std::to_string(i);

		// Create the new function component
		FunctionComponent newFunctionComponent;

		// Get the function component data
		newFunctionComponent.functionName = j[paramName]["name"].get<std::string>();
		newFunctionComponent.functionId = j[paramName]["id"].get<unsigned int>();
		newFunctionComponent.functionVersion = j[paramName]["version"].get<unsigned int>();
		newFunctionComponent.creationId = j[paramName]["creationid"].get<unsigned int>();

		// Add it
		m_ComponentFunctions.push_back(newFunctionComponent);
	}

	// Real all output parameters
	for (int i = 0; i < totalFunctionLinks; i++)
	{
		// Make the param name
		std::string paramName = "functionlink" + std::to_string(i);

		// Create the new link
		FunctionLink newLink;

		// Get the typeand input slot
		newLink.linkType = (FunctionLinkType)j[paramName]["type"].get<int>();
		m_FunctionLinks[i].toInputSlot = j[paramName]["inputslot"].get<unsigned int>();

		// Check the type
		if (newLink.linkType == FunctionLinkType::Function)
		{
			// Get the function data
			newLink.fromOutputSlot = j[paramName]["functionslot"].get<unsigned int>();
			newLink.fromFunctionOutputId = j[paramName]["functionoutputid"].get<unsigned int>();
			newLink.fromFunctionOutputName = j[paramName]["functionoutputname"].get<std::string>();
			newLink.targetFunction.functionName = j[paramName]["functionname"].get<std::string>();
			newLink.targetFunction.functionId = j[paramName]["functionid"].get<unsigned int>();
			newLink.targetFunction.functionVersion = j[paramName]["functionversion"].get<unsigned int>();
			newLink.targetFunction.creationId = j[paramName]["functioncreationid"].get<unsigned int>();
		}
		else
		{
			// Get the variable data
			newLink.fromVariable.variableName = j[paramName]["variablename"].get<std::string>();
			newLink.fromVariable.variableType = j[paramName]["variabletype"].get<std::string>();
			newLink.fromVariable.variableOrigin = (VariableOriginType)j[paramName]["variableorigin"].get<int>();
		}

		// Add it
		m_FunctionLinks.push_back(newLink);
	}

	// Close the file
	file.close();

	*/

	return true;
}

FluxFunctionBody::FunctionComponent* FluxFunctionBody::FindFunctionComponent(unsigned int _creationId)
{
	// For each function stored
	for (int i = 0; i < m_ComponentFunctions.size(); i++)
	{
		// Compare the ids
		if (m_ComponentFunctions[i].creationId == _creationId)
		{
			return &m_ComponentFunctions[i];
		}
	}

	// Error!
	return nullptr;
}