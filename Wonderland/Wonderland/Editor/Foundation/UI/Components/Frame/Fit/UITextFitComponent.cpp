////////////////////////////////////////////////////////////////////////////////
// Filename: UITextFitComponent.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UITextFitComponent.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UITextFitComponent::UITextFitComponent() : ECS_Component(ClassComponentID())
{
	// Set the initial data
	m_LastTextSize = Vector2(0, 0);
}

UITextFitComponent::UITextFitComponent(const UITextFitComponent& other) : ECS_Component(other)
{
}

UITextFitComponent::~UITextFitComponent()
{
}

///////////////
// MODIFIERS //
///////////////

#include "..\..\..\..\ECS\ECS_Entity.h"
#include "..\UIFrameComponent.h"
#include "..\..\Renderable\Text\UITextComponent.h"

/////////////
// VIRTUAL //
/////////////

void UITextFitComponent::Update(unsigned int _updateId, float _timeElapsed)
{
	// Get the frame and text components
	UIFrameComponent* frameComponent = GetEntityComponent<UIFrameComponent>();
	UITextComponent* textComponent = GetEntityComponent<UITextComponent>();

	// Get the text size
	Vector2 currentTextSize = Vector2(textComponent->GetMaxDimensionSize().width, 0);

	// Check if the size changed
	if (!m_LastTextSize.Compare(currentTextSize))
	{
		// Set the frame
		frameComponent->SetFrame(frameComponent->GetFrame(), Vector2(currentTextSize.x * 1.7, frameComponent->GetFrame().height));
		
		// Set the size
		m_LastTextSize.x = currentTextSize.x;
		m_LastTextSize.y = currentTextSize.y;
	}
}

void UITextFitComponent::Clear()
{

}
