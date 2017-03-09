////////////////////////////////////////////////////////////////////////////////
// Filename: CommandDispatcher.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\..\Support\Container\Array\StaticArray.h"

#include "CommandType.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: CommandDispatcher
////////////////////////////////////////////////////////////////////////////////
class CommandDispatcher
{
public:
	CommandDispatcher();
	CommandDispatcher(const CommandDispatcher&);
	~CommandDispatcher();

	// Add a command
	void AddCommand(CommandType _command);

	// Get the next command
	CommandType GetNextCommand();

	// Return false if we have no more commands
	bool Empty();

private:

	// The command array
	StaticArray<CommandType, 10> m_CommandArray;

};