////////////////////////////////////////////////////////////////////////////////
// Filename: LinkObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "VariableNameProvider.h"
#include <string>
#include "VariableObject.h"
#include "..\..\Support\Container\Array\Array.h"
#include "Plug\FluxPlugObject.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

//
class FluxObject;

////////////////////////////////////////////////////////////////////////////////
// Class name: LinkObject
////////////////////////////////////////////////////////////////////////////////
class LinkObject
{
/////////////
// DEFINES //
public: /////

	/*
	// The link plug reference (we use this to generate valid names for variables when we need to compile)
	struct LinkPlugReference
	{
		LinkPlugReference() {}
		LinkPlugReference(FluxPlugObject* _plug, std::string _variableName = "")
		{
			plug = _plug;
			variableName = _variableName;
		}

		// The generated variable name (only usable by variables)
		std::string variableName;

		// The plug itself
		FluxPlugObject* plug;
	};
	*/

	// 
	friend FluxObject;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	LinkObject(FluxObject* _fluxObject, VariableNameProvider* _fromVariableNameProvider);
	~LinkObject();

//////////////////
// MAIN METHODS //
public: //////////

	// Connect 2 plug objects from 2 links
	static bool ConnectPlugs(FluxPlugObject* _fromObject, LinkObject* _targetLink, unsigned int _usingIndex);
	// static bool ConnectPlugs(FluxPlugReference* _fromReference, LinkObject* _targetLink, unsigned int _usingIndex);

	// Compile this link
	bool CompileLink(std::string* _compileString, LinkObject* _link, unsigned int _fromLinkInput = 0);

	// Return the input/output plugs
	Array<FluxPlugObject*>* GetInputPlugs();
	Array<FluxPlugObject*>* GetOutputPlugs();

	// Return a input/output variable by index
	FluxPlugObject* GetInputPlugByIndex(unsigned int _index);
	FluxPlugObject* GetOutputPlugByIndex(unsigned int _index);

private:

	// Set an input/output reference
	bool SetInputPlugReference(unsigned int _location, FluxPlugObject* _reference, std::string _variableName = "");
	bool SetOutputPlugReference(unsigned int _location, LinkObject* _fromLink, FluxPlugObject* _reference);

////////////
// LINKER //
public: ////

/////////////////////
// VIRTUAL METHODS //
protected: //////////

///////////////
// VARIABLES //
private: //////

	// The linked flux object Id and the object itself
	FluxObject* m_LinkedFluxObject;

	// References for the input/output plugs
	Array<FluxPlugObject*> m_InputPlugs;
	Array<FluxPlugObject*> m_OutputPlugs;

private:

};


/*
=> Um link tem:

- O nome/id do tipo de objeto ao qual faz referência
- Os links de entrada
- Os links de saída





*/