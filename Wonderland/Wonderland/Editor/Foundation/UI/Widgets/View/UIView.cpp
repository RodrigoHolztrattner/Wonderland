////////////////////////////////////////////////////////////////////////////////
// Filename: UIView.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIView.h"

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

UIView::UIView()
{
}

UIView::UIView(const UIView& other)
{
}

UIView::~UIView()
{
}

bool UIView::Create()
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
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UIView::ProcessCommand));

	// Set the renderable component data
	renderableComponent->SetColor(Vector4(0.15, 0.15, 0.15, 1.0));

	// Set the border component data
	borderComponent->SetBorderColor(Vector4(0.15, 0.15, 0.15, 1.0));

	// Add all components
	AddComponent(renderableComponent);
	AddComponent(borderComponent);

	return true;
}

void UIView::Update()
{
}

#include "..\Programming\UIProgrammingBox.h"
#include "..\..\Components\Command\UIMovableCommandComponent.h"

bool UIView::ProcessCommand(CommandType* _command)
{
	return true;
}