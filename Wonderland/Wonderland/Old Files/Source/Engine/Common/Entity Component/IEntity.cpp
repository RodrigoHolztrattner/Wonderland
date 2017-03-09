///////////////////////////////////////////////////////////////////////////////
// Filename: IEntity.cpp
///////////////////////////////////////////////////////////////////////////////
#include "IEntity.h"
#include "IComponent.h"

IEntity::IEntity()
{
	// Set the initial data
	// ...
}

IEntity::IEntity(const IEntity& other)
{
}

IEntity::~IEntity()
{
}

void IEntity::Create()
{

}

void IEntity::Destroy()
{
	// Destroy all components
	for (int i = 0; i < m_ComponentArray.Size(); i++)
	{
		// Delete it
		delete m_ComponentArray.GetObject(i);
	}

	// Erase the array
	m_ComponentArray.Zero();
}

void IEntity::AddComponent(IComponent* _component)
{
	// Add the component
	m_ComponentArray.Add(_component, _component->GetComponentID());
	
	// Register the owner
	_component->RegisterEntityOwner(this);
}

void IEntity::RemoveComponent(IComponent* _component)
{
	// TO-BE IMPLEMENTED
}

IComponent* IEntity::FindComponentByID(unsigned int _ID)
{
	return m_ComponentArray[_ID];
}