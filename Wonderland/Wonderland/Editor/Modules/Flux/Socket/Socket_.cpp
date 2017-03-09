////////////////////////////////////////////////////////////////////////////////
// Filename: Socket.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Socket.h"

Flux::Socket::Socket()
{
	// Set the initial data
	m_IsVisible = true;
}

Flux::Socket::Socket(std::string _socketName) // Editor name
{
	// Set the initial data
	m_EditorName = _socketName;
	m_IsVisible = true;
}

Flux::Socket::~Socket()
{
}
