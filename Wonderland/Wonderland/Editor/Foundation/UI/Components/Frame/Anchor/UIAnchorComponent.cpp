////////////////////////////////////////////////////////////////////////////////
// Filename: UIAnchorComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIAnchorComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIAnchorComponent::UIAnchorComponent() : ECS_Component(ClassComponentID())
{
}

UIAnchorComponent::UIAnchorComponent(const UIAnchorComponent& other) : ECS_Component(other)
{
}

UIAnchorComponent::~UIAnchorComponent()
{
}

///////////////
// MODIFIERS //
///////////////

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\Frame\UIFrameComponent.h"
#include "..\..\Tree\UITreeComponent.h"

#include "..\..\..\..\Context\Context.h"

void UIAnchorComponent::AddAnchor(UIFrameComponent* targetFrame, Policy _policy, Modifier _modifier)
{
	AnchorController newAnchor;

	// Set the new anchor data
	newAnchor.targetFrame = targetFrame;
	newAnchor.policy = _policy;
	newAnchor.modifier = _modifier;
	newAnchor.targetFrameValue = Vector4(0, 0, 0, 0);

	// Add the new anchor to the array
	m_Controllers.Add(newAnchor);
}

void UIAnchorComponent::AddAnchor(Policy _policy, Modifier _modifier)
{
	AnchorController newAnchor;

	// Set the new anchor data
	newAnchor.targetFrame = nullptr;
	newAnchor.policy = _policy;
	newAnchor.modifier = _modifier;
	newAnchor.targetFrameValue = Vector4(0, 0, 0, 0);

	// Add the new anchor to the array
	m_Controllers.Add(newAnchor);
}

void UIAnchorComponent::ApplyController(AnchorController& _controller, Vector4& _currentFrame)
{
	// Get the controller frame component
	UIFrameComponent* frameComponent = GetControllerFrameComponent(_controller);
	if (frameComponent == nullptr)
	{
		// We probably are the root component
		return;
	}

	// Compare the frame values (check if we need to update)
	Vector4 frameValue = frameComponent->GetFrame();
	if (frameValue.Compare(_controller.targetFrameValue))
	{
		// No need to update
		return;
	}

	// Check the modifier
	switch (_controller.modifier)
	{
		// Move
		case Modifier::Move:
		{
			// Move to the anchor point
			MoveToAnchorPoint(_controller, _currentFrame, Vector4(frameComponent->GetFramePosition(), frameComponent->GetFrameSize()));

			break;
		}
		// Scale
		case Modifier::Scale:
		{
			// Scale to the anchor point
			ScaleToAnchorPoint(_controller, _currentFrame, Vector4(frameComponent->GetFramePosition(), frameComponent->GetFrameSize()));

			break;
		}
		// Pin
		case Modifier::Pin:
		{
			// Pin the frame component to the anchor point
			PinToAnchorPoint(_controller, _currentFrame, Vector4(frameComponent->GetFramePosition(), frameComponent->GetFrameSize()));

			break;
		}
		// Move pin
		case Modifier::MovePin:
		{
			// Move pin the frame component to the anchor point
			MovePinToAnchorPoint(_controller, _currentFrame, Vector4(frameComponent->GetFramePosition(), frameComponent->GetFrameSize()));

			break;
		}
	}

	// Save the new frame value
	_controller.targetFrameValue = frameComponent->GetFrame();;
}

UIFrameComponent* UIAnchorComponent::GetControllerFrameComponent(AnchorController _controller)
{
	// Check the controller type
	if (_controller.targetFrame == nullptr)
	{
		// Use parent frame //

		// Get the entity owner
		ECS_Entity* entity = GetEntityOwner();

		// Find the entity tree component
		UITreeComponent* treeComponent = entity->FindComponent<UITreeComponent>();

		// Get the entity parent tree component
		UITreeComponent* parentTreeComponent = treeComponent->GetParent();

		// Check if the parent is valid
		if (parentTreeComponent == nullptr)
		{
			// We are the root parent, we cant use an anchor
			return nullptr;
		}

		// Get the parent frame component
		return (UIFrameComponent*)parentTreeComponent->GetEntityComponentById(UIFrameComponent::ClassComponentID());
	}
	else
	{
		// Use target frame //
		
		// Get the target frame component
		return _controller.targetFrame;
	}

	// Will never happen
	return nullptr;
}

void UIAnchorComponent::MoveToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame)
{
	// Check the policy type
	switch (_controller.policy)
	{
		// Top
		case Policy::TopAlign:
		{
			// Set the frame
			_currentFrame.y = _targetFrame.y + _targetFrame.height;

			break;
		}
		// Right
		case Policy::RightAlign:
		{
			// Set the frame
			_currentFrame.x = _targetFrame.x - _currentFrame.width;

			break;
		}
		// Left
		case Policy::LeftAlign:
		{
			// Set the frame
			_currentFrame.x = _targetFrame.x + _targetFrame.width;

			break;
		}
		// Bottom
		case Policy::BottomAlign:
		{
			// Set the frame
			_currentFrame.y = _targetFrame.y - _currentFrame.height;

			break;
		}
	}
}

void UIAnchorComponent::ScaleToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame)
{
	// Check the policy type
	switch (_controller.policy)
	{
		// Top
		case Policy::TopAlign:
		{
			// Set the frame
			_currentFrame.height = (_currentFrame.y + _currentFrame.height) - (_targetFrame.y + _targetFrame.height);
			_currentFrame.y = _targetFrame.y + _targetFrame.height;

			break;
		}
		// Right
		case Policy::RightAlign:
		{
			// Set the frame
			_currentFrame.width = _targetFrame.x - _currentFrame.x;

			break;
		}
		// Left
		case Policy::LeftAlign:
		{
			// Set the frame
			_currentFrame.width = (_currentFrame.x + _currentFrame.width) - (_targetFrame.x + _targetFrame.width);
			_currentFrame.x = _targetFrame.x + _targetFrame.width;

			break;
		}
		// Bottom
		case Policy::BottomAlign:
		{
			// Set the frame
			_currentFrame.height = _targetFrame.y - _currentFrame.y;

			break;
		}
	}
}

void UIAnchorComponent::PinToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame)
{
	// Check the policy type
	switch (_controller.policy)
	{
		// Top
		case Policy::TopAlign:
		{
			// Set the frame
			_currentFrame.height = (_currentFrame.y + _currentFrame.height) - (_targetFrame.y);
			_currentFrame.y = _targetFrame.y;

			break;
		}
		// Right
		case Policy::RightAlign:
		{
			// Set the frame
			_currentFrame.width = (_targetFrame.x + _targetFrame.width) - _currentFrame.x;

			break;
		}
		// Left
		case Policy::LeftAlign:
		{
			// Set the frame
			_currentFrame.width = (_currentFrame.x + _currentFrame.width) - (_targetFrame.x);
			_currentFrame.x = _targetFrame.x;

			break;
		}
		// Bottom
		case Policy::BottomAlign:
		{
			// Set the frame
			_currentFrame.height = (_targetFrame.y + _targetFrame.height) - _currentFrame.y;

			break;
		}
	}
}

void UIAnchorComponent::MovePinToAnchorPoint(AnchorController _controller, Vector4& _currentFrame, Vector4 _targetFrame)
{
	// Check the policy type
	switch (_controller.policy)
	{
		// Top
		case Policy::TopAlign:
		{
			// Set the frame
			_currentFrame.y = _targetFrame.y;

			break;
		}
		// Right
		case Policy::RightAlign:
		{
			// Set the frame
			_currentFrame.width = (_targetFrame.x + _targetFrame.width) - _currentFrame.width;

			break;
		}
		// Left
		case Policy::LeftAlign:
		{
			// Set the frame
			_currentFrame.x = _targetFrame.x;

			break;
		}
		// Bottom
		case Policy::BottomAlign:
		{
			// Set the frame
			_currentFrame.height = (_targetFrame.y + _targetFrame.height) - _currentFrame.height;

			break;
		}
	}
}

/////////////
// VIRTUAL //
/////////////

void UIAnchorComponent::Update(unsigned int _updateId, float _timeElapsed)
{
	// Get the entity owner
	ECS_Entity* entity = GetEntityOwner();

	// Get the current frame
	UIFrameComponent* frameComponent = entity->FindComponent<UIFrameComponent>();

	// Get the frame object
	Vector4 currentFrame = Vector4(frameComponent->GetFramePosition(), frameComponent->GetFrameSize());

	// For each controller
	for (int i = 0; i < m_Controllers.Size(); i++)
	{
		// Apply this controller
		ApplyController(m_Controllers[i], currentFrame);
	}
	
	// Set the new frame
	frameComponent->SetFrame(Vector2(currentFrame.x, currentFrame.y), Vector2(currentFrame.width, currentFrame.height));
}

void UIAnchorComponent::Clear()
{
	// Zero the controll array
	m_Controllers.Zero();
}
