////////////////////////////////////////////////////////////////////////////////
// Filename: UIRelativeFrameComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIRelativeFrameComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIRelativeFrameComponent::UIRelativeFrameComponent()
{
	// Set the initial data
	m_TopLeftRelative = Vector2(0, 0);
	m_BottomRightRelative = Vector2(0, 0);
}

UIRelativeFrameComponent::UIRelativeFrameComponent(const UIRelativeFrameComponent& other)
{
}

UIRelativeFrameComponent::~UIRelativeFrameComponent()
{
}

///////////////
// MODIFIERS //
///////////////

#include "..\..\..\ECS\ECS_Entity.h"
#include "..\Tree\UITreeComponent.h"

void UIRelativeFrameComponent::SetFrame(Vector2 _position, Vector2 _size, int _restriction)
{
	// Save the restriction
	m_Restriction = _restriction;

	// Set the data
	m_TopLeftRelative = _position;
	m_BottomRightRelative = Vector2(_position.x + _size.x, _position.y + _size.y);

	// Get the parent entity
	ECS_Entity* parent = GetEntityOwner();

	// Get the UITreeComponent
	UITreeComponent* treeComponent = parent->FindComponent<UITreeComponent>();

	// Check if this entity has a parent (if we are using the relative frame, it must have)
	UITreeComponent* parentTreeComponent = treeComponent->GetParent();
	if (parentTreeComponent == nullptr)
	{
		// Ok, problem, return
		return;
	}

	// Get the parent frame data
	UIFrameComponent* parentFrameComponent = (UIFrameComponent*)parentTreeComponent->GetEntityComponentById(UIFrameComponent::ClassComponentID());

	// Set the frame variables
	Vector2 topLeft;
	Vector2 bottomRight;
	topLeft.x = parentFrameComponent->GetFramePosition().x + m_TopLeftRelative.x * parentFrameComponent->GetFrameSize().width;
	topLeft.y = parentFrameComponent->GetFramePosition().y + m_TopLeftRelative.y * parentFrameComponent->GetFrameSize().height;
	bottomRight.x = parentFrameComponent->GetFramePosition().x + m_BottomRightRelative.x * parentFrameComponent->GetFrameSize().width - topLeft.x;
	bottomRight.y = parentFrameComponent->GetFramePosition().y + m_BottomRightRelative.y * parentFrameComponent->GetFrameSize().height - topLeft.y;

	// Flag X check
	if ((int)m_Restriction & (int)Restriction::X)
	{
		// Set the value
		topLeft.x = _position.x;
	}

	// Flag Y check
	if ((int)m_Restriction & (int)Restriction::Y)
	{
		// Set the value
		topLeft.y = _position.y;
	}

	// Flag Width check
	if ((int)m_Restriction & (int)Restriction::Width)
	{
		// Set the value
		bottomRight.width = _size.width;
	}

	// Flag Height check
	if ((int)m_Restriction & (int)Restriction::Height)
	{
		// Set the value
		bottomRight.height = _size.height;
	}

	// Update the base class variables
	UIFrameComponent::SetFrame(topLeft, bottomRight);
}

/*
Vector2 UIRelativeFrameComponent::GetFramePosition()
{
	return m_TopLeftRelative;
}

Vector2 UIRelativeFrameComponent::GetFrameSize()
{
	return Vector2(m_BottomRightRelative.x - m_TopLeftRelative.x, m_BottomRightRelative.y - m_TopLeftRelative.y);
}

Vector2 UIRelativeFrameComponent::GetFrameEndPosition()
{
	return m_BottomRightRelative;
}
*/

/////////////
// VIRTUAL //
/////////////

void UIRelativeFrameComponent::Update(unsigned int _updateId, float _timeElapsed)
{

}

void UIRelativeFrameComponent::Clear()
{

}

void UIRelativeFrameComponent::ParentChagedFrame()
{
	// Call the set frame with the internal values
	UIRelativeFrameComponent::SetFrame(m_TopLeftRelative, Vector2(m_BottomRightRelative.x - m_TopLeftRelative.x, m_BottomRightRelative.y - m_TopLeftRelative.y), m_Restriction);
}