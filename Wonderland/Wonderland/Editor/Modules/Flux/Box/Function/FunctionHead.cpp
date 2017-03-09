////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionHead.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FunctionHead.h"

Flux::FunctionHead::FunctionHead()
{
}

Flux::FunctionHead::~FunctionHead()
{
}

bool Flux::FunctionHead::AddLocalVariable(Flux::Variable _variable)
{
	// Check if the variable is valid
	// ...

	// Check if we can add this variable
	// ...

	// Add the variable
	m_LocalVariables.push_back(_variable);

	return true;
}

Flux::Variable* Flux::FunctionHead::GetLocalVariable(Flux::Handle _variableHandle)
{
	// For each local variable
	for (int i = 0; i < m_LocalVariables.size(); i++)
	{
		// Get the local variable
		Flux::Variable* localVariable = &m_LocalVariables[i];

		// Compare the handle
		if (localVariable->CompareHandle(_variableHandle))
		{
			return localVariable;
		}
	}

	return nullptr;
}