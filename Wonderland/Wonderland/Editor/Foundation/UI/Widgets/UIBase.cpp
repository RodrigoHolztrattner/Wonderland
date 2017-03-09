////////////////////////////////////////////////////////////////////////////////
// Filename: UIBase.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIBase.h"

///////////////
// NAMESPACE //
///////////////

#include "..\..\ECS\ECS_System.h"
#include "..\Components\Tree\UITreeComponent.h"
#include "..\Components\State\UIStateComponent.h"
#include "..\Components\Frame\UIFrameComponent.h"
#include "..\Components\Command\UICommandComponent.h"
#include "..\Components\Renderable\Color\UIColorComponent.h"
#include "..\Components\Renderable\Border\UIBorderComponent.h"

UIBase::UIBase()
{
}

UIBase::UIBase(const UIBase& other)
{
}

UIBase::~UIBase()
{
}

UIBase* UIBase::GetParent()
{
	// Get the tree component
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();

	// Fint the tree parent
	UITreeComponent* parentTreeComponent = treeComponent->GetParent();
	
	// Check if the parent tree is valid
	if (parentTreeComponent != nullptr)
	{
		return (UIBase*)parentTreeComponent->GetEntityOwner();;
	}

	return nullptr;
}

UIBase* UIBase::GetRootParent()
{
	// Check if our current parent is valid
	UIBase* currentParent = GetParent();
	if (currentParent == nullptr) // We are the root parent
	{
		return this;
	}

	// Untill we find a null parent...
	while (currentParent->GetParent() != nullptr)
	{
		// Get the next parent
		currentParent = currentParent->GetParent();
	}

	return currentParent;
}

void UIBase::Update()
{
	UIRenderableComponent* renderableComponent = (UIRenderableComponent*)FindComponentByID(UIRenderableComponent::ClassComponentID());
	renderableComponent->Render();
}

bool UIBase::ProcessCommand(CommandType* _command)
{


	return true;
}