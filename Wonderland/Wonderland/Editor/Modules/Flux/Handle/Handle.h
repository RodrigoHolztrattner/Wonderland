////////////////////////////////////////////////////////////////////////////////
// Filename: Handle.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include "..\..\NamespaceDefinitions.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

#define ReturnIfOutBounds(_vector, _index, _return)	if (_index < 0 || _index >= _vector.size()) return _return;

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Flux workspace
NamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// Class name: Handle
////////////////////////////////////////////////////////////////////////////////
class Handle
{
	// Valid / invalid
	enum class State
	{
		Valid,
		Invalid
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	Handle();
	~Handle();

	// Generate a valid handle for this
	void GenerateHandle();

	// Compare 2 handles
	bool CompareHandle(Flux::Handle _handle);

	// Check if this handle is valid
	bool IsValid();

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
private: //////

	// The handle value
	unsigned long m_Value;

	// The internal state
	State m_State;

////////////
// GLOBAL //
public: ////

	// Set the current handle id
	static void SetCurrentGlobalHandle(unsigned long _currentHandle);

protected:

	// Return the current handle
	static unsigned long GetCurrentGlobalHandle();

private:

	// The current handle
	static unsigned long s_CurrentHandle;
};

// Flux workspace
NamespaceEnd(Flux)
