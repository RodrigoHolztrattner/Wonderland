////////////////////////////////////////////////////////////////////////////////
// Filename: UITreeComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\ECS\ECS_Component.h"
#include "..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\Support\Container\Array\Array.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

/** UIStateComponent */
class UIStateComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: UITreeComponent
////////////////////////////////////////////////////////////////////////////////
class UITreeComponent : public ECS_Component
{

//////////////////
// CONSTRUCTORS //
public: //////////

	UITreeComponent();
	UITreeComponent(const UITreeComponent&);
	~UITreeComponent();

    // Add a unique ID to this component class
    AddComponentUniqueID(UITreeComponent);

	// Register the class dependencies
	RegisterClassDependencies(UIStateComponent);

///////////////
// MODIFIERS //
public: ///////

	// Set the parent
	void SetParent(UITreeComponent* _parent);

	// Return the parent
	UITreeComponent* GetParent();

	// Add a child
	void AddChild(UITreeComponent* _child);

	// Return the child array size
	unsigned int GetChildArraySize();

	// Return a child by index
	UITreeComponent* GetChildByIndex(unsigned int _index);

	// Set child position to top
	void MoveToTop();

protected:

	// Unregister a child
	void RemoveChild(UITreeComponent* _child);

private:

	// Move a child to position (array)
	void MoveChild(unsigned int _from, unsigned int _to);

/////////////
// VIRTUAL //
public: /////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed);

	// The clear method
	virtual void Clear();

//////////////
// CALLBACK //
private: /////

///////////////
// VARIABLES //
private: //////

	// The parent itself
	UITreeComponent* m_Parent;

	// The child array
	Array<UITreeComponent*> m_ChildArray;
};