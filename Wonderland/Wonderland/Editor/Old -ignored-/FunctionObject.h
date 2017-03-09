////////////////////////////////////////////////////////////////////////////////
// Filename: FunctionObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "FluxObject.h"
#include <string>
#include "..\..\Support\Container\Array\Array.h"
#include "VariableObject.h"


///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////
#include "Type\FluxType.h"

////////////
// GLOBAL //
////////////

/*

	=> Cada objeto de calsse aqui deve ser simples:

		- Ter as entradas e saidas
		- Ter um nome
		- Ter um simbolo
		- Permitir fazer edições à esses dados

	=> Existem classes que gerenciam o corpo da função e outra que replica dados daqui para construir um link.

		- À ser definido...
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FunctionObject
////////////////////////////////////////////////////////////////////////////////
class FunctionObject : public FluxObject
{
/////////////
// DEFINES //
public: /////

	// 
	friend LinkObject;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FunctionObject();
	~FunctionObject();

//////////////////
// MAIN METHODS //
public: //////////

	// Create/Initialize this object
	bool Create(std::string _functionName);

	// Compile the function header
	bool CompileHeader(std::string* _compileString);

	// Compile the function source
	bool CompileSource(std::string* _compileString);

	// Compile this object
	virtual bool CompileLink(std::string* _compileString, LinkObject* _link, unsigned int _fromLinkInput = 0);

////////////
// LINKER //
public: ////

/////////////////////
// VIRTUAL METHODS //
protected: //////////

///////////////
// VARIABLES //
private: //////

	// The function name
	std::string m_FunctionName;
};
