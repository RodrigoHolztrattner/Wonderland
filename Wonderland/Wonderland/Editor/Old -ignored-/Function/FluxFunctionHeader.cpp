////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionHeader.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionHeader.h"
#include <json.hpp>
#include <fstream>

FluxFunctionHeader::FluxFunctionHeader()
{
    // Set the initial data
    // ...
}

FluxFunctionHeader::~FluxFunctionHeader()
{
}

bool FluxFunctionHeader::CreateNewHeader(std::string _functionName, FunctionType _functionType, FunctionBodyType _functionBodyType)
{
	// Set the data
	m_FunctionDefinition.functionName = _functionName;
	m_FunctionDefinition.functionType = _functionType;
	m_FunctionDefinition.functionBodyType = _functionBodyType;
	m_FunctionDefinition.functionVersion = 0;
	m_FunctionDefinition.functionId = 0;
	m_FunctionDefinition.classOwner = "dummy";
	m_FunctionDefinition.currentParameterId = 0;
	// ...

	return true;
}

void FluxFunctionHeader::IncrementVersion()
{
	m_FunctionDefinition.functionVersion++;
}

void FluxFunctionHeader::AddInputParam(std::string _paramName, std::string _paramType)
{
	// Create the object
	FunctionParameter newParameter;

	// Set the data
	newParameter.parameterName = _paramName;
	newParameter.parameterType = _paramType;
	newParameter.parameterId = m_FunctionDefinition.currentParameterId++;

	// Add it
	m_FunctionDefinition.inputParameters.push_back(newParameter);
}

void FluxFunctionHeader::AddOutputParam(std::string _paramName, std::string _paramType)
{
	// Create the object
	FunctionParameter newParameter;

	// Set the data
	newParameter.parameterName = _paramName;
	newParameter.parameterType = _paramType;
	newParameter.parameterId = m_FunctionDefinition.currentParameterId++;

	// Add it
	m_FunctionDefinition.outputParameters.push_back(newParameter);
}

bool FluxFunctionHeader::SaveFunctionHeader(std::string _fileName)
{
	// Create the file
	std::ofstream ifs(_fileName);

	// create an empty structure (null)
	nlohmann::json j;
	
	// Set the json data
	j["fname"] = m_FunctionDefinition.functionName;
	j["fid"] = m_FunctionDefinition.functionId;
	j["fversion"] = m_FunctionDefinition.functionVersion;
	j["ftype"] = (int)m_FunctionDefinition.functionType;
	j["fbodytype"] = (int)m_FunctionDefinition.functionBodyType;
	j["fparameterid"] = m_FunctionDefinition.currentParameterId;
	j["fclassowner"] = m_FunctionDefinition.classOwner;
	j["ftotalinput"] = m_FunctionDefinition.inputParameters.size();
	j["ftotaloutput"] = m_FunctionDefinition.outputParameters.size();
	j["ftextbody"] = m_FunctionDefinition.functionTextBody;
	for (int i = 0; i < m_FunctionDefinition.inputParameters.size(); i++)
	{
		// Make the param name
		std::string paramName = "inputparam" + std::to_string(i);
		j[paramName]["name"] = m_FunctionDefinition.inputParameters[i].parameterName;
		j[paramName]["type"] = m_FunctionDefinition.inputParameters[i].parameterType;
		j[paramName]["id"] = m_FunctionDefinition.inputParameters[i].parameterId;
	}
	for (int i = 0; i < m_FunctionDefinition.outputParameters.size(); i++)
	{
		// Make the param name
		std::string paramName = "outputparam" + std::to_string(i);
		j[paramName]["name"] = m_FunctionDefinition.outputParameters[i].parameterName;
		j[paramName]["type"] = m_FunctionDefinition.outputParameters[i].parameterType;
		j[paramName]["id"] = m_FunctionDefinition.outputParameters[i].parameterId;
	}

	// Save the data
	ifs << j;

	// Close the file
	ifs.close();

	return true;
}

bool FluxFunctionHeader::LoadFunctionHeader(std::string _fileName)
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
	m_FunctionDefinition.functionName = j["fname"].get<std::string>();
	m_FunctionDefinition.functionId = j["fid"].get<unsigned int>();
	m_FunctionDefinition.functionVersion = j["fversion"].get<unsigned int>();
	m_FunctionDefinition.functionType = (FunctionType)j["ftype"].get<int>();
	m_FunctionDefinition.functionBodyType = (FunctionBodyType)j["fbodytype"].get<int>();
	m_FunctionDefinition.currentParameterId = j["fparameterid"].get<unsigned int>();
	m_FunctionDefinition.classOwner = j["fclassowner"].get<std::string>();
	unsigned int totalInputParameters = j["ftotalinput"].get<unsigned int>();
	unsigned int  totalOutputParameters = j["ftotaloutput"].get<unsigned int>();
	m_FunctionDefinition.functionTextBody = j["ftextbody"].get<std::string>();

	// Read all input parameters
	for (int i = 0; i < totalInputParameters; i++)
	{
		// Make the param name
		std::string paramName = "inputparam" + std::to_string(i);
		FunctionParameter newInputParameter;

		// Set the data
		newInputParameter.parameterName = j[paramName]["name"].get<std::string>();
		newInputParameter.parameterType = j[paramName]["type"].get<std::string>();
		newInputParameter.parameterId = j[paramName]["id"].get<unsigned int>();

		// Add it
		m_FunctionDefinition.inputParameters.push_back(newInputParameter);
	}

	// Real all output parameters
	for (int i = 0; i < totalOutputParameters; i++)
	{
		// Make the param name
		std::string paramName = "outputparam" + std::to_string(i);
		FunctionParameter newOutputParameter;

		// Set the data
		newOutputParameter.parameterName = j[paramName]["name"].get<std::string>();
		newOutputParameter.parameterType = j[paramName]["type"].get<std::string>();
		newOutputParameter.parameterId = j[paramName]["id"].get<unsigned int>();

		// Add it
		m_FunctionDefinition.outputParameters.push_back(newOutputParameter);
	}

	// Close the file
	file.close();

	return true;
}

std::string FluxFunctionHeader::GetFunctionName()
{
	return m_FunctionDefinition.functionName;
}

unsigned int FluxFunctionHeader::GetFunctionId()
{
	return m_FunctionDefinition.functionId;
}

unsigned int FluxFunctionHeader::GetCurrentVersion()
{
	return m_FunctionDefinition.functionVersion;
}

FluxFunctionHeader::FunctionType FluxFunctionHeader::GetFunctionType()
{
	return m_FunctionDefinition.functionType;
}

FluxFunctionHeader::FunctionBodyType FluxFunctionHeader::GetFunctionBodyType()
{
	return m_FunctionDefinition.functionBodyType;
}

std::string FluxFunctionHeader::GetFunctionClassOwner()
{
	return m_FunctionDefinition.classOwner;
}

unsigned int FluxFunctionHeader::GetInputSize()
{
	return m_FunctionDefinition.inputParameters.size();
}

unsigned int FluxFunctionHeader::GetOutputSize()
{
	return m_FunctionDefinition.outputParameters.size();
}

FluxFunctionHeader::FunctionParameter FluxFunctionHeader::GetInputParameter(unsigned int _index)
{
	return m_FunctionDefinition.inputParameters[_index];
}

FluxFunctionHeader::FunctionParameter FluxFunctionHeader::GetOutputParameter(unsigned int _index)
{
	return m_FunctionDefinition.outputParameters[_index];
}