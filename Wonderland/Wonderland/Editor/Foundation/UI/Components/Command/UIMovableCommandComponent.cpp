////////////////////////////////////////////////////////////////////////////////
// Filename: UIMovableCommandComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIMovableCommandComponent.h"

#include "..\..\..\ECS\ECS_Entity.h"

#include "..\Tree\UITreeComponent.h"
#include "..\State\UIStateComponent.h"
#include "..\Frame\UIFrameComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIMovableCommandComponent::UIMovableCommandComponent()
{
	// Set the initial data
	m_Moving = false;
}

UIMovableCommandComponent::UIMovableCommandComponent(const UIMovableCommandComponent& other)
{
}

UIMovableCommandComponent::~UIMovableCommandComponent()
{
}

///////////////
// MODIFIERS //
///////////////

bool UIMovableCommandComponent::EvaluateCommand(CommandType _command)
{
	// Mouse press
	if (_command.actor == CommandActor::Mouse && _command.action == CommandAction::Press)
	{
		// Get the entity owner
		ECS_Entity* entity = GetEntityOwner();

		// Get the frame component
		UIFrameComponent* frameComponent = entity->FindComponent<UIFrameComponent>();

		// Set the relative location
		m_MouseRelativePressLocation.x = _command.firstParam - frameComponent->GetFramePosition().x;
		m_MouseRelativePressLocation.y = _command.secondParam - frameComponent->GetFramePosition().y;

		// Set moving to true
		m_Moving = true;
	}

	// Update
	if (_command.actor == CommandActor::System && _command.action == CommandAction::Update && m_Moving)
	{
		// Get the entity owner
		ECS_Entity* entity = GetEntityOwner();

		// Get the frame component
		UIFrameComponent* frameComponent = entity->FindComponent<UIFrameComponent>();

		// Set the new frame
		Vector2 newFramePosition = Vector2(_command.firstParam - m_MouseRelativePressLocation.x, _command.secondParam - m_MouseRelativePressLocation.y);

		// Set the frame
		frameComponent->SetFrame(newFramePosition, frameComponent->GetFrameSize());
	}

	// Lost focus or release
	if (_command.action == CommandAction::LostFocus || _command.action == CommandAction::Release)
	{
		// Moving = false
		m_Moving = false;
	}

	// If our callback was set
	return UICommandComponent::EvaluateCommand(_command);
}

/////////////
// VIRTUAL //
/////////////

void UIMovableCommandComponent::Update(unsigned int _updateId, float _timeElapsed)
{

}

void UIMovableCommandComponent::Clear()
{

}