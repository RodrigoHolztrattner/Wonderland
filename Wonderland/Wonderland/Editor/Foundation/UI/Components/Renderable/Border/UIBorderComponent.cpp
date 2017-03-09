////////////////////////////////////////////////////////////////////////////////
// Filename: UIBorderComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIBorderComponent.h"
#include "UIBorderShader.h"

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\State\UIStateComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIBorderComponent::UIBorderComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_BorderColor = Vector4(0, 0, 0, 0);
	m_BorderSize = 2;
}

UIBorderComponent::UIBorderComponent(const UIBorderComponent& other) : ECS_Component(other)
{
}

UIBorderComponent::~UIBorderComponent()
{
}

///////////////
// MODIFIERS //
///////////////

#include <iostream>

void UIBorderComponent::SetBorderColor(Vector4 _color)
{
	m_BorderColor = _color;;
}

Vector4 UIBorderComponent::GetBorderColor()
{
	return m_BorderColor;
}

void UIBorderComponent::SetBorderSize(unsigned int _size)
{
	m_BorderSize = _size;
}

unsigned int UIBorderComponent::GetBorderSize()
{
	return m_BorderSize;
}

/////////////
// VIRTUAL //
/////////////

void UIBorderComponent::Update(unsigned int _updateId, float _timeElapsed)
{
	// Get the parent entity
	ECS_Entity* parentEntity = GetEntityOwner();

	// Get the state component from our entity owner
	UIStateComponent* stateComponent = parentEntity->FindComponent<UIStateComponent>();

	// Compare the update if with the render id
	if (stateComponent->GetRenderingID() == _updateId)
	{
		// Render this entity
		UIBorderShader::GetInstance()->AddObject(this);
	}
}

void UIBorderComponent::Clear()
{

}