////////////////////////////////////////////////////////////////////////////////
// Filename: ProjectExplorerView.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ProjectExplorerView.h"

///////////////
// NAMESPACE //
///////////////

ProjectExplorerView::ProjectExplorerView()
{
}

ProjectExplorerView::ProjectExplorerView(const ProjectExplorerView& other)
{
}

ProjectExplorerView::~ProjectExplorerView()
{
}

bool ProjectExplorerView::Create()
{
	// Call the super
	if (!UIView::Create())
	{
		return false;
	}

	return true;
}

void ProjectExplorerView::SetProjectDataReference(ProjectData* _projectData)
{
	m_ProjectData = _projectData;
}

bool ProjectExplorerView::ProcessCommand(CommandType* _command)
{
	// Call the super
	UIView::ProcessCommand(_command);

	return true;
}

void ProjectExplorerView::ModelChangedAlert()
{

}