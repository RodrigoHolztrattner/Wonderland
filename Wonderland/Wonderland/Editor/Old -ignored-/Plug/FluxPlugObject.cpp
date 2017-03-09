////////////////////////////////////////////////////////////////////////////////
// Filename: FluxPlugObject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxPlugObject.h"
#include "..\LinkObject.h"

FluxPlugObject::FluxPlugObject(std::string _socketName)
{
	// Set the initial data
	CreateUndefinedObject(_socketName);
}

FluxPlugObject::FluxPlugObject(PlugType _type, std::string _plugName)
{
	// Set the data
	// ...
}

FluxPlugObject::FluxPlugObject()
{
	// Set the initial data
	SetPlugType(PlugType::Undefined);
}

FluxPlugObject::FluxPlugObject(const FluxPlugObject& _other)
{
	// Check the type
	if (GetPlugType() == PlugType::ExecLink)
	{
		m_ExecLink = _other.m_ExecLink;
	}
	else if (GetPlugType() == PlugType::Variable)
	{
		m_Variable = _other.m_Variable;
	}
}

FluxPlugObject* FluxPlugObject::CreateFromReference(FluxPlugReference* _reference, bool _useCustomName, std::string _customName)
{
	// Set the use name
	std::string useName = (_useCustomName ? _customName : _reference->GetPlugName());

	// Exec type
	if (_reference->GetPlugType() == PlugType::ExecLink)
	{
		return CreateExecLinkObject(nullptr, useName);
	}
	// Variable type
	else if (_reference->GetPlugType() == PlugType::Variable)
	{
		return CreateVariableObject(FluxVariable::Create(_reference->GetVariableType(), useName), useName);
	}

	return nullptr;
}

FluxPlugObject::~FluxPlugObject()
{
}

FluxPlugObject* FluxPlugObject::CreateUndefinedObject(std::string _socketName)
{
	// Create the socket object
	FluxPlugObject* newSocket = new FluxPlugObject();

	// Set the data
	newSocket->SetPlugType(PlugType::Undefined);
	newSocket->SetPlugName(_socketName);

	return newSocket;
}

FluxPlugObject* FluxPlugObject::CreateExecLinkObject(LinkObject* _link, std::string _socketName)
{
	// Create the socket object
	FluxPlugObject* newSocket = new FluxPlugObject();

	// Set the data
	newSocket->SetPlugType(PlugType::ExecLink);
	newSocket->SetPlugName(_socketName);
	newSocket->SetExecLinkData(_link);

	return newSocket;
}

FluxPlugObject* FluxPlugObject::CreateVariableObject(FluxVariable* _variable, std::string _socketName)
{
	// Create the socket object
	FluxPlugObject* newSocket = new FluxPlugObject();

	// Set the data
	newSocket->SetPlugType(PlugType::Variable);
	newSocket->SetPlugName(_socketName);
	newSocket->SetVariableData(_variable);

	return newSocket;
}

void FluxPlugObject::SetVariableData(FluxVariable* _variableData)
{
	// Check the type
	if (!IsFromType(PlugType::Variable))
	{
		return;
	}

	// Set the variable
	m_Variable.variable = _variableData;
}

void FluxPlugObject::SetExecLinkData(LinkObject* _link)
{
	// Check the type
	if (!IsFromType(PlugType::ExecLink))
	{
		return;
	}

	// Set the link
	m_ExecLink.link = _link;
}

LinkObject* FluxPlugObject::GetExecLink()
{
	// Check the type
	if (!IsFromType(PlugType::ExecLink))
	{
		return nullptr;
	}

	// Return the link
	return m_ExecLink.link;
}

FluxVariable* FluxPlugObject::GetVariableData()
{
	// Check the type
	if (!IsFromType(PlugType::Variable))
	{
		return nullptr;
	}

	// Return the data
	return m_Variable.variable;
}