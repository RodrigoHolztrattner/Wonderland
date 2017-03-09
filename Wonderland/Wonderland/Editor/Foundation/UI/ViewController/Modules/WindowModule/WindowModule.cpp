////////////////////////////////////////////////////////////////////////////////
// Filename: WindowModule.cpp
////////////////////////////////////////////////////////////////////////////////
#include "WindowModule.h"
#include "..\..\ViewController.h"
#include "..\..\..\..\Context\Context.h"

////////////
// GLOBAL //
////////////

static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Call the view controller callback
	static_cast<ViewController*>(glfwGetWindowUserPointer(window))->KeyCallback(window, key, scancode, action, mods);
}

static void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Call the view controller callback
	static_cast<ViewController*>(glfwGetWindowUserPointer(window))->MouseButtonCallback(window, button, action, mods);
}

///////////
// LOCAL //
///////////

WindowModule::WindowModule()
{
}

WindowModule::WindowModule(const WindowModule& other)
{
}

WindowModule::~WindowModule()
{
}

bool WindowModule::Initialize()
{
	// Check if we already initialized the opengl libraries
	static bool OpenGLInitialized = false;
	if (!OpenGLInitialized)
	{
		// Initialize the glfw
		if (!glfwInit())
		{
			return false;
		}
	}

	// Set the window frame
	m_WindowFrame.x = 0;
	m_WindowFrame.y = 0;
	m_WindowFrame.z = Context::GetInstance()->GetScreenWidth(); // 1920
	m_WindowFrame.w = Context::GetInstance()->GetScreenHeight(); // 1080

	// Create the main window
	m_Window = glfwCreateWindow(m_WindowFrame.z, m_WindowFrame.w, "Wonderland", NULL, NULL); // glfwGetPrimaryMonitor() // NULL // 
	if (!m_Window)
	{
		return false;
	}

	/*
	// Get the desktop resolution.
	GLFWmonitor* desktopMode = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(desktopMode);
	glfwGetVideoMode(desktopMode);

	int desktopHeight = mode->height;
	int desktopWidth = mode->width;

	glfwSetWindowSize(m_Window, desktopWidth, desktopHeight);
	glfwSetWindowPos(m_Window, 0, 0);
	*/

	// Set the full screen windowed mode
	// const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	// glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate

	// Set the current context
	glfwMakeContextCurrent(m_Window);
	
	// Check if we should initialize the glew lib
	if (!OpenGLInitialized)
	{
		// Initialize the glew
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			return false;
		}

		// Set that we initialized the opengl
		OpenGLInitialized = true;
	}

	return true;
}

void WindowModule::SetWindowCallback(ViewController* _viewController)
{
	// Set the user pointer
	glfwSetWindowUserPointer(m_Window, _viewController);

	// Set all callbacks
	glfwSetKeyCallback(m_Window, _key_callback);
	glfwSetMouseButtonCallback(m_Window, _mouse_button_callback);
}

void WindowModule::Shutdown()
{

}