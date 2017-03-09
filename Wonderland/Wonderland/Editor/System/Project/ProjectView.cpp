////////////////////////////////////////////////////////////////////////////////
// Filename: ProjectView.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ProjectView.h"

///////////////
// NAMESPACE //
///////////////

ProjectView::ProjectView()
{
}

ProjectView::ProjectView(const ProjectView& other)
{
}

ProjectView::~ProjectView()
{
}

bool ProjectView::Create()
{
	// Call the super
	if (!UIView::Create())
	{
		return false;
	}

	// Get our color component
	UIColorComponent* colorComponent = FindComponent<UIColorComponent>();

	// Set our color
	colorComponent->SetColor(Vector4(0.1, 0.1, 0.1, 1.0));

	// Create our explorer view
	m_ExplorerView = UIBase::CreateWidget<ProjectExplorerView, UIRelativeFrameComponent, UICommandComponent>(this);

	// Get the components
	UIRelativeFrameComponent* explorerFrameComponent = m_ExplorerView->FindComponent<UIRelativeFrameComponent>();
	UIColorComponent* explorerColorComponent = m_ExplorerView->FindComponent<UIColorComponent>();
	UIBorderComponent* explorerBorderComponent = m_ExplorerView->FindComponent<UIBorderComponent>();

	// Set the frame data
	explorerFrameComponent->SetFrame(Vector2(0.8, 0), Vector2(0.2, 1.0));

	// Set the color (DEBUG)
	explorerColorComponent->SetColor(Vector4(0.4, 0.4, 0.4, 1.0));

	return true;
}

void ProjectView::SetProjectDataReference(ProjectData* _projectData)
{
	m_ProjectData = _projectData;
}

bool ProjectView::ProcessCommand(CommandType* _command)
{
	// Call the super
	UIView::ProcessCommand(_command);

	// Mouse right click
	if (_command->actor == CommandActor::Mouse && _command->action == CommandAction::Press && _command->button == CommandButton::Right)
	{
		// Third box
		UIProgrammingBox* thirdProgrammingBox = UIBase::CreateWidget<UIProgrammingBox, UIFrameComponent, UIMovableCommandComponent>(this);
		UIFrameComponent* thirdProgrammingFrameComponent = thirdProgrammingBox->FindComponent<UIFrameComponent>();
		UIStateComponent* secondthirdProgrammingStateComponent = thirdProgrammingBox->FindComponent<UIStateComponent>();
		thirdProgrammingFrameComponent->SetFrame(Vector2(_command->firstParam - 150, _command->secondParam - 50), Vector2(300, 100));
	}

	return true;
}

void ProjectView::ModelChangedAlert()
{

}