////////////////////////////////////////////////////////////////////////////////
// Filename: UIAnchorComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\ECS\ECS_Component.h"
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"

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

/** UITreeComponent */
class UIFrameComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIAnchorComponent
////////////////////////////////////////////////////////////////////////////////
class UIAnchorComponent : public ECS_Component
{
////////////
// POLICY //
public: ////

	// The policy type
	enum class Policy
	{
		TopAlign,
		RightAlign,
		BottomAlign,
		LeftAlign
	};

	// The modifier type
	enum class Modifier
	{
		Move,
		Scale,
		Pin,
		MovePin
	};

	// The acnhor controller type
	struct AnchorController
	{
		// Target frame component (may be null)
		// If the target is not null, we must ensure that if it will be deleted, we both should be deleted!
		UIFrameComponent* targetFrame;

		// The policy used
		Policy policy;

		// The modifier
		Modifier modifier;

		// The target frame value (used to check if we should update)
		Vector4 targetFrameValue;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	UIAnchorComponent();
	UIAnchorComponent(const UIAnchorComponent&);
	~UIAnchorComponent();

private:
 
    // Add a unique ID to this component class
    AddComponentUniqueID(UIAnchorComponent);
 
    // Register the class dependencies
    RegisterClassDependencies(UITreeComponent, UIFrameComponent);

///////////////
// MODIFIERS //
public: ///////

	// Add an anchor
	void AddAnchor(UIFrameComponent* targetFrame, Policy _policy, Modifier _modifier);
	void AddAnchor(Policy _policy, Modifier _modifier);

private:

	// Apply controller
	void ApplyController(AnchorController& _controller, Vector4& _currentFrame);

	// Return the controller frame component
	UIFrameComponent* GetControllerFrameComponent(AnchorController _controller);

	// Move the frame component to the anchor point
	void MoveToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame);

	// Scale the frame component to the anchor point
	void ScaleToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame);

	// Pin the frame component to the anchor point
	void PinToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame);

	// Move pin the frame component to the anchor point
	void MovePinToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame);

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
protected: ////

	// The controllers
	Array<AnchorController> m_Controllers;
};