////////////////////////////////////////////////////////////////////////////////
// Filename: UIBase.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIBase.h"

///////////////
// NAMESPACE //
///////////////

UIBase::UIBase(UIBase* _parent) : UIFrame(this) // : ShaderRenderer(_renderShader)
{
	// Take ownership (we will store the parent ptr)
	_parent = UIBase::TakeOwnership(_parent);

	// Set the initial data
	m_Parent = _parent;
	m_ReferenceCounter = 0; // We start with zero reference
	m_IsPendingDeletion = false;
	m_IsVisible = true;
	m_IsRenderable = true;
	m_CanReceiveCommands = true;

	// If the parent is not null
	if (_parent != nullptr)
	{
		// Register the parent child
		_parent->RegisterChild(this);

		// Find the root parent
		UIBase* currentParent = _parent;
		while (currentParent->GetParent() != nullptr)
		{
			// Get the topmost parent
			currentParent = currentParent->GetParent();
		}

		// Take ownership for the root parent
		currentParent = UIBase::TakeOwnership(currentParent);

		// Set the root parent
		m_RootParent = currentParent;
	}
	else
	{
		// Set the root parent
		m_RootParent = this;
	}

	// Initialize the frame module
	InitializeFrameModule();
}

UIBase::UIBase(const UIBase& other) : UIFrame(this)
{
}

UIBase::~UIBase()
{
	// Check if the reference counter is 0
	if (m_ReferenceCounter != 0)
	{
		// Error!
		// ...
	}
}

void UIBase::MoveToTop()
{
	// Check if we can change the position for this widget
	// ...

	// Check if the parent exists
	UIBase* parent = GetParent();
	if (parent == nullptr)
	{
		return;
	}

	// Get the parent child widget array
	Array<UIBase*>* widgetArray = parent->GetChildArray();

	// Find this widget inside the child array
	for (int i = 0; i < widgetArray->Size(); i++)
	{
		// Compare the ptrs
		if ((*widgetArray)[i] == this)
		{
			printf(("Widget de nome: " + (*widgetArray)[i]->GetDebugName() + " foi movida para o topo!\n").c_str());

			// Move this widget to the top
			widgetArray->Move(i, 0);

			return;
		}
	}
}