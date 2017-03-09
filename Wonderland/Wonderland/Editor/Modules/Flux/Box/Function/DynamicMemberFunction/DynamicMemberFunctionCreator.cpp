////////////////////////////////////////////////////////////////////////////////
// Filename: DynamicMemberFunctionCreator.cpp
////////////////////////////////////////////////////////////////////////////////
#include "DynamicMemberFunctionCreator.h"
#include "DynamicMemberFunctionRegister.h"
#include "DynamicMemberFunction.h"
#include "..\..\..\Class\ClassRegister.h"
#include "..\..\..\Class\Class.h"

Flux::DynamicMemberFunctionCreator::DynamicMemberFunctionCreator()
{
}

Flux::DynamicMemberFunctionCreator::~DynamicMemberFunctionCreator()
{
}

Flux::DynamicMemberFunction* Flux::DynamicMemberFunctionCreator::CreateDynamicMemberFunction(std::string _functionName, Flux::Handle _classHandle)
{
	// Get the global instances we will need
	Flux::ClassRegister* classRegisterInstance = Flux::ClassRegister::GetInstance();
	Flux::DynamicMemberFunctionRegister* DynamicMemberFunctionRegisterInstance = Flux::DynamicMemberFunctionRegister::GetInstance();

	// First we need to get the class object
	Flux::Class* functionClass = classRegisterInstance->GetClass(_classHandle);

	// Now we need to check if the class already have a member function with the same name
	if (functionClass->GetMemberFunction(_functionName))
	{
		// We already have a function with this name
		return nullptr;
	}

	// Now we can create our member function object and set the internal class handle to differentiate the owner
	Flux::DynamicMemberFunction* newDynamicMemberFunction = new Flux::DynamicMemberFunction(_functionName, _classHandle);

	// Generate a valid handle for the new member function
	newDynamicMemberFunction->GenerateHandle();

	// We need to register the function
	DynamicMemberFunctionRegisterInstance->RegisterFunction(newDynamicMemberFunction);

	return newDynamicMemberFunction;
}
