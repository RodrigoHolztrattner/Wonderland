////////////////////////////////////////////////////////////////////////////////
// Filename: HGInputController.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "HGWidget.h"
#include "HGInputDispatcher.h"
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

// We know the Widget class
class HGWidget;
class HGWindow;

////////////////////////////////////////////////////////////////////////////////
// Class name: HGInputController
////////////////////////////////////////////////////////////////////////////////
class HGInputController
{
public:
    
    // The Window is a friend class
    friend HGWindow;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGInputController();
	~HGInputController();

//////////////////
// MAIN METHODS //
public: //////////
   
	// Process all input commands
	void ProcessInputCommands(HGWidget* _mainWidget, HGInputDispatcher& _inputDispatcher);

private:

	// Process a mouse input recursivelly for this widget
	bool ProcessMouseInput(HGWidget* _currentWidget, HGInputCommand& _input);

///////////////
// VARIABLES //
private: //////
    
    // The widget on focus
    HGWidget* m_FocusWidget;
};

// HookGui workspace
NamespaceEnd(HookGui)
