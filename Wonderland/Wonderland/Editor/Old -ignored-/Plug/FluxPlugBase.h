////////////////////////////////////////////////////////////////////////////////
// Filename: FluxPlugBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include "..\Variable\FluxVariable.h"

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
// Class name: FluxPlugBase
////////////////////////////////////////////////////////////////////////////////
class FluxPlugBase
{
/////////////
// DEFINES //
public: /////

	// The exec link type
	struct ExecLinkPlug
	{
		// The link object (where to continue the execution)
		LinkObject* link;
	};

	// The variable plug type
	struct VariablePlug
	{
		// The variable itself
		FluxVariable* variable;
	};

	// The type of plug
	enum class PlugType
	{
		Undefined,
		ExecLink,
		Variable
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxPlugBase();
	FluxPlugBase(const FluxPlugBase& _other);
	~FluxPlugBase();

//////////////////
// MAIN METHODS //
public: //////////

	// Set the plug name
	void SetPlugName(std::string _name);

	// Get the plug name
	std::string GetPlugName();

	// Set the plug type
	void SetPlugType(PlugType _type);

	// Return the plug type
	PlugType GetPlugType();

	// Compare 2 variables (type)
	bool IsFromType(PlugType _type);

///////////////
// VARIABLES //
private: //////

	// The plug type
	PlugType m_PlugType;

	// The plug name
	std::string m_PlugName;
};
