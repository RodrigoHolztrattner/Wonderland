////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionMaker.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <vector>
#include "FluxFunctionAssembler.h"
#include "FluxFunction.h"


///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxFunctionMaker
////////////////////////////////////////////////////////////////////////////////
class FluxFunctionMaker : public FluxFunctionAssembler
{
/////////////
// DEFINES //
public: /////



//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxFunctionMaker();
	~FluxFunctionMaker();

//////////////////
// MAIN METHODS //
public: //////////

	// Make a function
	bool MakeFunction(FluxFunction* _function);

private:

	// Set the working function
	bool ProcessFunctionLink(FluxFunction* _fromFunction, unsigned int _functionId, std::string& _outputString, unsigned int _ident);

private:

	// Write to string (temp)
	void WriteToString(std::string _whatToWrite, std::string& _toString, unsigned int _ident, bool _souldIdent = true);


////////////////////
// INPUT / OUTPUT //
public: ////////////

///////////////
// VARIABLES //
protected: ////




};