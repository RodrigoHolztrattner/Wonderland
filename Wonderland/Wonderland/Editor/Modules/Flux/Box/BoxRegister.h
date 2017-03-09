////////////////////////////////////////////////////////////////////////////////
// Filename: BoxRegister.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
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
// BoxRegister name: BoxRegister
////////////////////////////////////////////////////////////////////////////////
template <typename BoxRegisterClass, typename BoxClass>
class BoxRegister
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	BoxRegister() {}
	~BoxRegister() {}

//////////////////
// MAIN METHODS //
public: //////////

	 // Return a instance to this box register
	static BoxRegisterClass* GetInstance()
	{
		// The instance
		static BoxRegisterClass* boxRegister = nullptr;
		if (boxRegister == nullptr)
		{
			// Create the new class register object
			boxRegister = new BoxRegisterClass();
		}

		return boxRegister;
	}

	// Register a new box
	bool RegisterFunction(BoxClass* _newBox)
	{
		// Check if a Box with the same name already exists
		if (FunctionWithNameExists(_newBox->GetName()))
		{
			return false;
		}

		// Add the new Box into the registered array
		m_RegisteredBoxes.push_back(_newBox);
	}

	// Return a registered box with the given name
	BoxClass* GetFunction(std::string _name)
	{
		return FindBoxByName(_name);
	}

	// Return a registered box with the given handle
	BoxClass* GetFunction(Flux::Handle _BoxHandle)
	{
		return FindBoxByHandle(_BoxHandle);
	}

	// Check if a box with a given name already exist
	bool FunctionWithNameExists(std::string _BoxName)
	{
		return FindBoxByName(_BoxName) != nullptr;
	}

private:

	// Find a box by name
	BoxClass* FindBoxByName(std::string _name)
	{
		// For each registered Box
		for (auto boxObject : m_RegisteredBoxes)
		{
			// Compare the names
			if (!_name.compare(boxObject->GetName()))
			{
				return boxObject;
			}
		}

		return nullptr;
	}

	// Find a box by handle
	BoxClass* FindBoxByHandle(Flux::Handle _handle)
	{
		// For each registered Box
		for (auto BoxObject : m_RegisteredBoxes)
		{
			// Compare the names
			if (BoxObject->CompareHandle(_handle))
			{
				return BoxObject;
			}
		}

		return nullptr;
	}

///////////////
// VARIABLES //
private: //////

	// All the boxes
	std::vector<BoxClass*> m_RegisteredBoxes;
};

// Flux workspace
NamespaceEnd(Flux)
