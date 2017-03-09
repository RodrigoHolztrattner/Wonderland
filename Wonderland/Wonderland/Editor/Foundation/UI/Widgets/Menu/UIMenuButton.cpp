////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenuButton.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIMenuButton.h"
#include "UIMenuLaneView.h"

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
#include "..\..\Components\Frame\Fit\UITextFitComponent.h"
#include "..\..\Components\Frame\Anchor\UIAnchorComponent.h"

UIMenuButton::UIMenuButton()
{
	// Set the initial data
	m_LaneViewChild = nullptr;
	m_IsTopMenuButton = false;
	m_Pressing = false;
	m_Selected = false;
}

UIMenuButton::UIMenuButton(const UIMenuButton& other)
{
}

UIMenuButton::~UIMenuButton()
{
}

bool UIMenuButton::Create()
{
	// Create all components
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UICommandComponent* commandComponent = FindComponent<UICommandComponent>();
	UIColorComponent* renderableComponent = ECS_System<UIColorComponent>::Create();
	UIBorderComponent* borderComponent = ECS_System<UIBorderComponent>::Create();
	UITextComponent* textComponent = ECS_System<UITextComponent>::Create();
	//

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIMenuButton::ProcessCommand));

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
	renderableComponent->SetColor(Vector4(0.15, 0.15, 0.15, 1.0));

	// Set the border component data
	borderComponent->SetBorderColor(Vector4(0.15, 0.15, 0.15, 1.0));

	// Set the text data
	textComponent->SetFontType("segoeui.ttf", 10);

	// Add all components
	AddComponent(renderableComponent);
	AddComponent(borderComponent);
	AddComponent(textComponent);
	

	return true;
}

void UIMenuButton::SetIsTopMenuButton()
{
	UITextFitComponent* textFitComponent = ECS_System<UITextFitComponent>::Create();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UITextComponent* textComponent = FindComponent<UITextComponent>();

	textFitComponent->RegisterDependency(frameComponent);
	textFitComponent->RegisterDependency(textComponent);

	AddComponent(textFitComponent);

	m_IsTopMenuButton = true;
}

bool UIMenuButton::IsRelated(UIMenuChain* _other, bool _ignoreChilds)
{
	// Get the tree component
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();

	// Check for the chain owner
	if (m_ChainOwner == _other)
	{
		EchoChainStatus(false);
		return true;
	}

	// Check for the chain child
	if (m_LaneViewChild == _other)
	{
		return true;
	}

	// If the laneview exist
	if (m_LaneViewChild != nullptr)
	{
		// Ask the lane if the widget is related
		if (m_LaneViewChild->IsRelated(_other))
		{
			return true;
		}
	}

	// If the owner exist
	if (m_ChainOwner)
	{
		if (m_ChainOwner->IsRelated(_other))
		{
			EchoChainStatus(false);
			return true;
		}
	}

	return false;
}

void UIMenuButton::ForceVisibleStatus(bool _status)
{
	// Get our state and renderable components
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIColorComponent* renderableComponent = FindComponent<UIColorComponent>();

	// Set the visibility status
	// stateComponent->SetIsVisible(_status);

	// Check the status
	if (!_status)
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.15, 0.15, 0.15, 1.0));
	}
	else
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.3, 0.3, 0.3, 1.0));
	}
}

void UIMenuButton::SetChainStatus(bool _status)
{
	// Hide our childlane
	if (m_LaneViewChild != nullptr) m_LaneViewChild->ForceVisibleStatus(false);

	// If we have a menubutton owner
	if (m_ChainOwner != nullptr)
	{
		// Confirm the chain
		m_ChainOwner->SetChainStatus(_status);
	}

	// Base call
	UIMenuChain::SetChainStatus(_status);
}

void UIMenuButton::EchoChainStatus(bool _status)
{
	// If we have a child laneview
	if (m_LaneViewChild)
	{
		// Echo
		m_LaneViewChild->EchoChainStatus(_status);
	}

	// Force visible status
	UIMenuChain::EchoChainStatus(_status);
}

UIMenuLaneView* UIMenuButton::CreateLaneview()
{
	// Check if our laneview exist
	if (m_LaneViewChild != nullptr)
	{
		return m_LaneViewChild;
	}

	// Get our frame component
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();

	// The laneview
	m_LaneViewChild = UIBase::CreateWidget<UIMenuLaneView, UIRelativeFrameComponent, UICommandComponent>(GetRootParent());
	m_LaneViewChild->RegisterChainOwner(this);

	// Get the laneview components
	UIFrameComponent* laneviewFrameComponent = m_LaneViewChild->FindComponent<UIFrameComponent>();
	UITreeComponent* laneviewTreeComponent = m_LaneViewChild->FindComponent<UITreeComponent>();

	// Set the laneview frame
	laneviewFrameComponent->SetFrame(Vector2(frameComponent->GetFramePosition().x, frameComponent->GetFramePosition().y + frameComponent->GetFrameSize().height), Vector2(200, 700));

	// Create the anchor component
	UIAnchorComponent* laneviewAnchor = ECS_System<UIAnchorComponent>::Create();

	// Set the dependencies
	laneviewAnchor->RegisterDependency(laneviewFrameComponent);
	laneviewAnchor->RegisterDependency(laneviewTreeComponent);

	// Check the type of button
	if (m_IsTopMenuButton)
	{
		// Add the anchor
		laneviewAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::Move);
		laneviewAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::MovePin);
	}
	// Normal menu button
	else
	{
		// Add the anchor
		laneviewAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::MovePin);
		laneviewAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::Move);
	}
	
	// Add the anchor component to the laneview
	m_LaneViewChild->AddComponent(laneviewAnchor);

	return m_LaneViewChild;
}

bool UIMenuButton::ProcessCommand(CommandType* _command)
{
	// Get our renderable component
	UIColorComponent* renderableComponent = FindComponent<UIColorComponent>();

	// Hover
	if (_command->actor == CommandActor::System && _command->action == CommandAction::Hover && !m_Pressing)
	{
		// Confirm the chain
		if (m_LaneViewChild != nullptr)
		{
			m_LaneViewChild->SetChainStatus(true);
		}
		else
		{
			SetChainStatus(true);
		}
	}

	// Hover clear
	if (_command->actor == CommandActor::System && _command->action == CommandAction::HoverClear && !m_Pressing)
	{
		// Check if we are a top button
		if (!m_IsTopMenuButton)
		{
			// We lost our hover, ok, got it!
			ForceVisibleStatus(false);
		}

		// Check if we lost the hover to another widget
		if (_command->object != nullptr)
		{
			// Try to cast to a chain-like object
			UIMenuChain* chainObject = dynamic_cast<UIMenuChain*>((UIBase*)_command->object);
			if (chainObject == nullptr)
			{
				// Lost by another widget different from any menu-like ones
				SetChainStatus(false);
				// m_Selected = false;

				return true;
			}

			// Check if the widget is related to us
			bool isRelated = IsRelated(chainObject);
			if (isRelated)
			{

			}
			// No
			else
			{
				// Hide our childlane
				if (m_LaneViewChild != nullptr) m_LaneViewChild->ForceVisibleStatus(false);
				if(m_ChainOwner != nullptr) m_ChainOwner->ForceVisibleStatus(false);
				ForceVisibleStatus(false);
			}
		}
		// We lost by going out of bounds
		else
		{
			// Set the chain status
			SetChainStatus(false);
			// m_Selected = false;
		}
	}

	// Press
	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press)
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));

		// Confirm the chain
		if (m_LaneViewChild != nullptr) m_LaneViewChild->SetChainStatus(true);

		// Set pressing to true
		m_Pressing = true;

		// We selected this button
		m_Selected = true;
	}
	// Release
	else if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Release && m_Pressing)
	{
		// Check if the click callback exist
		if (m_ClickCallback.IsSet())
		{
			// Call the click callback
			m_ClickCallback.Run(this);
		}

		// Set pressing to false
		m_Pressing = false;
	}

	// Lost focus
	if (_command->actor == CommandActor::System && _command->action == CommandAction::LostFocus)
	{
		// Set pressing to false
		m_Pressing = false;
	}

	return true;
}

void UIMenuButton::RegisterClickCallback(MemberCallback<void*> _callback)
{
	m_ClickCallback = _callback;
}