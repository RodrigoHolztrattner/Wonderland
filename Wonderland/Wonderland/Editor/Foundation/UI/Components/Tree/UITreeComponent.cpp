////////////////////////////////////////////////////////////////////////////////
// Filename: UITreeComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UITreeComponent.h"
#include "..\..\..\ECS\ECS_Entity.h"
#include "..\State\UIStateComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UITreeComponent::UITreeComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_Parent = nullptr;
}

UITreeComponent::UITreeComponent(const UITreeComponent& other) : ECS_Component(other)
{
}

UITreeComponent::~UITreeComponent()
{
}

///////////////
// MODIFIERS //
///////////////

void UITreeComponent::SetParent(UITreeComponent* _parent)
{
	m_Parent = _parent;
}

UITreeComponent* UITreeComponent::GetParent()
{
	return m_Parent;
}

void UITreeComponent::AddChild(UITreeComponent* _child)
{
	m_ChildArray.Add(_child);
}

unsigned int UITreeComponent::GetChildArraySize()
{
	return m_ChildArray.Size();
}

UITreeComponent* UITreeComponent::GetChildByIndex(unsigned int _index)
{
	return m_ChildArray[_index];
}

void UITreeComponent::MoveChild(unsigned int _from, unsigned int _to)
{
	m_ChildArray.Move(_from, _to);
}

void UITreeComponent::MoveToTop()
{
	// Check if the parent exists
	if (m_Parent == nullptr)
	{
		return;
	}
	
	// Find this widget inside the child array
	for (int i = 0; i < m_Parent->GetChildArraySize(); i++)
	{
		// Compare the ptrs
		if (m_Parent->GetChildByIndex(i) == this)
		{
			// Find the first location we can swap this view
			for (int j = 0; j < m_Parent->GetChildArraySize(); j++)
			{
				// Get the child
				UITreeComponent* swapTreeComponent = m_Parent->GetChildByIndex(j);

				// The the child entity
				ECS_Entity* swapChild = swapTreeComponent->GetEntityOwner();

				// The the child state
				UIStateComponent* swapStateComponent = swapChild->FindComponent<UIStateComponent>();

				// Check if we can use this to swap
				if (!swapStateComponent->IsAlwaysOnTop())
				{
					// Move this widget to the top
					m_Parent->MoveChild(i, j);

					// Move the parent to the top
					m_Parent->MoveToTop();

					return;
				}
			}
		}
	}
}

void UITreeComponent::RemoveChild(UITreeComponent* _child)
{
	// Find the child inside the child array
	for (int i = 0; i < m_ChildArray.Size(); i++)
	{
		// Compare the childs
		if (m_ChildArray[i] == _child)
		{
			// Remove the child
			m_ChildArray.Remove(i);
		}
	}
}

/////////////
// VIRTUAL //
/////////////

void UITreeComponent::Update(unsigned int _updateId, float _timeElapsed)
{

}

void UITreeComponent::Clear()
{
	// Remove from the parent
	m_Parent->RemoveChild(this);

	// Send a clear signal to all childs
	for (int i = 0; i < m_ChildArray.Size(); i++)
	{
		// Send the signal
		// m_ChildArray[i]->Clear();

		// Destroy the child entity
		m_ChildArray[i]->GetEntityOwner()->Destroy();
	}

	// Zero the child array
	m_ChildArray.Zero();
}