////////////////////////////////////////////////////////////////////////////////
// Filename: ViewController.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ViewController.h"
#include "..\..\Context\Context.h"
#include "..\..\Shader\ShaderManager.h"

////////////
// GLOBAL //
////////////

///////////
// LOCAL //
///////////

ViewController::ViewController()
{
	// Set the initial data
	m_MainView = nullptr;
}

ViewController::~ViewController()
{
}

bool ViewController::Initialize()
{
	// Initialize all modules
	if (!InitializeModules())
	{
		return false;
	}

	// Create the main view
	m_MainView = UIBase::CreateWidget<UIView, UIFrameComponent, UICommandComponent>(nullptr);
	UIFrameComponent* mainFrameComponent = m_MainView->FindComponent<UIFrameComponent>();
	UIStateComponent* mainStateComponent = m_MainView->FindComponent<UIStateComponent>();
	mainFrameComponent->SetFrame(Vector2(0, 0), Vector2(Context::GetInstance()->GetScreenWidth(), Context::GetInstance()->GetScreenHeight()));
	mainStateComponent->SetIsRenderable(false);

	return true;
}

bool ViewController::InitializeModules()
{
	// Initialize the window module
	if (!m_WindowModule.Initialize())
	{
		return false;
	}

	// Set the window callback
	m_WindowModule.SetWindowCallback(this);

	// Initialize the command module
	if (!m_CommandModule.Initialize())
	{
		return false;
	}

	// Initialize the render module
	if (!m_RenderModule.Initialize())
	{
		return false;
	}

	return true;
}

void ViewController::Exit(void* _data)
{
	exit(0);
}

void ViewController::StartUpdating()
{
	// Initialize the frame update thread
	// m_UpdateThread = std::thread(&ViewController::FrameUpdateAux, this);
	FrameUpdateAux();

	// ...
	m_UpdateThread.join();
}

void ViewController::FrameUpdateAux()
{
	float currentTime = 0;

	// No fps cap
	glfwSwapInterval(0);
	
	while (!glfwWindowShouldClose(m_WindowModule.GetModuleWindow()))
	{
		// Clear the back buffer
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Enable depth
		// glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		// Get the frame time
		double frameTime = glfwGetTime();
		frameTime -= currentTime;
		currentTime = glfwGetTime();

		// Call the real frame update
		FrameUpdate(frameTime);

		// Call the render function for all shaders
		ShaderManager::ProcessGlobalRenderPhase();

		// Swap the buffers and poll all events
		glfwSwapBuffers(m_WindowModule.GetModuleWindow());
		glfwPollEvents();
	}
}

void ViewController::FrameUpdate(double _time)
{
	// Our update ID
	static unsigned int UpdateID = 0;

	// Get the mouse coordinates
	double xpos, ypos;
	glfwGetCursorPos(m_WindowModule.GetModuleWindow(), &xpos, &ypos);

	// Process the command module
	m_CommandModule.ProcessCommands(m_MainView, xpos, ypos);

	// Update all widget
	m_CommandModule.Update(m_MainView, _time, xpos, ypos);

	// Render all views
	m_RenderModule.Update(m_MainView, _time, UpdateID);

	// Update all component systems
	ECS_SystemManager::UpdateAllSystems(UpdateID, _time);

	// Increment the update ID
	UpdateID++;
}

void ViewController::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	static bool ShiftPressed = false;

	// Check for shift
	if (_key == 340)
	{
		// Set the shift status
		ShiftPressed = _action == GLFW_PRESS ? true : false;
		return;
	}

	// Set the new key code using the ctrl, shift and alt
	_key = ShiftPressed ? _key + 32 : _key;

	// Prepare the command
	CommandType newCommand = CommandType(CommandActor::Keyboard, (CommandAction)_action, _key, _mods);

	// Insert the new command into the command module
	m_CommandModule.RegisterCommand(newCommand);
}

void ViewController::MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods)
{
	// Get the mouse position
	double xpos, ypos;
	glfwGetCursorPos(m_WindowModule.GetModuleWindow(), &xpos, &ypos);

	// Prepare the command
	CommandType newCommand = CommandType(CommandActor::Mouse, (CommandAction)_action, (CommandButton)_button, xpos, ypos);

	// Insert the new command into the command module
	m_CommandModule.RegisterCommand(newCommand);
}