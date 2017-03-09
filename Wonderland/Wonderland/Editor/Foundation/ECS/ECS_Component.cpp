///////////////////////////////////////////////////////////////////////////////
// Filename: ECS_Component.cpp
///////////////////////////////////////////////////////////////////////////////
#include "ECS_Component.h"

ECS_Component::ECS_Component(unsigned int _componentID)
{
	// Set the initial data
	m_ComponentID = _componentID;
	m_Invalidated = false;
}

ECS_Component::ECS_Component(const ECS_Component& other)
{
}

ECS_Component::~ECS_Component()
{
}

#include "ECS_Entity.h"

ECS_Component* ECS_Component::GetEntityComponentById(unsigned int _id)
{
	return GetEntityOwner()->FindComponentByID(_id);
}