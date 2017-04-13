////////////////////////////////////////////////////////////////////////////////
// Filename: FluxAnchor.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGAnchor.h"
#include "Widget\HGFrame.h"
#include "Widget\HGFrameComponent.h"
#include "HGWidget.h"

HookGui::HGAnchor::HGAnchor()
{
	// Set the initial data
    // ...
}

HookGui::HGAnchor::~HGAnchor()
{
}

void HookGui::HGAnchor::CreateAnchor(HGFrameComponent* _currentWidget, HGWidget* _targetWidget, HookGui::HGAnchor::Policy _policy, HookGui::HGAnchor::Modifier _modifier)
{
	// Set the operation mode
	m_OperationMode = Mode::WidgetAnchor;

	// Set the other data
	m_Policy = _policy;
	m_Modifier = _modifier;
	m_CurrentWidget = _currentWidget;
	m_TargetWidget = _targetWidget;
}

void HookGui::HGAnchor::CreateAnchor(HGFrameComponent* _currentWidget, HGFrame _targetFrame, HookGui::HGAnchor::Policy _policy, HookGui::HGAnchor::Modifier _modifier)
{
	// Set the operation mode
	m_OperationMode = Mode::PositionAnchor;

	// Set the other data
	m_Policy = _policy;
	m_Modifier = _modifier;
	m_CurrentWidget = _currentWidget;
	m_TargetPosition = _targetFrame;
}

void HookGui::HGAnchor::Apply()
{
	// Check the operation mode
	if (m_OperationMode == Mode::WidgetAnchor)
	{
		// Set the target widget
		m_TargetFrame = m_TargetWidget->GetFrame(false);

		// Set the current frame
		m_CurrentFrame = m_CurrentWidget->GetFrame(false);
	}
	else if (m_OperationMode == Mode::PositionAnchor)
	{
		// Set the target widget
		m_TargetFrame = m_TargetPosition;

		// Set the current frame
		m_CurrentFrame = m_CurrentWidget->GetFrame(false);
	}

    // Check the modifier
    switch (m_Modifier)
    {
            // Move
        case Modifier::Move:
        {
            // Move to the anchor point
            MoveToAnchorPoint();
            
            break;
        }
            // Scale
        case Modifier::Scale:
        {
            // Scale to the anchor point
            ScaleToAnchorPoint();
            
            break;
        }
            // Pin
        case Modifier::Pin:
        {
            // Pin the frame component to the anchor point
            PinToAnchorPoint();
            
            break;
        }
            // Move pin
        case Modifier::MovePin:
        {
            // Move pin the frame component to the anchor point
            MovePinToAnchorPoint();
            
            break;
        }
    }
    
	// Get the frame reference
	HGFrame* frameReference = m_CurrentWidget->GetFrameReference();

    // Save the new frame value
	*frameReference = m_CurrentFrame;
}

void HookGui::HGAnchor::MoveToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame.y = m_TargetFrame.y + m_TargetFrame.height;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame.x = m_TargetFrame.x - m_CurrentFrame.width;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame.x = m_TargetFrame.x + m_TargetFrame.width;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame.y = m_TargetFrame.y - m_CurrentFrame.height;
            
            break;
        }
    }
}

void HookGui::HGAnchor::ScaleToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame.height = (m_CurrentFrame.y + m_CurrentFrame.height) - (m_TargetFrame.y + m_TargetFrame.height);
            m_CurrentFrame.y = m_TargetFrame.y + m_TargetFrame.height;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame.width = m_TargetFrame.x - m_CurrentFrame.x;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame.width = (m_CurrentFrame.x + m_CurrentFrame.width) - (m_TargetFrame.x + m_TargetFrame.width);
            m_CurrentFrame.x = m_TargetFrame.x + m_TargetFrame.width;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame.height = m_TargetFrame.y - m_CurrentFrame.y;
            
            break;
        }
    }
}

void HookGui::HGAnchor::PinToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame.height = (m_CurrentFrame.y + m_CurrentFrame.height) - (m_TargetFrame.y);
            m_CurrentFrame.y = m_TargetFrame.y;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame.width = (m_TargetFrame.x + m_TargetFrame.width) - m_CurrentFrame.x;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame.width = (m_CurrentFrame.x + m_CurrentFrame.width) - (m_TargetFrame.x);
            m_CurrentFrame.x = m_TargetFrame.x;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame.height = (m_TargetFrame.y + m_TargetFrame.height) - m_CurrentFrame.y;
            
            break;
        }
    }
}

void HookGui::HGAnchor::MovePinToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame.y = m_TargetFrame.y;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame.width = (m_TargetFrame.x + m_TargetFrame.width) - m_CurrentFrame.width;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame.x = m_TargetFrame.x;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame.height = (m_TargetFrame.y + m_TargetFrame.height) - m_CurrentFrame.height;
            
            break;
        }
    }
}

