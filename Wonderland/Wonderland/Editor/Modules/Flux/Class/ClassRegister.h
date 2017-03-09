////////////////////////////////////////////////////////////////////////////////
// Filename: ClassRegister.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "Class.h"

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
// ClassRegister name: ClassRegister
////////////////////////////////////////////////////////////////////////////////
class ClassRegister
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	ClassRegister();
	~ClassRegister();

//////////////////
// MAIN METHODS //
public: //////////

	 // Return a instance to this class
	static ClassRegister* GetInstance()
	{
		// The instance
		static Flux::ClassRegister* classRegister = nullptr;
		if (classRegister == nullptr)
		{
			// Create the new class register object
			classRegister = new Flux::ClassRegister();
		}

		return classRegister;
	}

	// Register a new class
	bool RegisterClass(Flux::Class* _newClass);

	// Return a registered class with the given name
	Flux::Class* GetClass(std::string _name);

	// Return a registered class with the given handle
	Flux::Class* GetClass(Flux::Handle _classHandle);

	// Check if a class with a given name already exist
	bool ClassWithNameExists(std::string _className);

private:

	// Find a class by name
	Flux::Class* FindClassByName(std::string _name);

	// Find a class by handle
	Flux::Class* FindClassByHandle(Flux::Handle _handle);

///////////////
// VARIABLES //
private: //////

	// All the classes
	std::vector<Flux::Class*> m_RegisteredClasses;
};

// Flux workspace
NamespaceEnd(Flux)
