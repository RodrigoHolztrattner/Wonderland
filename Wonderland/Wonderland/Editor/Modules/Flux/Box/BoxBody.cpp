////////////////////////////////////////////////////////////////////////////////
// Filename: FluxBoxBody.cpp
////////////////////////////////////////////////////////////////////////////////
#include "BoxBody.h"

Flux::BoxBody::BoxBody()
{
}

Flux::BoxBody::BoxBody(Flux::Box* _boxReference)
{
	// Set the initial data
	m_BoxReference = _boxReference;
}

Flux::BoxBody::~BoxBody()
{
}