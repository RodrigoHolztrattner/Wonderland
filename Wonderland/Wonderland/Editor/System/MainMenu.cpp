////////////////////////////////////////////////////////////////////////////////
// Filename: MainMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "MainMenu.h"

///////////////
// NAMESPACE //
///////////////

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(const MainMenu& other)
{
}

MainMenu::~MainMenu()
{
}

bool MainMenu::Create()
{
	// Call super
	if (!UIMenu::Create())
	{
		return false;
	}

	// Get our components
	UIRelativeFrameComponent* frameComponent = FindComponent<UIRelativeFrameComponent>();
	UITreeComponent* freeComponent = FindComponent<UITreeComponent>();

	// Add the buttons
	AddButton("File");
	AddButton("Edit");
	AddButton("View");
	UIMenuButton* projectButton = AddButton("Project");
	AddButton("Build");
	AddButton("Debug");
	AddButton("Team");
	AddButton("vMicro");
	AddButton("Tools");
	AddButton("Test");
	AddButton("Analyze");
	AddButton("Window");
	AddButton("Help");

	//
	UIMenuLaneView* projectLaneview = projectButton->CreateLaneview();

	// Add more button
	projectLaneview->AddButton("teste1");
	projectLaneview->AddButton("teste2");
	UIMenuButton* selectButton3 = projectLaneview->AddButton("teste3");
	projectLaneview->AddButton("teste4");
	projectLaneview->AddButton("teste5");

	//
	UIMenuLaneView* select3LaneView = selectButton3->CreateLaneview();

	// Add moar button
	select3LaneView->AddButton("teste1");
	UIMenuButton* selectFarButton2 = select3LaneView->AddButton("teste2");

	//
	UIMenuLaneView* selectFar2LaneView = selectFarButton2->CreateLaneview();

	// Moar moar buttons
	selectFar2LaneView->AddButton("teste1");
	selectFar2LaneView->AddButton("teste2");
	selectFar2LaneView->AddButton("teste3");

	return true;
}

bool MainMenu::ProcessCommand(CommandType* _command)
{
	// Call super
	UIMenu::ProcessCommand(_command);

	return true;
}
