////////////////////////////////////////////////////////////////////////////////
// Filename: RenderModule.cpp
////////////////////////////////////////////////////////////////////////////////
#include "RenderModule.h"

#include "..\..\..\Widgets\UIBase.h"
#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\..\..\Components\Tree\UITreeComponent.h"
#include "..\..\..\Components\State\UIStateComponent.h"
#include "..\..\..\Components\Frame\UIFrameComponent.h"
#include "..\..\..\Components\Command\UICommandComponent.h"

RenderModule::RenderModule()
{
}

RenderModule::RenderModule(const RenderModule& other)
{
}

RenderModule::~RenderModule()
{
}

bool RenderModule::Initialize()
{
	return true;
}

void RenderModule::Shutdown()
{

}

void RenderModule::Update(UIBase* _currentWidget, float _time, unsigned int _renderingId)
{
	// Zero the depth order
	m_DepthOrder = 0;

	// Start the rendering process
	StartRenderProcessAux(_currentWidget, _renderingId);
}

void RenderModule::StartRenderProcessAux(UIBase* _currentWidget, unsigned int _renderingId)
{
	// Get the entity dependency components
	UIStateComponent* entityState = _currentWidget->FindComponent<UIStateComponent>();
	UITreeComponent* entityTree = _currentWidget->FindComponent<UITreeComponent>();

	// Check if the entity is visible
	if (!entityState->IsVisible())
	{
		return;
	}

	// Render this widget if it is renderable
	if (entityState->IsRenderable())
	{
		// Set the rendering id
		entityState->SetRenderingID(_renderingId);

		// Set the depth order
		entityState->SetDepthOrder(m_DepthOrder);

		// Increment the depth order
		m_DepthOrder += 0.001;
	}

	// For each child widget
	for (int i = entityTree->GetChildArraySize()-1; i >= 0; i--)
	{
		// Get the child entity tree component
		UITreeComponent* childTreeComponent = entityTree->GetChildByIndex(i);

		// Get the child widget
		UIBase* childWidget = (UIBase*)childTreeComponent->GetEntityOwner();

		// Call this function for the child widget
		StartRenderProcessAux(childWidget, _renderingId);
	}
}