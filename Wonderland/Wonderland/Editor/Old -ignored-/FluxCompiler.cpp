////////////////////////////////////////////////////////////////////////////////
// Filename: FluxCompiler.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxCompiler.h"

FluxCompiler::FluxCompiler()
{
    // Set the initial data
	// ...
}

FluxCompiler::~FluxCompiler()
{
}

FluxPlugReference* FluxCompiler::AddInputPlug(FluxPlugReference* _plug)
{
	// Add it
	m_InputPlugs.Add(_plug);

	return _plug;
}

FluxPlugReference* FluxCompiler::AddOutputPlug(FluxPlugReference* _plug)
{
	// Add it
	m_OutputPlugs.Add(_plug);

	return _plug;
}

bool FluxCompiler::ChangeInputPlugName(std::string _objectName, std::string _newName)
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

bool FluxCompiler::ChangeOutputPlugName(std::string _objectName, std::string _newName)
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

unsigned int FluxCompiler::GetNumberInputPlugs()
{
	return m_InputPlugs.Size();
}

unsigned int FluxCompiler::GetNumberOutputPlugs()
{
	return m_OutputPlugs.Size();
}

FluxPlugReference* FluxCompiler::GetOutputPlug(unsigned int _id)
{
	return m_OutputPlugs[_id];
}

FluxPlugReference* FluxCompiler::GetInputPlug(unsigned int _id)
{
	return m_InputPlugs[_id];
}

FluxPlugReference* FluxCompiler::FindPlugWithName(Array<FluxPlugReference*>* _from, std::string _name)
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