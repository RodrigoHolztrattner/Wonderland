////////////////////////////////////////////////////////////////////////////////
// Filename: UICommandComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UICommandComponent.h"

#include "..\..\..\ECS\ECS_Entity.h"

#include "..\Tree\UITreeComponent.h"
#include "..\State\UIStateComponent.h"
#include "..\Frame\UIFrameComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UICommandComponent::UICommandComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_ComponentOnFocus = nullptr;
}

UICommandComponent::UICommandComponent(const UICommandComponent& other) : ECS_Component(other)
{
}

UICommandComponent::~UICommandComponent()
{
}

///////////////
// MODIFIERS //
///////////////

bool UICommandComponent::EvaluateCommand(CommandType _command)
{
	// If our callback was set
	if (m_CommandCallback.IsSet())
	{
		return m_CommandCallback.Run(&_command);
	}

	return false;
}

void UICommandComponent::SetCommandCallback(UICommandComponentCallback<CommandType*> _callback)
{
	m_CommandCallback = _callback;
}

/////////////
// VIRTUAL //
/////////////

void UICommandComponent::Update(unsigned int _updateId, float _timeElapsed)
{

}

void UICommandComponent::Clear()
{

}