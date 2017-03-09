////////////////////////////////////////////////////////////////////////////////
// Filename: WidgetController.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "Frame.h"
#include "InputDispatcher.h"
#include "ReferenceCounter.h"
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
class Widget;
class Window;

////////////////////////////////////////////////////////////////////////////////
// Class name: WidgetController
////////////////////////////////////////////////////////////////////////////////
class WidgetController : public ReferenceCounter
{
public:
    
    // The Window is a friend class
    friend Window;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	WidgetController();
	~WidgetController();

//////////////////
// MAIN METHODS //
public: //////////
    
private:
    
    // Process a input command
    bool EvaluateInput(InputCommand _inputCommand);
    
    // The destroy call
    virtual void DestroyWarning(){};
    
///////////////
// VARIABLES //
private: //////
    
    // The root view
    Widget* m_RootView;
    
    // The controller frame (the root view should match this value)
    HookGui::Frame m_Frame;
    
    // Controllers
    bool m_IsHidden;
    bool m_CanInteract;
};

// HookGui workspace
NamespaceEnd(HookGui)
