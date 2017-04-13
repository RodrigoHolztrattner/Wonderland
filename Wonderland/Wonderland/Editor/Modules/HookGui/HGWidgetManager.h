////////////////////////////////////////////////////////////////////////////////
// Filename: HGWidgetManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "HGWidget.h"
#include "HGInputController.h"
#include "HGInputDispatcher.h"
#include "..\VulkanWrapper\VulkanWrapper.h"

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

////////////////////////////////////////////////////////////////////////////////
// Class name: HGWidgetManager
////////////////////////////////////////////////////////////////////////////////
class HGWidgetManager
{
public:
    
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGWidgetManager();
	~HGWidgetManager();

	// Initialize this
	bool Initialize(VulkanWrapper::Context* _context);

	// The main widget update function
	void Update(HGWidget* _mainWidget, float _timeElapsed);

	// Render all widgets from the given one
	void Render(HGWidget* _mainWidget);

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
private: //////

	// Our input dispatcher
	HGInputDispatcher m_InputDispatcher;

	// Our input controller
	HGInputController m_InputController;
};

// HookGui workspace
NamespaceEnd(HookGui)
