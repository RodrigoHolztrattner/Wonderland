////////////////////////////////////////////////////////////////////////////////
// Filename: UIBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\ECS\ECS_Entity.h"

#include "..\ViewController\Modules\CommandModule\CommandType.h"

#include "..\Components\Tree\UITreeComponent.h"
#include "..\Components\State\UIStateComponent.h"
#include "..\Components\Frame\UIFrameComponent.h"

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
class UIBase : public ECS_Entity
{
public:

	template<typename WidgetClass, typename FrameComponent = UIFrameComponent, typename CommandComponent = UICommandComponent>
	static WidgetClass* CreateWidget(UIBase* _parent)
	{
		// Create the widget on the memory
		WidgetClass* widget = new WidgetClass();

		// Create all components
		UIStateComponent* stateComponent = ECS_System<UIStateComponent>::Create();
		UITreeComponent* treeComponent = ECS_System<UITreeComponent>::Create();
		UIFrameComponent* frameComponent = ECS_System<FrameComponent>::Create();
		CommandComponent* commandComponent = ECS_System<CommandComponent>::Create();

		// Set the dependencies
		treeComponent->RegisterDependency(stateComponent);
		frameComponent->RegisterDependency(treeComponent);
		commandComponent->RegisterDependency(treeComponent);
		commandComponent->RegisterDependency(stateComponent);
		commandComponent->RegisterDependency(frameComponent);

		// Add all components
		widget->AddComponent(treeComponent);
		widget->AddComponent(stateComponent);
		widget->AddComponent(frameComponent);
		widget->AddComponent(commandComponent);

		// If the parent is valid
		if (_parent != nullptr)
		{
			// Get the parent tree component
			UITreeComponent* parentTreeComponent = _parent->FindComponent<UITreeComponent>();

			// Add this child
			parentTreeComponent->AddChild(treeComponent);

			// Set our parent
			treeComponent->SetParent(parentTreeComponent);
		}

		// Create the widget
		widget->Create();

		return widget;
	}

	UIBase();
	UIBase(const UIBase&);
	~UIBase();

	// Return the parent
	UIBase* GetParent();

	// Return the root parent
	UIBase* GetRootParent();

	// Test
	void Update();

/////////////
// VIRTUAL //
public: /////

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

	// Render this widget
	virtual void Render() {};

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

	// The debug name
	std::string m_DebugName;
};