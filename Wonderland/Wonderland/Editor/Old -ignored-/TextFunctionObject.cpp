////////////////////////////////////////////////////////////////////////////////
// Filename: TextFunctionObject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextFunctionObject.h"

TextFunctionObject::TextFunctionObject()
{
    // Set the initial data
	// ...
}

TextFunctionObject::~TextFunctionObject()
{
}

bool TextFunctionObject::Create(std::string _functionName, std::string _functionBody)
{
	// Set the data
	m_FunctionName = _functionName;
	m_FunctionBody = _functionBody;

    return true;
}

bool TextFunctionObject::Compile(std::string* _compileString, LinkObject* _link, unsigned int _fromLinkInput)
{
	return true;
}