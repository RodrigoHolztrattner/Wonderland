////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFrame.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Frame.h"

HookGui::FrameHolder::FrameHolder()
{
	// Set the initial data
    m_CurrentFrame = HookGui::Frame(0, 0, 200, 100);
    m_Bounds = HookGui::Frame(0, 0, 200, 100);
}

HookGui::FrameHolder::~FrameHolder()
{
}

void HookGui::FrameHolder::ChangeFrame(HookGui::Frame _newFrame)
{
    // Set the current frame
    m_CurrentFrame = _newFrame;
    
    // Apply all anchors
    ApplyAllAnchors();
}

HookGui::Frame HookGui::FrameHolder::GetFrame()
{
    return m_CurrentFrame;
}

void HookGui::FrameHolder::AddAnchor(Frame* _targetFrame, HookGui::Anchor::Policy _policy, HookGui::Anchor::Modifier _modifier)
{
    // Create a new anchor object
    Anchor newAnchor; newAnchor.CreateAnchor(&m_CurrentFrame, _targetFrame, _policy, _modifier);
    
    // Add the anchor
    m_Anchors.push_back(newAnchor);
    
    // Apply all anchors
    // ...
}

void HookGui::FrameHolder::DetachAllAnchors(Frame* _frame)
{
    // For each anchor
    for(int i=0; i<m_Anchors.size(); i++)
    {
        // Compare the frame target
        if(m_Anchors[i].m_TargetFrame == _frame)
        {
            // Get the anchor
            // HookGui::Anchor currentAnchor = m_Anchors[i];
            
            // Remove this anchor
            m_Anchors.erase(m_Anchors.begin() + i);
        }
    }
}

void HookGui::FrameHolder::ApplyAllAnchors()
{
    // For each anchor
    for(auto anchor : m_Anchors)
    {
        // Apply this anchor
        anchor.Apply();
    }
}
