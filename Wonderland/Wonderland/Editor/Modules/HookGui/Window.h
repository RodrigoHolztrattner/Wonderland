////////////////////////////////////////////////////////////////////////////////
// Filename: Window.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "InputDispatcher.h"
#include "WidgetController.h"
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

/*
 
    => Window
 
        - Cada window vai teoricamente usar um contexto de opengl e vai se renderizar a parte de outras windows
        - Ela pode conter widget controllers filhos e é responsável por repassar eventos de input
 
    => WidgetController
 
        - Contem widgets filhos e faz as verificações de input neles
        - É usada para a implementação de delegates e pode conter código de processamento
        
    => Widget
 
        -
 
 
 
 
 
 
 */

// HookGui workspace
NamespaceBegin(HookGui)

////////////////////////////////////////////////////////////////////////////////
// Class name: Window
////////////////////////////////////////////////////////////////////////////////
class Window
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	Window();
	~Window();

//////////////////
// MAIN METHODS //
public: //////////
    
    // Initialize this window
    bool Initialize();
    
    // Update this window
    void Update(float _elapsedTime);
    
    // Shutdown this window
    void Shutdown();
    
public:
    
    // Return the input dispatcher for this window
    InputDispatcher* GetInputDispatcher();
    
private:
    
    // Process input
    void ProcessInput();
    
///////////////
// VARIABLES //
private: //////
    
    // The input dispatcher
    InputDispatcher m_InputDispatcher;
    
    // All the widget controllers (childs)
    std::vector<WidgetController*> m_WidgetControllers;
    
    // The controller frame (the root view should match this value)
    HookGui::Frame m_Frame;
    
    // Controllers
    bool m_IsHidden;
    bool m_CanInteract;
};

// HookGui workspace
NamespaceEnd(HookGui)
