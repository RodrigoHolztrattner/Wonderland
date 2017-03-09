////////////////////////////////////////////////////////////////////////////////
// Filename: UITextureComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UITextureComponent.h"
#include "UITextureShader.h"

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\State\UIStateComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UITextureComponent::UITextureComponent()
{
	// Set the initial data
	m_Color = Vector4(0, 0, 0, 1);
}

UITextureComponent::UITextureComponent(const UITextureComponent& other)
{
}

UITextureComponent::~UITextureComponent()
{
}

///////////////
// MODIFIERS //
///////////////

void UITextureComponent::SetColor(Vector4 _color)
{
	m_Color = _color;
}

Vector4 UITextureComponent::GetColor()
{
	return m_Color;
}

/////////////
// VIRTUAL //
/////////////

void UITextureComponent::Update(unsigned int _updateId, float _timeElapsed)
{
	// Get the parent entity
	ECS_Entity* parentEntity = GetEntityOwner();

	// Get the state component from our entity owner
	UIStateComponent* stateComponent = parentEntity->FindComponent<UIStateComponent>();

	// Compare the update if with the render id
	if (stateComponent->GetRenderingID() == _updateId)
	{
		// Render this entity
		UITextureShader::GetInstance()->AddObject(this);
	}
}

void UITextureComponent::Clear()
{

}