////////////////////////////////////////////////////////////////////////////////
// Filename: BoxCreator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "Box.h"

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

// Flux workspace
NamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// BoxCreator name: BoxCreator
////////////////////////////////////////////////////////////////////////////////
template <typename BoxCreatorClass, typename BoxClass>
class BoxCreator
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	BoxCreator() {}
	~BoxCreator() {}

//////////////////
// MAIN METHODS //
public: //////////

	// Return a instance to this class
	static BoxCreatorClass* GetInstance()
	{
		// The instance
		static BoxCreatorClass* BoxCreator = nullptr;
		if (BoxCreator == nullptr)
		{
			// Create the new class creator object
			BoxCreator = new BoxCreatorClass();
		}

		return BoxCreator;
	}

///////////////
// VARIABLES //
private: //////

};

// Flux workspace
NamespaceEnd(Flux)
