////////////////////////////////////////////////////////////////////////////////
// Filename: UIRenderableComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIRenderableComponent.h"

#include "..\..\..\ECS\ECS_Entity.h"

#include "..\Tree\UITreeComponent.h"
#include "..\State\UIStateComponent.h"
#include "..\Frame\UIFrameComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIRenderableComponent::UIRenderableComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_RenderOrder = 0;
}

UIRenderableComponent::UIRenderableComponent(const UIRenderableComponent& other) : ECS_Component(other)
{
}

UIRenderableComponent::~UIRenderableComponent()
{
}

///////////////
// MODIFIERS //
///////////////

void UIRenderableComponent::Render()
{
	// Call the aux function
	RenderAux(0);
}

void UIRenderableComponent::RenderAux(unsigned int _renderOrder)
{
	// Get the entity dependency components
	UIStateComponent* entityState = (UIStateComponent*)GetEntityOwner()->FindComponentByID(UIStateComponent::ClassComponentID());
	UIFrameComponent* entityFrame = (UIFrameComponent*)GetEntityOwner()->FindComponentByID(UIFrameComponent::ClassComponentID());
	UITreeComponent* entityTree = (UITreeComponent*)GetEntityOwner()->FindComponentByID(UITreeComponent::ClassComponentID());

	// Check if the entity is visible
	if (!entityState->IsVisible())
	{
		return;
	}

	// For each tree child
	for (int i = 0; i < entityTree->GetChildArraySize(); i++)
	{
		// Get the child entity tree component
		UITreeComponent* childTreeComponent = entityTree->GetChildByIndex(i);

		// Get the renderable component from the child tree component
		UIRenderableComponent* childRenderableComponent = (UIRenderableComponent*)childTreeComponent->GetEntityComponentById(UIRenderableComponent::ClassComponentID());

		// Call the child render function
		childRenderableComponent->RenderAux(_renderOrder + 1);
	}

	// Check if this entity is renderable
	if (entityState->IsRenderable())
	{
		// Set the render order for this object
		m_RenderOrder = _renderOrder;

		// Render this entity
		this->SetShader();
	}
}

/////////////
// VIRTUAL //
/////////////

void UIRenderableComponent::Update(unsigned int _updateId, float _timeElapsed)
{

}

void UIRenderableComponent::Clear()
{

}