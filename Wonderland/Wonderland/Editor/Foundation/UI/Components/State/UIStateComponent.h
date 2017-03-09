////////////////////////////////////////////////////////////////////////////////
// Filename: UIStateComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\ECS\ECS_Component.h"
#include "..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\Support\Container\Array\StaticArray.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UIStateComponent
////////////////////////////////////////////////////////////////////////////////
class UIStateComponent : public ECS_Component
{

//////////////////
// CONSTRUCTORS //
public: //////////

	UIStateComponent();
	UIStateComponent(const UIStateComponent&);
	~UIStateComponent();

private:
 
    // Add a unique ID to this component class
    AddComponentUniqueID(UIStateComponent);
 
///////////////
// MODIFIERS //
public: ///////

	// Set condition
	void SetIsVisible(bool _state);
	void SetIsRenderable(bool _state);
	void SetCanReceiveCommands(bool _state);
	void SetIsAlwaysOnTop(bool _state);

	// Return condition
	bool IsVisible();
	bool IsRenderable();
	bool CanReceiveCommands();
	bool IsAlwaysOnTop();

	// Set/get the rendering id
	void SetRenderingID(unsigned int _id) { m_RenderingId = _id; }
	unsigned int GetRenderingID() { return m_RenderingId; }

	// Set/get the depth order
	void SetDepthOrder(float _depthOrder) { m_DepthOrder = _depthOrder; }
	float GetDepthOrder() { return -m_DepthOrder; }

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

	// If the entity is visible
	bool m_IsVisible;

	// If the entity is renderable
	bool m_IsRenderable;

	// If the entity can receive input commands
	bool m_CanReceiveCommands;

	// If we can change position inside the view array
	bool m_IsAlwaysOnTop;

	// The rendering id
	unsigned int m_RenderingId;

	// The depth order
	float m_DepthOrder;
};