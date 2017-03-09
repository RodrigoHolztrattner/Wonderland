////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunction.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunction.h"

FluxFunction::FluxFunction() : FluxFunctionBody(this)
{
    // Set the initial data
	// ...
}

FluxFunction::~FluxFunction()
{
}

bool FluxFunction::CreateNewFunction(std::string _functionName, FunctionType _functionType, FunctionBodyType _functionBodyType)
{
	// Create the header
	if (!CreateNewHeader(_functionName, _functionType, _functionBodyType))
	{
		return false;
	}

	// Create the body
	if (!CreateNewBody())
	{
		return false;
	}

	// Register this function as a type
	// ...

	return true;
}

bool FluxFunction::SaveFunction()
{
	// Set the header and body names
	std::string headerName = GetFunctionName() + "_header" + ".json";
	std::string bodyName = GetFunctionName() + "_body" + ".json";

	// Save the header
	if (!SaveFunctionHeader(headerName))
	{
		return false;
	}

	// Save the body
	if (!SaveFunctionBody(bodyName))
	{
		return false;
	}

	return true;
}

bool FluxFunction::LoadFunction(std::string _functionName)
{
	// Set the header and body names
	std::string headerName = _functionName + "_header" + ".json";
	std::string bodyName = _functionName + "_body" + ".json";

	// Save the header
	if (!LoadFunctionHeader(headerName))
	{
		return false;
	}

	// Save the body
	if (!LoadFunctionBody(bodyName))
	{
		return false;
	}

	return true;
}