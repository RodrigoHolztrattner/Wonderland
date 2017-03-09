////////////////////////////////////////////////////////////////////////////////
// Filename: SocketType.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SocketType.h"

Flux::SocketType::SocketType()
{
	// Set the initial data
	m_IsArray = false;
	m_IsPointer = false;
}

Flux::SocketType::SocketType(std::string _editorName, Flux::Type* _socketType) : Flux::Socket(_editorName)
{
	// Set the initial data
	m_SoketType = _socketType; // Check if the type is valid?
	m_IsArray = false;
	m_IsPointer = false;
}

Flux::SocketType::~SocketType()
{
}
