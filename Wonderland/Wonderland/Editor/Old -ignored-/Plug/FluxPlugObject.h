////////////////////////////////////////////////////////////////////////////////
// Filename: FluxPlugObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include "FluxPlugBase.h"
#include "FluxPlugReference.h"
#include "..\VariableObject.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

// 
class LinkObject;

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxPlugObject
////////////////////////////////////////////////////////////////////////////////
class FluxPlugObject : public FluxPlugBase
{
/////////////
// DEFINES //
public: /////

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxPlugObject(std::string _socketName);
	FluxPlugObject(PlugType _type, std::string _plugName);
	FluxPlugObject();
	FluxPlugObject(const FluxPlugObject& _other);
	~FluxPlugObject();

//////////////////
// MAIN METHODS //
public: //////////

	// Create/Initialize this object
	static FluxPlugObject* CreateUndefinedObject(std::string _socketName = "");
	static FluxPlugObject* CreateExecLinkObject(LinkObject* _link, std::string _socketName = "");
	static FluxPlugObject* CreateVariableObject(FluxVariable* _variable, std::string _socketName = "");
	static FluxPlugObject* CreateFromReference(FluxPlugReference* _reference, bool _useCustomName = false, std::string _customName = "");

	// Set the variable data
	void SetVariableData(FluxVariable* _variableData);

	// Return the variable data (null if the type != from Varaible)
	FluxVariable* GetVariableData();

	// Set the exec link data
	void SetExecLinkData(LinkObject* _link);

	// Return the exec link (null if the type != from ExecType)
	LinkObject* GetExecLink();

///////////////
// VARIABLES //
private: //////

	// Our internal type object
	union /////////////////////
	{
		// The exec link type
		ExecLinkPlug m_ExecLink;

		// The variable type
		VariablePlug m_Variable;
	}; ////////////////////////
};
