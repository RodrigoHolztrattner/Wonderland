////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrameComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIFrameComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIFrameComponent::UIFrameComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_TopLeft = Vector2(0, 0);
	m_BottomRight = Vector2(0, 0);
}

UIFrameComponent::UIFrameComponent(const UIFrameComponent& other) : ECS_Component(other)
{
}

UIFrameComponent::~UIFrameComponent()
{
}

///////////////
// MODIFIERS //
///////////////

#include "..\..\..\ECS\ECS_Entity.h"
#include "..\Tree\UITreeComponent.h"

void UIFrameComponent::SetFrame(Vector2 _position, Vector2 _size)
{
	// Set the data
	m_TopLeft = _position;
	m_BottomRight = Vector2(_position.x + _size.x, _position.y + _size.y);

	// Get the parent entity
	ECS_Entity* parent = GetEntityOwner();

	// Get the UITreeComponent
	UITreeComponent* treeComponent = parent->FindComponent<UITreeComponent>();

	// For each child
	for (int i = 0; i < treeComponent->GetChildArraySize(); i++)
	{
		// Get the child tree component
		UITreeComponent* childTreeComponent = treeComponent->GetChildByIndex(i);

		// Get the child frame component
		UIFrameComponent* childFrameComponent = (UIFrameComponent*)childTreeComponent->GetEntityComponentById(UIFrameComponent::ClassComponentID());

		// Call the ParentChangedFrame() for this child
		childFrameComponent->ParentChagedFrame();
	}

	// Update the token id
	m_FrameToken.Increment();
}

Vector4 UIFrameComponent::GetFrame()
{
	return Vector4(GetFramePosition(), GetFrameSize());
}

Vector2 UIFrameComponent::GetFramePosition()
{
	return m_TopLeft;
}

Vector2 UIFrameComponent::GetFrameSize()
{
	return Vector2(m_BottomRight.x - m_TopLeft.x, m_BottomRight.y - m_TopLeft.y);
}

Vector2 UIFrameComponent::GetFrameEndPosition()
{
	return m_BottomRight;
}

bool UIFrameComponent::PointIsInsideFrame(Vector2 _point)
{
	// Rectangle bound check
	if (_point.x < m_TopLeft.x || _point.y < m_TopLeft.y || _point.x > m_BottomRight.x || _point.y > m_BottomRight.y)
	{
		return false;
	}

	return true;
}

#include "..\..\..\Context\Context.h"

Vector4 UIFrameComponent::GetScreenFrame()
{
	Vector4 screenFrame;
	screenFrame.x = m_TopLeft.x / Context::GetInstance()->GetScreenWidth();
	screenFrame.y = m_TopLeft.y / Context::GetInstance()->GetScreenHeight();
	screenFrame.width = (m_BottomRight.x - m_TopLeft.x) / Context::GetInstance()->GetScreenWidth();
	screenFrame.height = (m_BottomRight.y - m_TopLeft.y) / Context::GetInstance()->GetScreenHeight();
	
	return screenFrame;
}

UIFrameToken UIFrameComponent::GetFrameToken()
{
	return m_FrameToken;
}

/////////////
// VIRTUAL //
/////////////

void UIFrameComponent::Update(unsigned int _updateId, float _timeElapsed)
{

}

void UIFrameComponent::Clear()
{

}

void UIFrameComponent::ParentChagedFrame()
{
	// Do nothing
	// ...
}