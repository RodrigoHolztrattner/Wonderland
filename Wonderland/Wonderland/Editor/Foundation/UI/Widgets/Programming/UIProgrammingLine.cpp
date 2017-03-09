////////////////////////////////////////////////////////////////////////////////
// Filename: UIProgrammingLine.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIProgrammingLine.h"

///////////////
// NAMESPACE //
///////////////

#include "..\..\..\ECS\ECS_System.h"
#include "..\..\Components\Tree\UITreeComponent.h"
#include "..\..\Components\State\UIStateComponent.h"
#include "..\..\Components\Frame\UIFrameComponent.h"
#include "..\..\Components\Command\UICommandComponent.h"
#include "..\..\Components\Renderable\Line\UILineComponent.h"

UIProgrammingLine::UIProgrammingLine()
{
}

UIProgrammingLine::UIProgrammingLine(const UIProgrammingLine& other)
{
}

UIProgrammingLine::~UIProgrammingLine()
{
}

bool UIProgrammingLine::Create()
{
	// Create all components
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIFrameComponent* frameComponent = FindComponent<UIFrameComponent>();
	UICommandComponent* commandComponent = FindComponent<UICommandComponent>();
	UILineComponent* renderableComponent = ECS_System<UILineComponent>::Create();

	// Set the dependencies
	renderableComponent->RegisterDependency(treeComponent);
	renderableComponent->RegisterDependency(stateComponent);
	renderableComponent->RegisterDependency(frameComponent);

	// Set the state data
	stateComponent->SetCanReceiveCommands(false);
	stateComponent->SetIsAlwaysOnTop(true);

	// Set the frame component data
	frameComponent->SetFrame(Vector2(100, 100), Vector2(300, 300));

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIProgrammingLine::ProcessCommand));

	// Set the renderable component data
	renderableComponent->SetLineColor(Vector4(0.1, 0.1, 0.8, 1.0));

	// Add all components
	AddComponent(renderableComponent);

	return true;
}

bool UIProgrammingLine::ProcessCommand(CommandType* _command)
{
	return true;
}

void UIProgrammingLine::SetSockets(UIProgrammingSocket* _from, UIProgrammingSocket* _to)
{

}