////////////////////////////////////////////////////////////////////////////////
// Filename: DynamicFunction.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "..\FunctionHead.h"
#include "..\FunctionBody.h"

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
// Class name: DynamicFunction
////////////////////////////////////////////////////////////////////////////////
class DynamicFunction : public Flux::FunctionHead, public Flux::FunctionBody
{

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	DynamicFunction();
	DynamicFunction(std::string _name);
	~DynamicFunction();

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
private: //////

};

// Flux workspace
NamespaceEnd(Flux)