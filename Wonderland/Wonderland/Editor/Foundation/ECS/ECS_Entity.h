////////////////////////////////////////////////////////////////////////////////
// Filename: ECS_Entity.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Container\Array\BinaryArray.h"

/////////////
// DEFINES //
/////////////

// We know the ECS_Component class
class ECS_Component;

/*
 *
 *
 *
 *
 *
 *
 *
 */

/*
//
template <typename ComponentType>
ComponentType* Component(ECS_Entity* _entity)
{
	return _entity->FindComponent<ComponentType>();
}
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: ECS_Entity
////////////////////////////////////////////////////////////////////////////////
class ECS_Entity
{
private:

public:
	ECS_Entity();
	ECS_Entity(const ECS_Entity&);
	~ECS_Entity();

	// Create this entity
	void Create();

	// Destroy this entity
	void Destroy();

	///////////////
	// COMPONENT //
	///////////////

	// Add a component
	void AddComponent(ECS_Component* _component);

	// Remove a component
	void RemoveComponent(ECS_Component* _component);

	// Find a component by ID
	ECS_Component* FindComponentByID(unsigned int _ID)
	{
		return m_ComponentArray[_ID];
	}

	// Find a component
	template <typename ComponentClass>
	ComponentClass* FindComponent()
	{
		return (ComponentClass*)m_ComponentArray[ComponentClass::ClassComponentID()];
	}

private:

	// The component array
	BinaryArray<ECS_Component*, unsigned int> m_ComponentArray;

	// If this entity is being destroyed
	bool m_IsbeingDestroyed;
};
