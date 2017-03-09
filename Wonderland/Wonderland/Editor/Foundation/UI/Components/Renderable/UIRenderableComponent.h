////////////////////////////////////////////////////////////////////////////////
// Filename: UIRenderableComponent.h
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

/** UITreeComponent */
class UITreeComponent;

/** UIFrameComponent */
class UIFrameComponent;

/** UIFrameComponent */
class UIStateComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIRenderableComponent
////////////////////////////////////////////////////////////////////////////////
class UIRenderableComponent : public ECS_Component
{

//////////////////
// CONSTRUCTORS //
public: //////////

	UIRenderableComponent();
	UIRenderableComponent(const UIRenderableComponent&);
	~UIRenderableComponent();

private:
 
    // Add a unique ID to this component class
    AddComponentUniqueID(UIRenderableComponent);
 
    // Register the class dependencies
    RegisterClassDependencies(UITreeComponent, UIFrameComponent, UIStateComponent);

///////////////
// MODIFIERS //
public: ///////

	// Render function
	void Render();

	// Return the render order for this component
	unsigned int GetRenderOrder() { return m_RenderOrder; }

private:

	// Render aux
	void RenderAux(unsigned int _renderOrder);

/////////////
// VIRTUAL //
public: /////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed);

	// The clear method
	virtual void Clear();

	// The set shader method
	virtual void SetShader() = 0;

//////////////
// CALLBACK //
private: /////


///////////////
// VARIABLES //
private: //////

	// The render order for this renderable
	unsigned int m_RenderOrder;
};