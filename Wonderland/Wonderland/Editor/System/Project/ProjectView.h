////////////////////////////////////////////////////////////////////////////////
// Filename: ProjectView.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Foundation\UI\UI.h"
#include "..\..\Foundation\MVC\MVC_View.h"
#include "ProjectData.h"
#include "ProjectExplorerView.h"
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
// Class name: ProjectView
////////////////////////////////////////////////////////////////////////////////
class ProjectView : public UIView, public MVC_View
{
	// UIBase is a friend
	friend UIBase;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	ProjectView();

	// We cant copy or destruct too
	ProjectView(const ProjectView&);
	~ProjectView();

	// Create this widget (called from the UIBase)
	virtual bool Create();

	// Set the project data reference
	void SetProjectDataReference(ProjectData* _projectData);

public:

/////////////
// VIRTUAL //
public: /////

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

	// Model changed callback
	virtual void ModelChangedAlert();

///////////////
// VARIABLES //
private: //////

	// Reference to the project data
	ProjectData* m_ProjectData;

	// The project explorer
	ProjectExplorerView* m_ExplorerView;

};