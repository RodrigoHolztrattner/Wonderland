////////////////////////////////////////////////////////////////////////////////
// Filename: UITextField.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UITextField.h"

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
#include "..\..\Components\Renderable\Text\UITextComponent.h"

UITextField::UITextField()
{
}

UITextField::UITextField(const UITextField& other)
{
}

UITextField::~UITextField()
{
}

bool UITextField::Create()
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
	textComponent->RegisterDependency(frameComponent);
	textComponent->RegisterDependency(stateComponent);

	// Set the command component data
	commandComponent->SetCommandCallback(UICommandComponentCallback<CommandType*>(*this, &UITextField::ProcessCommand));

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

void UITextField::Update()
{
}

bool UITextField::ProcessCommand(CommandType* _command)
{
	UIColorComponent* renderableComponent = FindComponent<UIColorComponent>();
	UITextComponent* textComponent = FindComponent<UITextComponent>();

	// Process the command for the text component
	textComponent->ProcessCommand(_command);

	/*
	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press)
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.5, 0.2, 0.2, 1.0));
	}
	else if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Release)
	{
		// Set the renderable component data
		renderableComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));
	}
	*/

	return true;
}