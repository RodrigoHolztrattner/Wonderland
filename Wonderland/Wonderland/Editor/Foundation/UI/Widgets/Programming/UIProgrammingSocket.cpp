////////////////////////////////////////////////////////////////////////////////
// Filename: UIProgrammingSocket.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIProgrammingSocket.h"

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

UIProgrammingSocket::UIProgrammingSocket()
{
	// Set the initial data
	m_CurrentProgrammingLine = nullptr;
}

UIProgrammingSocket::UIProgrammingSocket(const UIProgrammingSocket& other)
{
}

UIProgrammingSocket::~UIProgrammingSocket()
{
}

bool UIProgrammingSocket::Create()
{
	// Create all components
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UICommandComponent* commandComponent = FindComponent<UICommandComponent>();
	UIColorComponent* renderableComponent = ECS_System<UIColorComponent>::Create();
	UIBorderComponent* borderComponent = ECS_System<UIBorderComponent>::Create();

	// Set the dependencies
	renderableComponent->RegisterDependency(treeComponent);
	renderableComponent->RegisterDependency(stateComponent);
	renderableComponent->RegisterDependency(frameComponent);
	borderComponent->RegisterDependency(treeComponent);
	borderComponent->RegisterDependency(stateComponent);
	borderComponent->RegisterDependency(frameComponent);

	// Set the frame component data
	frameComponent->SetFrame(Vector2(100, 100), Vector2(300, 300));

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIProgrammingSocket::ProcessCommand));

	// Set the renderable component data
	renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));

	// Set the border component data
	borderComponent->SetBorderColor(Vector4(0.4, 0.8, 0.4, 1.0));

	// Add all components
	AddComponent(renderableComponent);
	AddComponent(borderComponent);

	return true;
}

#include "UIProgrammingLine.h"
#include "..\..\Components\Frame\Anchor\UIAnchorComponent.h"

bool UIProgrammingSocket::ProcessCommand(CommandType* _command)
{
	// Click
	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press)
	{
		// Get our frame component and parent
		UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
		UIBase* parent = GetParent();

		// Create the programming line
		m_CurrentProgrammingLine = UIBase::CreateWidget<UIProgrammingLine, UIFrameComponent, UICommandComponent>(parent);

		// Calc the position
		Vector2 position = Vector2(frameComponent->GetFrameSize().width / 2 + frameComponent->GetFramePosition().x, frameComponent->GetFrameSize().height / 2 + frameComponent->GetFramePosition().y);

		// Set the line frame
		UIFrameComponent* lineFrameComponent = m_CurrentProgrammingLine->FindComponent<UIFrameComponent>();
		lineFrameComponent->SetFrame(position, Vector2(0, 0));
	}

	// Update
	if (_command->actor == CommandActor::System && _command->action == CommandAction::Update && m_CurrentProgrammingLine != nullptr)
	{
		// Get our frame component
		UIFrameComponent* frameComponent = m_CurrentProgrammingLine->FindComponent<UIFrameComponent>();

		// Calc the new size
		Vector2 newSize = Vector2(_command->firstParam - frameComponent->GetFramePosition().x, _command->secondParam - frameComponent->GetFramePosition().y);
		
		// Set the line frame
		UIFrameComponent* lineFrameComponent = m_CurrentProgrammingLine->FindComponent<UIFrameComponent>();
		lineFrameComponent->SetFrame(frameComponent->GetFramePosition(), newSize);
	}

	// Lost focus
	if (_command->actor == CommandActor::System && _command->action == CommandAction::LostFocus && m_CurrentProgrammingLine != nullptr)
	{
		// Get the widget object
		UIBase* widgetObject = (UIBase*)_command->object;

		// Cast to socket type
		UIProgrammingSocket* socket = dynamic_cast<UIProgrammingSocket*>(widgetObject);
		if (socket == nullptr)
		{
			// Remove the line
			m_CurrentProgrammingLine->Destroy();
			m_CurrentProgrammingLine = nullptr;

			// Log
			std::cout << "Warning: Trying to link but the target is not a socket!" << std::endl;

			return true;
		}

		// Try to make the link
		bool linkResult = MakeLink(socket, m_CurrentProgrammingLine);
		if (!linkResult)
		{
			// Remove the line
			m_CurrentProgrammingLine->Destroy();
			m_CurrentProgrammingLine = nullptr;

			return true;
		}

		// Get our frame component and the other socket too
		UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
		UIFrameComponent* otherFrameComponent = socket->FindComponent<UIFrameComponent>();

		// Create the anchor object
		UIAnchorComponent* anchor = ECS_System<UIAnchorComponent>::Create();

		// Set the anchor dependncies
		anchor->RegisterDependency(m_CurrentProgrammingLine->FindComponent<UITreeComponent>());
		anchor->RegisterDependency(m_CurrentProgrammingLine->FindComponent<UIFrameComponent>());

		// Set the anchor data
		anchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::Scale);
		anchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::Scale);
		anchor->AddAnchor(otherFrameComponent, UIAnchorComponent::Policy::RightAlign, UIAnchorComponent::Modifier::Scale);
		anchor->AddAnchor(otherFrameComponent, UIAnchorComponent::Policy::BottomAlign, UIAnchorComponent::Modifier::Scale);

		// Add all anchors to the line
		m_CurrentProgrammingLine->AddComponent(anchor);
	}
	
	return true;
}