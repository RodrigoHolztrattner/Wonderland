////////////////////////////////////////////////////////////////////////////////
// Filename: CommandDispatcher.cpp
////////////////////////////////////////////////////////////////////////////////
#include "CommandDispatcher.h"

///////////////
// NAMESPACE //
///////////////

CommandDispatcher::CommandDispatcher()
{
}

CommandDispatcher::CommandDispatcher(const CommandDispatcher& other)
{
}

CommandDispatcher::~CommandDispatcher()
{
}

void CommandDispatcher::AddCommand(CommandType _command)
{
	// Insert the command
	m_CommandArray.Add(_command);
}

CommandType CommandDispatcher::GetNextCommand()
{
	// Return the first command
	CommandType command = m_CommandArray.Get(0);

	// Remove the command
	m_CommandArray.Remove(0);

	return command;
}

bool CommandDispatcher::Empty()
{
	return !m_CommandArray.Size();
}