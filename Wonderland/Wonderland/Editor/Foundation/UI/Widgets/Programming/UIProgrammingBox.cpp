////////////////////////////////////////////////////////////////////////////////
// Filename: UIProgrammingBox.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIProgrammingBox.h"

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

#include "UIProgrammingSocket.h"

UIProgrammingBox::UIProgrammingBox()
{
}

UIProgrammingBox::UIProgrammingBox(const UIProgrammingBox& other)
{
}

UIProgrammingBox::~UIProgrammingBox()
{
}

bool UIProgrammingBox::Create()
{
	// Create all components
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UICommandComponent* commandComponent = FindComponent<UICommandComponent>();
	UIColorComponent* renderableComponent = ECS_System<UIColorComponent>::Create();
	UIBorderComponent* borderComponent = ECS_System<UIBorderComponent>::Create();
	UITextComponent* textComponent = ECS_System<UITextComponent>::Create();

	// Set the dependencies
	renderableComponent->RegisterDependency(treeComponent);
	renderableComponent->RegisterDependency(stateComponent);
	renderableComponent->RegisterDependency(frameComponent);
	borderComponent->RegisterDependency(treeComponent);
	borderComponent->RegisterDependency(stateComponent);
	borderComponent->RegisterDependency(frameComponent);
	textComponent->RegisterDependency(stateComponent);
	textComponent->RegisterDependency(frameComponent);

	// Set the frame component data
	frameComponent->SetFrame(Vector2(100, 100), Vector2(300, 300));

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIProgrammingBox::ProcessCommand));

	// Set the renderable component data
	renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));

	// Set the border component data
	borderComponent->SetBorderColor(Vector4(0.2, 0.2, 0.2, 1.0));

	// Set the text
	textComponent->SetFontType("monaco.ttf", 14);
	textComponent->SetFormatation(UIString::HorizontalFormatation::Centralized, UIString::VerticalFormatation::TopAlign);
	textComponent->SetPadAmout(Vector2(5, 10));
	textComponent->SetText("Programming Box");
	
	// Add all components
	AddComponent(renderableComponent);
	AddComponent(borderComponent);
	AddComponent(textComponent);

	UIProgrammingSocket* socket = UIBase::CreateWidget<UIProgrammingSocket, UIRelativeFrameComponent, UICommandComponent>(this);
	UIRelativeFrameComponent* socketFrameComponent = socket->FindComponent<UIRelativeFrameComponent>();
	socketFrameComponent->SetFrame(Vector2(0.03, 0.1), Vector2(0.06, 0.2));
	socket->SetType(UIProgrammingSocket::Type::Flow);
	socket->SetBehavior(UIProgrammingSocket::Behavior::In);

	UIProgrammingSocket* socket2 = UIBase::CreateWidget<UIProgrammingSocket, UIRelativeFrameComponent, UICommandComponent>(this);
	UIRelativeFrameComponent* socketFrameComponent2 = socket2->FindComponent<UIRelativeFrameComponent>();
	socketFrameComponent2->SetFrame(Vector2(0.9, 0.1), Vector2(0.06, 0.2));
	socket2->SetType(UIProgrammingSocket::Type::Flow);
	socket2->SetBehavior(UIProgrammingSocket::Behavior::Out);

	return true;
}

void UIProgrammingBox::Update()
{
}

bool UIProgrammingBox::ProcessCommand(CommandType* _command)
{
	UIColorComponent* renderableComponent = FindComponent<UIColorComponent>();
	UITextComponent* textComponent = FindComponent<UITextComponent>();

	// Process the command for the text component
	textComponent->ProcessCommand(_command);

	return true;
}