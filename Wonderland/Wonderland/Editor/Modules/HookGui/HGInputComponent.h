////////////////////////////////////////////////////////////////////////////////
// Filename: HGInputComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "Widget\HGFrame.h"
#include "HGInputDispatcher.h"
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
class HGWidget;
class HGWindow;

////////////////////////////////////////////////////////////////////////////////
// Class name: HGInputComponent
////////////////////////////////////////////////////////////////////////////////
class HGInputComponent : public ReferenceCounter
{
public:
    
    // The Window is a friend class
    friend HGWindow;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGInputComponent();
	~HGInputComponent();

//////////////////
// MAIN METHODS //
public: //////////
    
private:
    
    // Process a input command
    bool EvaluateInput(HGInputCommand _inputCommand);
    
    // The destroy call
    virtual void DestroyWarning(){};
    
///////////////
// VARIABLES //
private: //////
    
    // The root view
    HGWidget* m_RootView;
    
    // The controller frame (the root view should match this value)
   //  HookGui::HGFrame m_Frame;
    
    // Controllers
    bool m_IsHidden;
    bool m_CanInteract;

	// If this widget must be in focus to receive inputs
	// ...
};

// HookGui workspace
NamespaceEnd(HookGui)
