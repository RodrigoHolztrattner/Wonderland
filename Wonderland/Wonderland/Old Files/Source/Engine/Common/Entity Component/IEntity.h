////////////////////////////////////////////////////////////////////////////////
// Filename: IEntity.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IEntity_H_
#define _IEntity_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Containers\Array\TBinaryArray.h"

/////////////
// DEFINES //
/////////////

// We know the IComponent class
class IComponent;

/*
 *
 *
 *
 *
 *
 *
 *
 */

////////////////////////////////////////////////////////////////////////////////
// Class name: IEntity
////////////////////////////////////////////////////////////////////////////////
class IEntity
{
private:

public:
	IEntity();
	IEntity(const IEntity&);
	~IEntity();

	// Create this entity
	void Create();

	// Destroy this entity
	void Destroy();

	///////////////
	// COMPONENT //
	///////////////

	// Add a component
	void AddComponent(IComponent* _component);

	// Remove a component
	void RemoveComponent(IComponent* _component);

	// Find a component by ID
	IComponent* FindComponentByID(unsigned int _ID);

private:

	// The component array
	TBinaryArray<IComponent*, unsigned int> m_ComponentArray;
};

#endif
