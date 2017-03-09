////////////////////////////////////////////////////////////////////////////////
// Filename: FInput.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FInput_H_
#define _FInput_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "Containers\Array\TArray.h"

/////////////
// DEFINES //
/////////////

// The input types
enum class InputTypes
{
	Mouse,
	Keyboard
};

// The input message 
struct InputMessage
{
	// The input type
	InputTypes type;

	// The button (what button for both the mouse and the keyboard)
	unsigned int button;

	// The action ID (press, release or hold)
	unsigned int actionID;

	// The long param (usually the mouse x position)
	unsigned int longParam;

	// The short param (usually the mouse y position)
	unsigned int shortParam;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FInput
////////////////////////////////////////////////////////////////////////////////
class FInput
{
public:

	// The iterator class
	class Iterator
	{
	public:

		Iterator()
		{
			// Get the messages references
			m_InputMessages = FInput::GetInputMessages();
		}
		Iterator(const Iterator& other)
		{
			m_InputMessages = other.m_InputMessages;
			m_IndexPosition = other.m_IndexPosition;
		}
		~Iterator()
		{
		}

		// Start the iteraction
		void Begin()
		{
			m_IndexPosition = 0;
		}

		// Go to the next object
		void Next()
		{
			m_IndexPosition++;
		}

		// Check if we reached the end
		bool End()
		{
			return m_IndexPosition < m_InputMessages->Size();
		}

		// Remove the current object
		void RemoveCurrent()
		{
			m_InputMessages->Remove(m_IndexPosition);
			m_IndexPosition--;
		}

		// Return the index value
		InputMessage operator()() const
		{
			return (*(m_InputMessages))[m_IndexPosition];
		}

	private:

		// The input messages reference
		TArray<InputMessage>* m_InputMessages;

		// The current index position
		unsigned int m_IndexPosition;
	};

public:
	FInput();
	FInput(const FInput&);
	~FInput();

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Register a input message
	static void RegisterInputMessage(InputMessage _message)
	{
		m_InputMessages.Add(_message);
	}

	// <GLOBAL> Clear all input messages
	static void ClearInputMessages()
	{
		m_InputMessages.Zero();
	}

private:

	// <GLOBAL> Return the input messages
	static TArray<InputMessage>* GetInputMessages()
	{
		return &m_InputMessages;
	}

private:

	////////////
	// GLOBAL //
	////////////

	// The message array
	static TArray<InputMessage> m_InputMessages;
};

#endif
