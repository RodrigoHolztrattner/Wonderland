////////////////////////////////////////////////////////////////////////////////
// Filename: ClassRegister.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ClassRegister.h"
#include "..\Type\Type.h"

Flux::ClassRegister::ClassRegister()
{
}

Flux::ClassRegister::~ClassRegister()
{
}

bool Flux::ClassRegister::RegisterClass(Flux::Class* _newClass)
{
	// Check if a class with the same name already exists
	if (ClassWithNameExists(_newClass->GetClassName()))
	{
		return false;
	}

	// Add the new class into the registered array
	m_RegisteredClasses.push_back(_newClass);
}

Flux::Class* Flux::ClassRegister::GetClass(std::string _name)
{
	return FindClassByName(_name);
}

Flux::Class* Flux::ClassRegister::GetClass(Flux::Handle _classHandle)
{
	return FindClassByHandle(_classHandle);
}

bool Flux::ClassRegister::ClassWithNameExists(std::string _className)
{
	return FindClassByName(_className) != nullptr;
}

Flux::Class* Flux::ClassRegister::FindClassByName(std::string _name)
{
	// For each registered class
	for (auto classObject : m_RegisteredClasses)
	{
		// Compare the names
		if (!_name.compare(classObject->GetClassName()))
		{
			return classObject;
		}
	}

	return nullptr;
}

Flux::Class* Flux::ClassRegister::FindClassByHandle(Flux::Handle _handle)
{
	// For each registered class
	for (auto classObject : m_RegisteredClasses)
	{
		// Compare the names
		if (classObject->CompareHandle(_handle))
		{
			return classObject;
		}
	}

	return nullptr;
}