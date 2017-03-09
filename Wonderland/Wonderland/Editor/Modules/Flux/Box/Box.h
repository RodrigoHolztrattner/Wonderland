////////////////////////////////////////////////////////////////////////////////
// Filename: Box.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "..\Handle\Handle.h"
#include "..\Socket\SocketType.h"
#include "..\Socket\SocketExecution.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Flux workspace
NamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// Class name: Box
////////////////////////////////////////////////////////////////////////////////
class Box : public Flux::Handle
{
public:

	// The box types (reflects the parent type, used for derived cast)
	enum class BoxType
	{
		Undefined,
		DynamicFunction,
		DynamicMemberFunction
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	Box();
	Box(std::string _name);
	~Box();

//////////////////
// MAIN METHODS //
public: //////////

	// Get the name
	std::string GetName();

	// Return the type
	BoxType GetType();

	// Add //

	// Add an output execution socket
	bool AddOutputExecutionSocket(Flux::SocketExecution _executionSocket);

	// Add an input socket
	bool AddInputSocket(Flux::SocketType _socket);

	// Add an output socket
	bool AddOutputSocket(Flux::SocketType _socket);

	// Get //

	// Return the reference for the execution input socket
	Flux::SocketExecution* GetInputExecutionReference();

	// Return a reference for the given execution output socket
	Flux::SocketExecution* GetOutputExecutionSocket(unsigned int _socketIndex);
	Flux::SocketExecution* GetOutputExecutionSocket(Flux::Handle _socketHandle);

	// Return a reference for the given input socket
	Flux::SocketType* GetInputSocket(unsigned int _socketIndex);
	Flux::SocketType* GetInputSocket(Flux::Handle _socketHandle);

	// Return a reference for the given output socket
	Flux::SocketType* GetOutputSocket(unsigned int _socketIndex);
	Flux::SocketType* GetOutputSocket(Flux::Handle _socketHandle);

	// Find //

	// Find an execution socket with the given handle
	Flux::SocketExecution* FindOutputExecutionSocket(Flux::Handle _socketHandle);

	// Find an input socket with the given handle
	Flux::SocketType* FindInputSocket(Flux::Handle _socketHandle);

	// Find an output socket with the given handle
	Flux::SocketType* FindOutputSocket(Flux::Handle _socketHandle);

///////////////
// VARIABLES //
private: //////

	// The box name
	std::string m_Name;

	// The box type
	BoxType m_Type;

	// Our input call soket
	Flux::SocketExecution m_InputCallSoket;

	// Our output call sockets
	std::vector<Flux::SocketExecution> m_OutputCallSockets;

	// All the inputs and outputs
	std::vector<Flux::SocketType> m_Inputs;
	std::vector<Flux::SocketType> m_Outputs;
};

// Flux workspace
NamespaceEnd(Flux)