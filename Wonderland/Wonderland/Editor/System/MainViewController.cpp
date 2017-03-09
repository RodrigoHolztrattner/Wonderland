////////////////////////////////////////////////////////////////////////////////
// Filename: MainViewController.cpp
////////////////////////////////////////////////////////////////////////////////
#include "MainViewController.h"
#include "..\Foundation\Context\Context.h"

////////////
// GLOBAL //
////////////

///////////
// LOCAL //
///////////

MainViewController::MainViewController()
{
}

MainViewController::~MainViewController()
{
}

/*
__________________________________________________

usar talvez o MVC aqui, mas mudar os nomes por favor porque ta tudo bem complicado
usar nomes decentes para o Model, não preciso usar tipo "menu model" ou "explorer model" pode ser algo geral, no caso da explorer vai ser uma das classes de dados
na real, o ideal aqui é começar a criar as classes de dados, pelo menos a base delas...

__________________________________________________

problema:

-> Criar uma classe "main" separada que vai gerenciar todos os widgets (essa atual?)
primeiro que a "lotação" da janela deve ser criada em uma classe separada, pode ser aqui na main view controller talvez
precisamos criar aqui a area do projeto, a explorer view, a debug view e assim por diante...
não devemos seguir o padrão arvore e ir descendo nas dependências, melhor colocar tudo aqui e separar talvez por dados(?)

precisamos pensar como tudo vai se relacionar com tudo, talvez usando uma referência(?)

criar a debug view

modificar os nomes(?) ta meio estranho usar MainBlabla e ProjectBlabla

*/

bool MainViewController::Initialize()
{
	// Call the super
	if (!ViewController::Initialize())
	{
		return false;
	}

	// Get the main frame components
	UIFrameComponent* mainFrameComponent = m_MainView->FindComponent<UIFrameComponent>();
	UIStateComponent* mainStateComponent = m_MainView->FindComponent<UIStateComponent>();

	///////////////
	// INFO VIEW //
	///////////////
	
	// Create the main info view
	m_MainInfoView = UIBase::CreateWidget<MainInfoView, UIRelativeFrameComponent>(m_MainView);

	// Get the frame and tree components and set the frame component
	UIRelativeFrameComponent* infoViewRelativeFrameComponent = m_MainInfoView->FindComponent<UIRelativeFrameComponent>();
	UITreeComponent* infoViewTreeComponent = m_MainInfoView->FindComponent<UITreeComponent>();
	UIFrameComponent* infoViewFrameComponent = infoViewRelativeFrameComponent;
	infoViewRelativeFrameComponent->SetFrame(Vector2(0, 0), Vector2(1, 30), UIRelativeFrameComponent::Restriction::Height);

	// Create our anchor
	UIAnchorComponent* infoViewAnchor = ECS_System<UIAnchorComponent>::Create();
	infoViewAnchor->RegisterDependency(infoViewFrameComponent);
	infoViewAnchor->RegisterDependency(infoViewTreeComponent);
	infoViewAnchor->AddAnchor(mainFrameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::MovePin);
	infoViewAnchor->AddAnchor(mainFrameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::MovePin);

	// Add the anchor component
	m_MainInfoView->AddComponent(infoViewAnchor);

	///////////////
	// MAIN MENU //
	///////////////

	// Create the main menu
	m_MainMenu = UIBase::CreateWidget<MainMenu, UIRelativeFrameComponent, UICommandComponent>(m_MainView);

	// get the frame and tree components and set the frame component
	UIRelativeFrameComponent* menuRelativeFrameComponent = m_MainMenu->FindComponent<UIRelativeFrameComponent>();
	UITreeComponent* menuTreeComponent = m_MainMenu->FindComponent<UITreeComponent>();
	UIFrameComponent* menuFrameComponent = menuRelativeFrameComponent;
	menuRelativeFrameComponent->SetFrame(Vector2(0, 0), Vector2(1, 20), UIRelativeFrameComponent::Restriction::Height);

	// Create the menu anchor
	UIAnchorComponent* menuAnchor = ECS_System<UIAnchorComponent>::Create();
	menuAnchor->RegisterDependency(menuFrameComponent);
	menuAnchor->RegisterDependency(menuTreeComponent);
	menuAnchor->AddAnchor(infoViewFrameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::Move);
	menuAnchor->AddAnchor(infoViewFrameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::MovePin);

	// Add the anchor component
	m_MainMenu->AddComponent(menuAnchor);

	//////////////////
	// PROJECT VIEW //
	//////////////////

	
	// Create the project view
	m_ProjectView = UIBase::CreateWidget<ProjectView, UIRelativeFrameComponent, UICommandComponent>(m_MainView);

	// Get the frame and tree components and set the frame component
	UIRelativeFrameComponent* projectRelativeFrameComponent = m_ProjectView->FindComponent<UIRelativeFrameComponent>();
	UITreeComponent* projectTreeComponent = m_ProjectView->FindComponent<UITreeComponent>();
	UIFrameComponent* projectFrameComponent = menuRelativeFrameComponent;
	projectRelativeFrameComponent->SetFrame(Vector2(0, 0), Vector2(1, 0.8));

	// Create the project anchor
	UIAnchorComponent* projectAnchor = ECS_System<UIAnchorComponent>::Create();
	projectAnchor->RegisterDependency(projectFrameComponent);
	projectAnchor->RegisterDependency(projectTreeComponent);
	projectAnchor->AddAnchor(menuFrameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::Move);
	projectAnchor->AddAnchor(menuFrameComponent, UIAnchorComponent::Policy::LeftAlign, UIAnchorComponent::Modifier::MovePin);

	// Add the anchor component
	m_ProjectView->AddComponent(projectAnchor);
	
	// Start updatind
	StartUpdating();

	return true;
}

void MainViewController::FrameUpdate(double _time)
{
	// Call the super
	ViewController::FrameUpdate(_time);

	static unsigned int UpdateID = 0;
	static float accTime = 0;
	static int fpsCounter = 0;

	/////////
	// FPS //
	/////////

	// Increment the time and the counter
	accTime += _time;
	fpsCounter++;

	// Check the second val
	if (accTime >= 1)
	{
		// Set the fps text
		m_MainInfoView->UpdateFrameRate(accTime / fpsCounter, fpsCounter);

		// Set the new time and zero the counter
		accTime -= 1;
		fpsCounter = 0;
	}

	/////////
	/////////
	/////////
}

void MainViewController::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	// Call the super
	ViewController::KeyCallback(_window, _key, _scancode, _action, _mods);
}

void MainViewController::MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods)
{
	// Call the super
	ViewController::MouseButtonCallback(_window, _button, _action, _mods);
}