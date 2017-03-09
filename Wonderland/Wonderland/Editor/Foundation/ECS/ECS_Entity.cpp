///////////////////////////////////////////////////////////////////////////////
// Filename: ECS_Entity.cpp
///////////////////////////////////////////////////////////////////////////////
#include "ECS_Entity.h"
#include "ECS_Component.h"

ECS_Entity::ECS_Entity()
{
	// Set the initial data
	m_IsbeingDestroyed = false;
}

ECS_Entity::ECS_Entity(const ECS_Entity& other)
{
}

ECS_Entity::~ECS_Entity()
{
}

void ECS_Entity::Create()
{

}

void ECS_Entity::Destroy()
{
	/*
	// Check if this entity is already being destroyed
	if (m_IsbeingDestroyed)
	{
		return;
	}
	*/

	// Set that we are destroying this entity
	m_IsbeingDestroyed = true;

	// Destroy all components
	for (int i = 0; i < m_ComponentArray.Size(); i++)
	{
		// Clear the object
		m_ComponentArray.GetObject(i)->Clear();

		// Delete it
		m_ComponentArray.GetObject(i)->Invalidate();
		// delete m_ComponentArray.GetObject(i);
	}

	// Erase the array
	m_ComponentArray.Zero();
}

void ECS_Entity::AddComponent(ECS_Component* _component)
{
	// Add the component
	m_ComponentArray.Add(_component, _component->GetComponentID());
	
	// Register the owner
	_component->RegisterEntityOwner(this);
}

void ECS_Entity::RemoveComponent(ECS_Component* _component)
{
	// TO-BE IMPLEMENTED
}