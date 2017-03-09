////////////////////////////////////////////////////////////////////////////////
// Filename: MainInfoView.cpp
////////////////////////////////////////////////////////////////////////////////
#include "MainInfoView.h"

///////////////
// NAMESPACE //
///////////////

MainInfoView::MainInfoView()
{
}

MainInfoView::MainInfoView(const MainInfoView& other)
{
}

MainInfoView::~MainInfoView()
{
}

bool MainInfoView::Create()
{
	// Call the super
	if (!UIView::Create())
	{
		return false;
	}

	//////////////
	// OUR DATA //
	//////////////

	// Get our components
	UIRelativeFrameComponent* relativeFrameComponent = FindComponent<UIRelativeFrameComponent>();
	UITreeComponent* treeComponent = FindComponent<UITreeComponent>();
	UIStateComponent* stateComponent = FindComponent<UIStateComponent>();
	UIBorderComponent* borderComponent = FindComponent<UIBorderComponent>();
	UIFrameComponent* frameComponent = relativeFrameComponent;

	// Set our border color
	borderComponent->SetBorderColor(Vector4(0.15, 0.15, 0.15, 1.0));

	// Create a text component (info name) and set the dependencies
	UITextComponent* textComponent = ECS_System<UITextComponent>::Create();
	textComponent->RegisterDependency(frameComponent);
	textComponent->RegisterDependency(stateComponent);

	// Set our text data
	textComponent->SetFontType("segoeui.ttf", 10);
	textComponent->SetText("    Wonderland (Running) - Engine");
	textComponent->SetTextColor(Vector4(0.6, 0.6, 0.6, 1.0));
	textComponent->SetFormatation(UIString::HorizontalFormatation::LeftAlign, UIString::VerticalFormatation::Centralized);

	// Add the text component
	AddComponent(textComponent);

	///////////////////
	// FPS INDICATOR //
	///////////////////

	// Create the fps indicator
	m_FPSIndicator = UIBase::CreateWidget<UITextField, UIFrameComponent, UICommandComponent>(this);

	// Get the fps indicator components
	UIFrameComponent* fpsInficatorFrameComponent = m_FPSIndicator->FindComponent<UIFrameComponent>();
	UITreeComponent* fpsIndicatorTreeComponent = m_FPSIndicator->FindComponent<UITreeComponent>();
	UIBorderComponent* fpsBorderComponent = m_FPSIndicator->FindComponent<UIBorderComponent>();
	UIColorComponent* fpsColorComponent = m_FPSIndicator->FindComponent<UIColorComponent>();
	UITextComponent* fpsTextComponent = m_FPSIndicator->FindComponent<UITextComponent>();

	// Set some component data
	fpsTextComponent->SetFontType("segoeui.ttf", 10);
	fpsColorComponent->SetColor(Vector4(0.15, 0.15, 0.15, 1));
	fpsBorderComponent->SetBorderColor(Vector4(0.15, 0.15, 0.15, 1));
	fpsInficatorFrameComponent->SetFrame(Vector2(800, 0), Vector2(120, 30));

	// Create the fps indicator anchor
	UIAnchorComponent* fpsAnchor = ECS_System<UIAnchorComponent>::Create();
	fpsAnchor->RegisterDependency(fpsInficatorFrameComponent);
	fpsAnchor->RegisterDependency(fpsIndicatorTreeComponent);
	fpsAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::TopAlign, UIAnchorComponent::Modifier::MovePin);
	fpsAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::BottomAlign, UIAnchorComponent::Modifier::Pin);
	fpsAnchor->AddAnchor(frameComponent, UIAnchorComponent::Policy::RightAlign, UIAnchorComponent::Modifier::MovePin);

	// Add the anchor component
	m_FPSIndicator->AddComponent(fpsAnchor);

	return true;
}

void MainInfoView::UpdateFrameRate(float _frametime, float _framerate)
{
	// Set the fps text
	UITextComponent* fpsIndicatorTextComponent = m_FPSIndicator->FindComponent<UITextComponent>();
	fpsIndicatorTextComponent->SetText(std::to_string((int)_framerate).append(" | ").append(std::to_string(_frametime)));
}

bool MainInfoView::ProcessCommand(CommandType* _command)
{
	// Call the super
	UIView::ProcessCommand(_command);

	return true;
}
