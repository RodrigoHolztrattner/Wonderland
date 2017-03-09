////////////////////////////////////////////////////////////////////////////////
// Filename: InputDispatcher.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include <vector>
#include <string>

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

// HookGui workspace
NamespaceBegin(HookGui)

//////////
// ENUM //
//////////

// The input author (who did the input)
enum class InputAuthor
{
    Unknow,
    System,     // System input
    Mouse,
    Keyboard
};

// The input event type
enum class InputEvent
{
    Unknow,
    Press,      // Mouse or keyboard
    Release,    // Mouse or keyboard
    Hold,       // Mouse or keyboard
    Hover,      // Mouse hover
    Update      // System passive update
};

// The key action
enum class InputKey
{
    Unknow,
    Right,
    Left,
    Middle,
    Keyboard,
    Other
};

////////////
// STRUCT //
////////////

// The input command itself
struct InputCommand
{
    // The input author
    InputAuthor inputAuthor;
    
    // The event itself
    InputEvent inputEvent;
    
    // The key action
    InputKey inputKey;
    
    // The key param (used by the keyboard)
    unsigned int keyParam;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: InputDispatcher
////////////////////////////////////////////////////////////////////////////////
class InputDispatcher
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	InputDispatcher();
	~InputDispatcher();

//////////////////
// MAIN METHODS //
public: //////////
    
    // Insert a mouse input
    // ...
    
    // Insert a keyboard input
    // ...
    
    //
    
    // Initialize the iterator
    void StartIterator();
    
    // Get the current iterator input
    InputCommand GetIteratorInput();
    
    // Consume the current iterator input
    void ConsumeIteratorInput();
    
    // Go to the next input
    void IteratorIncrement();
    
    // Check if the current iterator is valid
    bool IteratorIsValid();
    
///////////////
// VARIABLES //
private: //////
    
    // The input array
    std::vector<InputCommand> m_InputArray;
    
    // The iterator
    unsigned int m_Iterator;
};

// HookGui workspace
NamespaceEnd(HookGui)
