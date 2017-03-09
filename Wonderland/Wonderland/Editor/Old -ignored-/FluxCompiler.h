////////////////////////////////////////////////////////////////////////////////
// Filename: FluxCompiler.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "VariableNameProvider.h"
#include <string>
#include "..\..\Support\Container\Array\Array.h"
#include "VariableObject.h"
#include "Type\FluxType.h"
#include "LinkObject.h"
#include "Plug\FluxPlugReference.h"

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
// Class name: FluxCompiler
////////////////////////////////////////////////////////////////////////////////
class FluxCompiler
{
/////////////
// DEFINES //
public: /////

	
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxCompiler();
	~FluxCompiler();

//////////////////
// MAIN METHODS //
public: //////////

	// Compile a link this object
	virtual bool CompileLink(std::string* _compileString, LinkObject* _link, unsigned int _fromLinkInput = 0) = 0;

////////////////////
// INPUT / OUTPUT //
public: ////////////

	// Add an input/output object
	FluxPlugReference* AddInputPlug(FluxPlugReference* _plug);
	FluxPlugReference* AddOutputPlug(FluxPlugReference* _plug);

	// Remove an input/output object
	// ...
	// ...

	// Change an input/output object name
	bool ChangeInputPlugName(std::string _objectName, std::string _newName);
	bool ChangeOutputPlugName(std::string _objectName, std::string _newName);

	// Return the number of input/output parameters
	unsigned int GetNumberInputPlugs();
	unsigned int GetNumberOutputPlugs();

	// Return a input/output parameter
	FluxPlugReference* GetOutputPlug(unsigned int _id);
	FluxPlugReference* GetInputPlug(unsigned int _id);

private:

	// Find an object with the given name
	FluxPlugReference* FindPlugWithName(Array<FluxPlugReference*>* _from, std::string _name);

///////////////
// VARIABLES //
protected: ////

	// The input/output types
	Array<FluxPlugReference*> m_InputPlugs;
	Array<FluxPlugReference*> m_OutputPlugs;
};