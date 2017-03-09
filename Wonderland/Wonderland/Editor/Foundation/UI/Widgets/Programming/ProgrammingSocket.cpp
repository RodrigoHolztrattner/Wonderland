////////////////////////////////////////////////////////////////////////////////
// Filename: ProgrammingSocket.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ProgrammingSocket.h"

///////////////
// NAMESPACE //
///////////////

#include "..\..\..\ECS\ECS_System.h"
#include "..\..\Components\Tree\UITreeComponent.h"
#include "..\..\Components\State\UIStateComponent.h"
#include "..\..\Components\Frame\UIFrameComponent.h"
#include "..\..\Components\Command\UICommandComponent.h"
#include "..\..\Components\Renderable\Color\UIColorComponent.h"
#include "..\..\Components\Renderable\Border\UIBorderComponent.h"
#include "..\..\Components\Frame\UIRelativeFrameComponent.h"
#include "..\..\Components\Frame\Anchor\UIAnchorComponent.h"
#include "UIProgrammingLine.h"

ProgrammingSocket::ProgrammingSocket()
{
	// Set the initial data
	m_Type = Type::Flow;
	m_Behavior = Behavior::In;
}

ProgrammingSocket::ProgrammingSocket(const ProgrammingSocket& other)
{
}

ProgrammingSocket::~ProgrammingSocket()
{
}


bool ProgrammingSocket::MakeLink(ProgrammingSocket* _otherSocket, UIProgrammingLine* _line)
{
	// Check the type and behavior (we need same types (flow/data) and different behaviors (in/out))
	if (m_Type != _otherSocket->GetType() || m_Behavior == _otherSocket->GetBehavior() || _otherSocket == this)
	{
		// Log
		std::cout << "Warning: Cant link with an socket with different type or same behavior or same ID!" << std::endl;

		return false;
	}

	// If this is an out socket, we can only have one link
	while (m_LinkArray.Size() && m_Behavior == Behavior::Out)
	{
		// Log
		std::cout << "Warning: Only one output can exist for this socket! (see Behavior::Out)" << std::endl;

		// Delete the line
		m_LinkArray[0].line->Destroy();

		// Delete this link
		m_LinkArray.Remove(0);
	}

	// Check if a link with this socket already exists
	for (int i = 0; i < m_LinkArray.Size(); i++)
	{
		// Log
		std::cout << "Warning: Removing duplicated link!" << std::endl;

		// Check the sockets
		if (m_LinkArray[i].socket == _otherSocket)
		{
			// Delete the line
			m_LinkArray[i].line->Destroy();

			// Remove this link
			m_LinkArray.Remove(i);
			i--;
		}
	}

	// Create the new link
	LinkType newLink;

	// Set the link data
	newLink.socket = _otherSocket;
	newLink.line = _line;

	// Add to the array
	m_LinkArray.Add(newLink);
	_otherSocket->m_LinkArray.Add(newLink);

	return true;
}

void ProgrammingSocket::SetType(Type _type)
{
	m_Type = _type;
}

void ProgrammingSocket::SetBehavior(Behavior _behavior)
{
	m_Behavior = _behavior;
}

ProgrammingSocket::Type ProgrammingSocket::GetType()
{
	return m_Type;
}

ProgrammingSocket::Behavior ProgrammingSocket::GetBehavior()
{
	return m_Behavior;
}