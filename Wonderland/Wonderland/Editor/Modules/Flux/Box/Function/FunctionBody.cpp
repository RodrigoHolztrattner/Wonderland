////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionBody.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FunctionBody.h"

Flux::FunctionBody::FunctionBody()
{
}

Flux::FunctionBody::FunctionBody(Flux::Box* _boxReference)
{
	// Set the initial data
	// m_BoxReference = _boxReference;
}

Flux::FunctionBody::~FunctionBody()
{
}

Flux::FunctionFlow* Flux::FunctionBody::GetInitialFlow()
{
	return &m_StartFlow;
}

Flux::FunctionFlow* Flux::FunctionBody::GetFlowById(unsigned int _flowId)
{
	// For each flow
	for (int i = 0; i < m_FlowArray.size(); i++)
	{
		// Compare the ids
		if (m_FlowArray[i]->flowId == _flowId)
		{
			return m_FlowArray[i];
		}
	}

	return nullptr;
}