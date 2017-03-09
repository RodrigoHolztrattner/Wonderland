////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenuLaneView.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIMenuLaneView.h"
#include "UIMenuButton.h"

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
#include "..\..\Components\Frame\Anchor\UIAnchorComponent.h"

UIMenuLaneView::UIMenuLaneView()
{
	// Set the initial data
	// ...
}

UIMenuLaneView::UIMenuLaneView(const UIMenuLaneView& other)
{
}

UIMenuLaneView::~UIMenuLaneView()
{
}

bool UIMenuLaneView::Create()
{
	// Create all components
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UICommandComponent* commandComponent = FindComponent<UICommandComponent>();
	UIColorComponent* renderableComponent = ECS_System<UIColorComponent>::Create();
	UIBorderComponent* borderComponent = ECS_System<UIBorderComponent>::Create();

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIMenuLaneView::ProcessCommand));

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
	renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));

	// Set the border component data
	borderComponent->SetBorderColor(Vector4(0.1, 0.1, 0.1, 1.0));

	// Add all components
	AddComponent(renderableComponent);
	AddComponent(borderComponent);

	return true;
}


UIMenuButton* UIMenuLaneView::AddButton(char* _label)
{
	// Create the new button
	UIMenuButton* button = UIBase::CreateWidget<UIMenuButton, UIFrameComponent, UICommandComponent>(this);
	button->RegisterChainOwner(this);

	// Get the button components
	UIFrameComponent* buttonFrameComponent = button->FindComponent<UIFrameComponent>();
	UITreeComponent* buttonTreeComponent = button->FindComponent<UITreeComponent>();
	UITextComponent* buttonTextComponent = button->FindComponent<UITextComponent>();

	// Get our frame
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();

	// the button width and height
	#define ButtonHeight	25

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
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::Move);
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::MovePin);

		// Get the parent frame component
		UIFrameComponent* parentFrameComponent = FindComponent<UIFrameComponent>();

		// Set the button size
		buttonFrameComponent->SetFrame(Vector2(frameComponent->GetFramePosition().x, frameComponent->GetFramePosition().y + frameComponent->GetFrameSize().height), Vector2(frameComponent->GetFrameSize().width, ButtonHeight));
	}
	else
	{
		// Use the parent position
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::MovePin);
		buttonAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::MovePin);

		// Set the new button frame
		buttonFrameComponent->SetFrame(Vector2(200, 60), Vector2(frameComponent->GetFrameSize().width, ButtonHeight));
	}

	// Add the anchor component
	button->AddComponent(buttonAnchor);

	// Set the text
	buttonTextComponent->SetText(_label);

	// Add to the array
	m_MenuButtons.Add(button);

	//
	SetChainStatus(false);

	// Set our frame size
	frameComponent->SetFrame(frameComponent->GetFramePosition(), Vector2(frameComponent->GetFrameSize().width, m_MenuButtons.Size() * ButtonHeight));

	return button;
}

bool UIMenuLaneView::IsRelated(UIMenuChain* _other, bool _ignoreChilds)
{
	// Get the tree component
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();

	// Check for the chain owner
	if (m_ChainOwner == _other)
	{
		return true;
	}

	// Check if we should ignore the childs
	if (!_ignoreChilds)
	{
		// For each child
		for (int i = 0; i < m_MenuButtons.Size(); i++)
		{
			// Get the child button
			UIMenuChain* childButton = m_MenuButtons[i];

			// Check if the ptrs are equal
			if (childButton == _other)
			{
				return true;
			}
		}
	}

	return false;
}

void UIMenuLaneView::ForceVisibleStatus(bool _status)
{
	// Get our state component
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();

	// Set the visibility status
	stateComponent->SetIsVisible(_status);

	// If we have an chain owner
	if (m_ChainOwner)
	{
		// Echo the visible status
		m_ChainOwner->ForceVisibleStatus(_status);
	}
}

void UIMenuLaneView::SetChainStatus(bool _status)
{
	// If we have a menubutton owner
	if (m_ChainOwner != nullptr)
	{
		// Confirm the chain
		m_ChainOwner->SetChainStatus(_status);
	}

	// Base call
	UIMenuChain::SetChainStatus(_status);
}

void UIMenuLaneView::EchoChainStatus(bool _status)
{
	// For each chain child
	for (int i = 0; i < m_MenuButtons.Size(); i++)
	{
		// Echo to this child
		m_MenuButtons[i]->EchoChainStatus(_status);
	}

	// Force visible status
	UIMenuChain::EchoChainStatus(_status);
}

bool UIMenuLaneView::ProcessCommand(CommandType* _command)
{
	UIColorComponent* renderableComponent = FindComponent<UIColorComponent>();

	// Hover
	if (_command->actor == CommandActor::System && _command->action == CommandAction::Hover)
	{
		// Confirm the chain
		SetChainStatus(true);
	}

	// Hover clear
	if (_command->actor == CommandActor::System && _command->action == CommandAction::HoverClear)
	{
		// Check if we lost the hover to another widget
		if (_command->object != nullptr)
		{
			// Try to cast to a chain-like object
			UIMenuChain* chainObject = dynamic_cast<UIMenuChain*>((UIBase*)_command->object);
			if (chainObject == nullptr)
			{
				// Lost by another widget different from any menu-like ones
				SetChainStatus(false);

				return true;
			}

			// Check if the widget is related to this laneview
			bool isRelated = IsRelated(chainObject);
			if (isRelated)
			{
				// Stay normal!
				SetChainStatus(true);
			}
			else
			{
				// Lost by another widget different from any menu-like ones
				SetChainStatus(false);
			}

		}
		// We lost by going out of bounds
		else
		{
			// Set the chain status
			SetChainStatus(false);
		}
	}

	return true;
}