////////////////////////////////////////////////////////////////////////////////
// Filename: UIBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Support\Math\Math.h"
#include "UIFrame.h"
#include "..\..\Shader\ShaderRenderer.h"
#include "..\ViewController\Modules\CommandModule\CommandType.h"

#include <string>
#include <iostream>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UIBase
////////////////////////////////////////////////////////////////////////////////
class UIBase : public UIFrame // , public ShaderRenderer
{
public:
	UIBase(UIBase* _parent);
	UIBase(const UIBase&);
	~UIBase();

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command) = 0;

	// Update this widget
	virtual void Update(float _time)
	{
		// Call all the update funcs
		UpdateFrame();

		// Update all childs
		for (int i = 0; i < m_Childs.Size(); i++)
		{
			// Update this child
			m_Childs[i]->Update(_time);
		}
	}

////////////
// PARENT //
public://///

	// Return the parent
	UIBase* GetParent() { return m_Parent; }

	// Return the root parent
	UIBase* GetRootParent() { return m_RootParent; }

/////////////////
// CHILD ARRAY //
public: /////////

	// Return the child array
	Array<UIBase*>* GetChildArray() { return &m_Childs; }

	// Set widget position to top
	void MoveToTop();

private:

	// Register a new child for this widget
	void RegisterChild(UIBase* _child) 
	{ 
		// Take ownership and add the child
		_child = UIBase::TakeOwnership(_child);
		m_Childs.Add(_child);
	}

/////////////////
// FRAME COLOR //
public: /////////

	// Set the frame color
	void SetFrameColor(Vector4 _color) { m_FrameColor = _color; }

	// Return the frame color
	Vector4 GetFrameColor() { return m_FrameColor; }

///////////////
// RENDERING //
public: ///////

	// Render this widget
	virtual void Render() = 0;

///////////////
// REFERENCE //
public: ///////

	// Store a reference to this widget
	static UIBase* TakeOwnership(UIBase* _widget)
	{
		// Check if this widget is valid
		if (!UIBase::IsValid(_widget))
		{
			return nullptr;
		}

		// Increment the reference counter
		_widget->IncrementReferenceCounter();

		return _widget;
	}

	// Release this widget (release the reference)
	static UIBase* ReleaseWidget(UIBase* _widget)
	{
		// Check if the widget is valid
		if (_widget != nullptr)
		{
			// Decrement the reference counter
			_widget->DecrementReferenceCounter();
		}

		return nullptr;
	}

	// Mark to deletion
	static UIBase* DeleteWidget(UIBase* _widget)
	{
		// Mark to delete
		_widget->MarkToDelete();

		// Delete each child
		for (int i = 0; i < _widget->m_Childs.Size(); i++)
		{
			// Delete this child
			UIBase::DeleteWidget((_widget->m_Childs)[i]);
		}

		// Release the parent
		UIBase::ReleaseWidget(_widget->m_Parent);

		// Release the root parent
		UIBase::ReleaseWidget(_widget->m_RootParent);

		// Release the frame module
		_widget->ReleaseFrameModule();

		// Decrment the reference counter
		_widget->DecrementReferenceCounter();

		return nullptr;
	}

	// Check if this widget is valid
	static bool IsValid(UIBase* _widget)
	{
		// Check if our widget ptr is alid
		if (_widget == nullptr)
		{
			return false;
		}

		// IsPendingKill must be false and our reference counter must be at last one
		if (_widget->IsPendingDelete())
		{
			return false;
		}

		return true;
	}

protected:

	// Increment the reference counter
	void IncrementReferenceCounter()
	{
		m_ReferenceCounter++;
	}

	// Decrement the reference counter
	void DecrementReferenceCounter()
	{
		// Crement the reference counter
		m_ReferenceCounter--;

		// Check if we should delete this widget
		if (m_ReferenceCounter == 0)
		{
			// Is pending kill
			MarkToDelete();

			// Delete widget
			std::cout << "View with name: " << m_DebugName << " was deleted!" << std::endl;
		}
	}

/////////////
// CONTROL //
public: /////

	// If we are pending deletion
	bool IsPendingDelete()
	{
		return m_IsPendingDeletion;
	}

	// Mark to delete
	void MarkToDelete()
	{
		m_IsPendingDeletion = true;
	}

	// If this widget is visible
	bool IsVisible() { return m_IsVisible; }

	// Set the visibility state
	void SetVisibilityState(bool _isVisible) { m_IsVisible = _isVisible; }

	// If this widget is renderable
	bool IsRenderable() { return m_IsRenderable; }

	// Set the renderable state
	void SetRenderableState(bool _isRenderable) { m_IsRenderable = _isRenderable; }

	// If this widget can receive commands
	bool CanReceiveCommand() { return m_CanReceiveCommands; }

	// Set the receive command state
	void SetCanReceiveCommand(bool _canReceiveCommand) { m_CanReceiveCommands = _canReceiveCommand; }

///////////
// DEBUG //
public: ///

	// Set the debug name
	void SetDebugName(const char* _debugName)
	{
		m_DebugName = _debugName;
	}

	// Return the debug name
	std::string GetDebugName()
	{
		return m_DebugName;
	}


///////////////
// VARIABLES //
private: //////

	// The parent
	UIBase* m_Parent;

	// The root parent
	UIBase* m_RootParent;

	// All the child widgets
	Array<UIBase*> m_Childs;

	// The frame color
	Vector4 m_FrameColor;

	// The debug name
	std::string m_DebugName;

	// The reference counter
	unsigned int m_ReferenceCounter;

	// CONTROL VARIABLES //

	// If this widget is visible
	bool m_IsVisible;

	// If this widget is renderable
	bool m_IsRenderable;

	// If this widget is pending kill
	bool m_IsPendingDeletion;

	// If this widget can receive commands
	bool m_CanReceiveCommands;
};