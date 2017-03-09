////////////////////////////////////////////////////////////////////////////////
// Filename: UIStateComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIStateComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIStateComponent::UIStateComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_IsVisible = true;
	m_IsRenderable = true;
	m_CanReceiveCommands = true;
	m_IsAlwaysOnTop = false;
	m_RenderingId = -1;
}

UIStateComponent::UIStateComponent(const UIStateComponent& other) : ECS_Component(other)
{
}

UIStateComponent::~UIStateComponent()
{
}

///////////////
// MODIFIERS //
///////////////

void UIStateComponent::SetIsVisible(bool _state)
{
	m_IsVisible = _state;
}

void UIStateComponent::SetIsRenderable(bool _state)
{
	m_IsRenderable = _state;
}

void UIStateComponent::SetCanReceiveCommands(bool _state)
{
	m_CanReceiveCommands = _state;
}

void UIStateComponent::SetIsAlwaysOnTop(bool _state)
{
	m_IsAlwaysOnTop = _state;
}

bool UIStateComponent::IsVisible()
{
	return m_IsVisible;
}

bool UIStateComponent::IsRenderable()
{
	return m_IsRenderable;
}

bool UIStateComponent::CanReceiveCommands()
{
	return m_CanReceiveCommands;
}

bool UIStateComponent::IsAlwaysOnTop()
{
	return m_IsAlwaysOnTop;
}

/////////////
// VIRTUAL //
/////////////

void UIStateComponent::Update(unsigned int _updateId, float _timeElapsed)
{

}

void UIStateComponent::Clear()
{

}