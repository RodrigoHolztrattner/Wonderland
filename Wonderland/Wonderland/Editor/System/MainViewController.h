////////////////////////////////////////////////////////////////////////////////
// Filename: MainViewController.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\Foundation\UI\UI.h"
#include "MainInfoView.h"
#include "MainMenu.h"
#include "Project\ProjectView.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

/*

	- *Uma Programming Grid possui dados pois é uma classe.
	- *Uma Programming Box possui dados pois é uma função no mínimo.
	- Um projeto é carregado e possui dados.
	- *Uma view com os arquivos do projeto faz relação com os dados do projeto.
	- Dados de usuário utilizam dados sensíveis também.

	=> Estruturação

		- UserData seria um MVC_Model.
		- O menu principal seria uma MVC_View e faria subscribe no UserData.
		- O menu se atualiza com os dados do UserData.
		- Outras views também fazem subscribe no UserData, estas então recebem o evento de alteração, e se atualizam de acordo...
		- Os dados de um projeto é um MVC_Model, as classes (ProgrammingGrid's) são (?) outros MVC_Model's que ficam dentro do primeiro (?).
		- ProgrammingBox'es são MVC_View's e dão subscribe em um MVC_Model referente à função que estaremos trabalhando.

		- **** Talvez precisa de um contador de referencia para o model, tem que ver como faremos com as mensagens de delete (recebida por uma view e passada para o model e
		depois repassada para as outras vies causando a deleção do model (usar unsubscribe?). *****
		
*/

//
class UITextField;

////////////////////////////////////////////////////////////////////////////////
// Class name: MainViewController
////////////////////////////////////////////////////////////////////////////////
class MainViewController : public ViewController
{
//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
public: //////////////////////

	// Constructor / Destructor
	MainViewController();
	~MainViewController();

////////////////////
// INITIALIZATION //
public: ////////////

	// Initialize the graphic system
	virtual bool Initialize();

	// Frame update callback
	virtual void FrameUpdate(double _time);

	// Build the interface
	bool BuildInterface();

///////////////
// CALLBACKS //
protected: ////

	// Key callback
	virtual void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

	// Mouse button callback
	virtual void MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods);

///////////////
// VARIABLES //
private: //////

	// The main info view
	MainInfoView* m_MainInfoView;

	// The main menu
	MainMenu* m_MainMenu;

	// The project view
	ProjectView* m_ProjectView;
};