////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIMenu.h"

///////////////
// NAMESPACE //
///////////////

#include "..\..\..\ECS\ECS_System.h"
#include "..\..\Components\Frame\Anchor\UIAnchorComponent.h"
#include "..\..\Components\Tree\UITreeComponent.h"
#include "..\..\Components\State\UIStateComponent.h"
#include "..\..\Components\Frame\UIFrameComponent.h"
#include "..\..\Components\Command\UICommandComponent.h"
#include "..\..\Components\Renderable\Color\UIColorComponent.h"
#include "..\..\Components\Renderable\Border\UIBorderComponent.h"
#include "..\..\Components\Frame\UIRelativeFrameComponent.h"
#include "..\..\Components\Renderable\Text\UITextComponent.h"

UIMenu::UIMenu()
{
}

UIMenu::UIMenu(const UIMenu& other)
{
}

UIMenu::~UIMenu()
{
}

bool UIMenu::Create()
{
	// Create all components
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UICommandComponent* commandComponent = FindComponent<UICommandComponent>();
	UIColorComponent* renderableComponent = ECS_System<UIColorComponent>::Create();
	UIBorderComponent* borderComponent = ECS_System<UIBorderComponent>::Create();

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIMenu::ProcessCommand));

	// Set the dependencies
	renderableComponent->RegisterDependency(treeComponent);
	renderableComponent->RegisterDependency(stateComponent);
	renderableComponent->RegisterDependency(frameComponent);
	borderComponent->RegisterDependency(treeComponent);
	borderComponent->RegisterDependency(stateComponent);
	borderComponent->RegisterDependency(frameComponent);

	// Set the frame component data
	frameComponent->SetFrame(Vector2(100, 100), Vector2(300, 300));

	// Set the renderable component data
	renderableComponent->SetColor(Vector4(0.15, 0.15, 0.15, 1.0));

	// Set the border component data
	borderComponent->SetBorderColor(Vector4(0.15, 0.15, 0.15, 1.0));

	// Add all components
	AddComponent(renderableComponent);
	AddComponent(borderComponent);

	return true;
}

UIMenuButton* UIMenu::AddButton(char* _label)
{
	// Create the new button
	UIMenuButton* button = UIBase::CreateWidget<UIMenuButton, UIFrameComponent, UICommandComponent>(this);
	UIFrameComponent* buttonFrameComponent = button->FindComponent<UIFrameComponent>();
	UITreeComponent* buttonTreeComponent = button->FindComponent<UITreeComponent>();
	UITextComponent* buttonTextComponent = button->FindComponent<UITextComponent>();

	// Set the button type
	button->SetIsTopMenuButton();

	// the button width
	#define ButtonWidth	80

	// Create a new anchor for this button
	UIAnchorComponent* buttonAnchor = ECS_System<UIAnchorComponent>::Create();

	// Set the anchor dependencies
	buttonAnchor->RegisterDependency(buttonFrameComponent);
	buttonAnchor->RegisterDependency(buttonTreeComponent);

	// Check if we have at last one button inside the array
	if (m_MenuButtons.Size())
	{
		// Get the last button
		UIMenuButton* lastButton = m_MenuButtons[m_MenuButtons.Size() - 1];

		// Get the last button frame component
		UIFrameComponent* frameComponent = lastButton->FindComponent<UIFrameComponent>();

		// Use the parent position
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::MovePin);
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::Move);
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::BottomAlign, UIAnchorComponent::Modifier::Pin);

		// Get the parent frame component
		UIFrameComponent* parentFrameComponent = FindComponent<UIFrameComponent>();

		// Set the button size
		buttonFrameComponent->SetFrame(Vector2(0, 0), Vector2(ButtonWidth, parentFrameComponent->GetFrameSize().height));
	}
	else
	{
		// Get our frame
		UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();

		// Use the parent position
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::MovePin);
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::MovePin);
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::BottomAlign, UIAnchorComponent::Modifier::Pin);

		// Set the new button frame
		buttonFrameComponent->SetFrame(frameComponent->GetFramePosition(), Vector2(ButtonWidth, frameComponent->GetFrameSize().height));
	}

	// Add the anchor component
	button->AddComponent(buttonAnchor);

	// Set the text
	buttonTextComponent->SetText(_label);

	// Add to the array
	m_MenuButtons.Add(button);

	return button;
}

bool UIMenu::ProcessCommand(CommandType* _command)
{
	/*
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
	*/
	return true;
}

void UIMenu::RegisterClickCallback(MemberCallback<void*> _callback)
{
	m_ClickCallback = _callback;
}