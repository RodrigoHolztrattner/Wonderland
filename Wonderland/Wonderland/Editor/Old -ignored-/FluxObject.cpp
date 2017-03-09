////////////////////////////////////////////////////////////////////////////////
// Filename: FluxObject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxObject.h"

FluxObject::FluxObject()
{
    // Set the initial data
	// ...
}

FluxObject::~FluxObject()
{
}

FluxPlugReference* FluxObject::AddInputPlug(FluxPlugReference* _plug)
{
	// Add it
	m_InputPlugs.Add(_plug);

	return _plug;
}

FluxPlugReference* FluxObject::AddOutputPlug(FluxPlugReference* _plug)
{
	// Add it
	m_OutputPlugs.Add(_plug);

	return _plug;
}

bool FluxObject::ChangeInputPlugName(std::string _objectName, std::string _newName)
{
	// Find an object with the given name
	FluxPlugReference* functionPlug = FindPlugWithName(&m_InputPlugs, _objectName);
	if (functionPlug == nullptr)
	{
		return false;
	}

	// Change the name
	functionPlug->SetPlugName(_newName);

	// Event?
	// ...

	return true;
}

bool FluxObject::ChangeOutputPlugName(std::string _objectName, std::string _newName)
{
	// Find an object with the given name
	FluxPlugReference* functionPlug = FindPlugWithName(&m_OutputPlugs, _objectName);
	if (functionPlug == nullptr)
	{
		return false;
	}

	// Change the name
	functionPlug->SetPlugName(_newName);

	// Event?
	// ...

	return true;
}

unsigned int FluxObject::GetNumberInputPlugs()
{
	return m_InputPlugs.Size();
}

unsigned int FluxObject::GetNumberOutputPlugs()
{
	return m_OutputPlugs.Size();
}

FluxPlugReference* FluxObject::GetOutputPlug(unsigned int _id)
{
	return m_OutputPlugs[_id];
}

FluxPlugReference* FluxObject::GetInputPlug(unsigned int _id)
{
	return m_InputPlugs[_id];
}

FluxPlugReference* FluxObject::FindPlugWithName(Array<FluxPlugReference*>* _from, std::string _name)
{
	// Check if the from array is valid
	if (_from == nullptr)
	{
		return nullptr;
	}

	// For each object
	for (int i = 0; i < _from->Size(); i++)
	{
		// Get the object
		FluxPlugReference* currentObject = (*_from)[i];

		// Compare the names
		if (!currentObject->GetPlugName().compare(_name))
		{
			return (*_from)[i];
		}
	}

	// No object found!
	return nullptr;
}