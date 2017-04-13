////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWidgetController.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGWidgetManager.h"

HookGui::HGWidgetManager::HGWidgetManager()
{
	// Set the initial data
	// ...
}

HookGui::HGWidgetManager::~HGWidgetManager()
{
}

bool HookGui::HGWidgetManager::Initialize(VulkanWrapper::Context* _context)
{
	// Get the vulkan window
	VulkanWrapper::Window* vulkanWindow = _context->GetWindow();

	// Register the input dispatcher to receive input callbacks
	vulkanWindow->SetInputCallbackObject(&m_InputDispatcher);

	return true;
}

void HookGui::HGWidgetManager::Update(HGWidget* _mainWidget, float _timeElapsed)
{
	// Process all input commands
	m_InputController.ProcessInputCommands(_mainWidget, m_InputDispatcher);
}

void HookGui::HGWidgetManager::Render(HGWidget* _widget)
{
	// Check if this widget is hidden
	if (_widget->IsHidden())
	{
		return;
	}

	// Check if we should render this widget
	if (_widget->CanBeRendered())
	{
		// Render this widget
		// ...
	}

	// For each child
	const std::vector<HGWidget*>& childArray = _widget->GetChildArray();
	for (int i = 0; i < childArray.size(); i++)
	{
		// Try to render this child
		Render(childArray[i]);
	}
}