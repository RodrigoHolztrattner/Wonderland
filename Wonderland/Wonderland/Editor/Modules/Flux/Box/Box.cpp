////////////////////////////////////////////////////////////////////////////////
// Filename: FluxBox.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Box.h"

Flux::Box::Box() : m_InputCallSoket("Input")
{
	// Set the initial data
	// ...

	// Generate a valid handle for the input call socket
	m_InputCallSoket.GenerateHandle();
}

Flux::Box::Box(std::string _name) : m_InputCallSoket("Input")
{
	// Set the initial data
	m_Name = _name;

	// Generate a valid handle for the input call socket
	m_InputCallSoket.GenerateHandle();
}

Flux::Box::~Box()
{
}

std::string Flux::Box::GetName()
{
	return m_Name;
}

Flux::Box::BoxType Flux::Box::GetType()
{
	return m_Type;
}

// Add //

bool Flux::Box::AddOutputExecutionSocket(Flux::SocketExecution _executionSocket)
{
	// Check if the socket is valid
	// ...

	// Add it
	m_OutputCallSockets.push_back(_executionSocket);

	return true;
}

bool Flux::Box::AddInputSocket(Flux::SocketType _socket)
{
	// Check if the socket is valid
	// ...

	// Add it
	m_Inputs.push_back(_socket);

	return true;
}

bool Flux::Box::AddOutputSocket(Flux::SocketType _socket)
{
	// Check if the socket is valid
	// ...

	// Add it
	m_Outputs.push_back(_socket);

	return true;
}

// Get //

Flux::SocketExecution* Flux::Box::GetInputExecutionReference()
{
	return &m_InputCallSoket;
}

Flux::SocketExecution* Flux::Box::GetOutputExecutionSocket(unsigned int _socketIndex)
{
	// Check if we are inbounds
	ReturnIfOutBounds(m_OutputCallSockets, _socketIndex, nullptr);

	return &m_OutputCallSockets[_socketIndex];
}

Flux::SocketExecution* Flux::Box::GetOutputExecutionSocket(Flux::Handle _socketHandle)
{
	return FindOutputExecutionSocket(_socketHandle);
}

Flux::SocketType* Flux::Box::GetInputSocket(unsigned int _socketIndex)
{
	// Check if we are inbounds
	ReturnIfOutBounds(m_Inputs, _socketIndex, nullptr);

	return &m_Inputs[_socketIndex];
}

Flux::SocketType* Flux::Box::GetInputSocket(Flux::Handle _socketHandle)
{
	return FindInputSocket(_socketHandle);
}

Flux::SocketType* Flux::Box::GetOutputSocket(unsigned int _socketIndex)
{
	// Check if we are inbounds
	ReturnIfOutBounds(m_Outputs, _socketIndex, nullptr);

	return &m_Outputs[_socketIndex];
}

Flux::SocketType* Flux::Box::GetOutputSocket(Flux::Handle _socketHandle)
{
	return FindOutputSocket(_socketHandle);
}

// Find //

Flux::SocketExecution* Flux::Box::FindOutputExecutionSocket(Flux::Handle _socketHandle)
{
	// For each socket
	for (int i=0; i<m_OutputCallSockets.size(); i++)
	{
		// Get the socket
		Flux::SocketExecution* socket = &m_OutputCallSockets[i];

		// Compare the handles
		if (socket->CompareHandle(_socketHandle))
		{
			return socket;
		}
	}

	return nullptr;
}

Flux::SocketType* Flux::Box::FindInputSocket(Flux::Handle _socketHandle)
{
	// For each socket
	for (int i = 0; i<m_Inputs.size(); i++)
	{
		// Get the socket
		Flux::SocketType* socket = &m_Inputs[i];

		// Compare the handles
		if (socket->CompareHandle(_socketHandle))
		{
			return socket;
		}
	}

	return nullptr;
}

Flux::SocketType* Flux::Box::FindOutputSocket(Flux::Handle _socketHandle)
{
	// For each socket
	for (int i = 0; i<m_Outputs.size(); i++)
	{
		// Get the socket
		Flux::SocketType* socket = &m_Outputs[i];

		// Compare the handles
		if (socket->CompareHandle(_socketHandle))
		{
			return socket;
		}
	}

	return nullptr;
}