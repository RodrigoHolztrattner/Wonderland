////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionValidator.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionValidator.h"

FluxFunctionValidator::FluxFunctionValidator()
{
    // Set the initial data
	// ...
}

FluxFunctionValidator::~FluxFunctionValidator()
{
}

bool FluxFunctionValidator::ValidateFunction(FluxFunction* _function)
{
	// Check if the function is valid
	if (_function == nullptr)
	{
		return false;
	}

	// We cant validate text body like functions
	if (_function->GetFunctionBodyType() == FluxFunctionHeader::FunctionBodyType::Text)
	{
		return true; // We cant say it is invalid
	}

	return true;
}