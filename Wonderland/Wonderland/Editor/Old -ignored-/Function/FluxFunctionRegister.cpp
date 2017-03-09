////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionRegister.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionRegister.h"
#include "FluxFunctionValidator.h"

FluxFunctionRegister::FluxFunctionRegister()
{
    // Set the initial data
	// ...
}

FluxFunctionRegister::~FluxFunctionRegister()
{
}

void FluxFunctionRegister::StoreFunction(FluxFunction* _function)
{
	// Get our instance
	FluxFunctionRegister* functionRegister = GetInstance();

	// Store the function
	functionRegister->m_FunctionStorage.push_back(_function);
}

FluxFunction* FluxFunctionRegister::GetFunction(std::string _functionName)
{
	// Get our instance
	FluxFunctionRegister* functionRegister = GetInstance();

	// For each stored function
	for (int i = 0; i < functionRegister->m_FunctionStorage.size(); i++)
	{
		// Compare the names
		if (!_functionName.compare(functionRegister->m_FunctionStorage[i]->GetFunctionName()))
		{
			return functionRegister->m_FunctionStorage[i];
		}
	}

	return nullptr;
}

FluxFunctionRegister* FluxFunctionRegister::GetInstance()
{
	// Our global instance
	static FluxFunctionRegister* functionRegister = nullptr;
	if (functionRegister == nullptr)
	{
		// Create a new instance
		functionRegister = new FluxFunctionRegister;
	}

	return functionRegister;
}