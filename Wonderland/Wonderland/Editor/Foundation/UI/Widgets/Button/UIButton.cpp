////////////////////////////////////////////////////////////////////////////////
// Filename: UIButton.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIButton.h"

///////////////
// NAMESPACE //
///////////////

#include "..\..\..\ECS\ECS_System.h"
#include "..\..\Components\Tree\UITreeComponent.h"
#include "..\..\Components\State\UIStateComponent.h"
#include "..\..\Components\Frame\UIFrameComponent.h"
#include "..\..\Components\Command\UICommandComponent.h"
#include "..\..\Components\Renderable\Color\UIColorComponent.h"
#include "..\..\Components\Renderable\Border\UIBorderComponent.h"
#include "..\..\Components\Frame\UIRelativeFrameComponent.h"
#include "..\..\Components\Renderable\Text\UITextComponent.h"

UIButton::UIButton()
{
}

UIButton::UIButton(const UIButton& other)
{
}

UIButton::~UIButton()
{
}

bool UIButton::Create()
{
	// Create all components
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UICommandComponent* commandComponent = FindComponent<UICommandComponent>();
	UIColorComponent* renderableComponent = ECS_System<UIColorComponent>::Create();
	UIBorderComponent* borderComponent = ECS_System<UIBorderComponent>::Create();
	UITextComponent* textComponent = ECS_System<UITextComponent>::Create();

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIButton::ProcessCommand));

	// Set the dependencies
	renderableComponent->RegisterDependency(treeComponent);
	renderableComponent->RegisterDependency(stateComponent);
	renderableComponent->RegisterDependency(frameComponent);
	borderComponent->RegisterDependency(treeComponent);
	borderComponent->RegisterDependency(stateComponent);
	borderComponent->RegisterDependency(frameComponent);
	textComponent->RegisterDependency(frameComponent);
	textComponent->RegisterDependency(stateComponent);

	// Set the frame component data
	frameComponent->SetFrame(Vector2(100, 100), Vector2(300, 300));

	// Set the renderable component data
	renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));

	// Set the border component data
	borderComponent->SetBorderColor(Vector4(0.4, 0.8, 0.4, 1.0));

	// Set the text data
	textComponent->SetFontType("monaco.ttf", 16);

	// Add all components
	AddComponent(renderableComponent);
	AddComponent(borderComponent);
	AddComponent(textComponent);

	return true;
}

bool UIButton::ProcessCommand(CommandType* _command)
{
	UIColorComponent* renderableComponent = FindComponent<UIColorComponent>();

	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press)
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.5, 0.2, 0.2, 1.0));
	}
	else if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Release)
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));

		// Check if the click callback exist
		if (m_ClickCallback.IsSet())
		{
			// Call the click callback
			m_ClickCallback.Run(this);
		}
	}

	if (_command->actor == CommandActor::System && _command->action == CommandAction::LostFocus)
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));
	}

	return true;
}

void UIButton::RegisterClickCallback(MemberCallback<void*> _callback)
{
	m_ClickCallback = _callback;
}