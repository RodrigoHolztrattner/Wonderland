////////////////////////////////////////////////////////////////////////////////
// Filename: UIColorComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIColorComponent.h"
#include "UIColorShader.h"

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\State\UIStateComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIColorComponent::UIColorComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_Color = Vector4(0, 0, 0, 1);
}

UIColorComponent::UIColorComponent(const UIColorComponent& other) : ECS_Component(other)
{
}

UIColorComponent::~UIColorComponent()
{
}

///////////////
// MODIFIERS //
///////////////

void UIColorComponent::SetColor(Vector4 _color)
{
	m_Color = _color;
}

Vector4 UIColorComponent::GetColor()
{
	return m_Color;
}

/////////////
// VIRTUAL //
/////////////

void UIColorComponent::Update(unsigned int _updateId, float _timeElapsed)
{
	// Get the parent entity
	ECS_Entity* parentEntity = GetEntityOwner();

	// Get the state component from our entity owner
	UIStateComponent* stateComponent = parentEntity->FindComponent<UIStateComponent>();

	// Compare the update if with the render id
	if (stateComponent->GetRenderingID() == _updateId)
	{
		// Render this entity
		UIColorShader::GetInstance()->AddObject(this);
	}
}

void UIColorComponent::Clear()
{

}