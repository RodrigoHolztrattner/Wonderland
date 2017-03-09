////////////////////////////////////////////////////////////////////////////////
// Filename: FluxAnchor.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Anchor.h"
#include "Frame.h"

HookGui::Anchor::Anchor()
{
	// Set the initial data
    // ...
}

HookGui::Anchor::~Anchor()
{
}

void HookGui::Anchor::CreateAnchor(Frame* _currentFrame, Frame* _targetFrame, HookGui::Anchor::Policy _policy, HookGui::Anchor::Modifier _modifier)
{
    
}

void HookGui::Anchor::Apply()
{
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
    
    // Save the new frame value
    // ...
}

/*
UIFrameComponent* HookGui::Anchor::GetControllerFrameComponent(AnchorController _controller)
{
    // Check the controller type
    if (_controller.targetFrame == nullptr)
    {
        // Use parent frame //
        
        // Get the entity owner
        ECS_Entity* entity = GetEntityOwner();
        
        // Find the entity tree component
        UITreeComponent* treeComponent = entity->FindComponent<UITreeComponent>();
        
        // Get the entity parent tree component
        UITreeComponent* parentTreeComponent = treeComponent->GetParent();
        
        // Check if the parent is valid
        if (parentTreeComponent == nullptr)
        {
            // We are the root parent, we cant use an anchor
            return nullptr;
        }
        
        // Get the parent frame component
        return (UIFrameComponent*)parentTreeComponent->GetEntityComponentById(UIFrameComponent::ClassComponentID());
    }
    else
    {
        // Use target frame //
        
        // Get the target frame component
        return _controller.targetFrame;
    }
    
    // Will never happen
    return nullptr;
}
*/

void HookGui::Anchor::MoveToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame->y = m_TargetFrame->y + m_TargetFrame->height;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame->x = m_TargetFrame->x - m_CurrentFrame->width;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame->x = m_TargetFrame->x + m_TargetFrame->width;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame->y = m_TargetFrame->y - m_CurrentFrame->height;
            
            break;
        }
    }
}

void HookGui::Anchor::ScaleToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame->height = (m_CurrentFrame->y + m_CurrentFrame->height) - (m_TargetFrame->y + m_TargetFrame->height);
            m_CurrentFrame->y = m_TargetFrame->y + m_TargetFrame->height;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame->width = m_TargetFrame->x - m_CurrentFrame->x;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame->width = (m_CurrentFrame->x + m_CurrentFrame->width) - (m_TargetFrame->x + m_TargetFrame->width);
            m_CurrentFrame->x = m_TargetFrame->x + m_TargetFrame->width;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame->height = m_TargetFrame->y - m_CurrentFrame->y;
            
            break;
        }
    }
}

void HookGui::Anchor::PinToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame->height = (m_CurrentFrame->y + m_CurrentFrame->height) - (m_TargetFrame->y);
            m_CurrentFrame->y = m_TargetFrame->y;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame->width = (m_TargetFrame->x + m_TargetFrame->width) - m_CurrentFrame->x;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame->width = (m_CurrentFrame->x + m_CurrentFrame->width) - (m_TargetFrame->x);
            m_CurrentFrame->x = m_TargetFrame->x;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame->height = (m_TargetFrame->y + m_TargetFrame->height) - m_CurrentFrame->y;
            
            break;
        }
    }
}

void HookGui::Anchor::MovePinToAnchorPoint()
{
    // Check the policy type
    switch (m_Policy)
    {
            // Top
        case Policy::TopAlign:
        {
            // Set the frame
            m_CurrentFrame->y = m_TargetFrame->y;
            
            break;
        }
            // Right
        case Policy::RightAlign:
        {
            // Set the frame
            m_CurrentFrame->width = (m_TargetFrame->x + m_TargetFrame->width) - m_CurrentFrame->width;
            
            break;
        }
            // Left
        case Policy::LeftAlign:
        {
            // Set the frame
            m_CurrentFrame->x = m_TargetFrame->x;
            
            break;
        }
            // Bottom
        case Policy::BottomAlign:
        {
            // Set the frame
            m_CurrentFrame->height = (m_TargetFrame->y + m_TargetFrame->height) - m_CurrentFrame->height;
            
            break;
        }
    }
}

