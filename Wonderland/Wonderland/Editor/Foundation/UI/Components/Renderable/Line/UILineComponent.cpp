////////////////////////////////////////////////////////////////////////////////
// Filename: UILineComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UILineComponent.h"
#include "UILineShader.h"

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\State\UIStateComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UILineComponent::UILineComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_LineColor = Vector4(0, 0, 0, 1);
	m_LineSize = 2;
}

UILineComponent::UILineComponent(const UILineComponent& other) : ECS_Component(other)
{
}

UILineComponent::~UILineComponent()
{
}

///////////////
// MODIFIERS //
///////////////

void UILineComponent::SetLineColor(Vector4 _color)
{
	m_LineColor = _color;
}

Vector4 UILineComponent::GetLineColor()
{
	return m_LineColor;
}

void UILineComponent::SetLineSize(unsigned int _size)
{
	m_LineSize = _size;
}

unsigned int UILineComponent::GetLineSize()
{
	return m_LineSize;
}

/////////////
// VIRTUAL //
/////////////

void UILineComponent::Update(unsigned int _updateId, float _timeElapsed)
{
	// Get the parent entity
	ECS_Entity* parentEntity = GetEntityOwner();

	// Get the state component from our entity owner
	UIStateComponent* stateComponent = parentEntity->FindComponent<UIStateComponent>();

	// Compare the update if with the render id
	if (stateComponent->GetRenderingID() == _updateId)
	{
		// Render this entity
		UILineShader::GetInstance()->AddObject(this);
	}
}

void UILineComponent::Clear()
{

}