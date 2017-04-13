////////////////////////////////////////////////////////////////////////////////
// Filename: HGInputDispatcher.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include <vector>
#include <string>
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

//////////
// ENUM //
//////////

// The input author (who did the input)
enum class HGInputAuthor
{
    Unknow,
    System,     // System input
    Mouse,
    Keyboard
};

// The input event type
enum class HGInputEvent
{
    Unknow,
    Press,      // Mouse or keyboard
    Release,    // Mouse or keyboard
	Repeat,		// Keyboard
    Hold,       // Mouse or keyboard
    Hover,      // Mouse hover
    Update      // System passive update
};

// The key action
enum class HGInputKey
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
struct HGInputCommand
{
    // The input author
    HGInputAuthor inputAuthor;
    
    // The event itself
    HGInputEvent inputEvent;
    
    // The key action
    HGInputKey inputKey;
    
    // The key param (used by the keyboard)
    unsigned int keyParam;

	// The upper param
	unsigned int upperParam;

	// The lower param
	unsigned int lowerParam;

	// Map a glfw action into an input event
	static HGInputEvent MapActionFromGLFW(int _action)
	{
		switch(_action)
		{
			case GLFW_RELEASE:
			{
				return HGInputEvent::Release;
			}
			case GLFW_PRESS:
			{
				return HGInputEvent::Press;
			}
			case GLFW_REPEAT:
			{
				return HGInputEvent::Repeat;
			}
			default:
			{
				return HGInputEvent::Unknow;
			}
		}
	}

	// Map a glfw button into an input key
	static HGInputKey MapButtonFromGLFW(int _button)
	{
		switch (_button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
			{
				return HGInputKey::Left;
			}
			case GLFW_MOUSE_BUTTON_RIGHT:
			{
				return HGInputKey::Right;
			}
			case GLFW_MOUSE_BUTTON_MIDDLE:
			{
				return HGInputKey::Middle;
			}
			default:
			{
				return HGInputKey::Other;
			}
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
// Class name: HGInputDispatcher
////////////////////////////////////////////////////////////////////////////////
class HGInputDispatcher : public VulkanWrapper::WindowInputCallback
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGInputDispatcher();
	~HGInputDispatcher();

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
    HGInputCommand GetIteratorInput();
    
    // Consume the current iterator input
    void ConsumeIteratorInput();
    
    // Go to the next input
    void IteratorIncrement();
    
    // Check if the current iterator is valid
    bool IteratorIsValid();

protected:

	// Process a key callback
	void ProcessKeyCallback(int key, int scancode, int action, int mods) override;

	// Process a mouse callback
	void ProcessMouseCallback(int button, int action, int mods) override;
    
///////////////
// VARIABLES //
private: //////
    
    // The input array
    std::vector<HGInputCommand> m_InputArray; //TODO: Adicionar um lock para não correr riscos de escrever enquanto estamos lendo
    
    // The iterator
    unsigned int m_Iterator;
};

// HookGui workspace
NamespaceEnd(HookGui)
