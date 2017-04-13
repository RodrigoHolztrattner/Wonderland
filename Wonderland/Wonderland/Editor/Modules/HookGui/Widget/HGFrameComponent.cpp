////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFrame.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGFrameComponent.h"
#include "..\HGWidget.h"

HookGui::HGFrameComponent::HGFrameComponent(HGWidget* _selfWidgetReference)
{
	// Set the initial data
    m_CurrentFrame = HookGui::HGFrame(0, 0, 200, 100);
    m_Bounds = HookGui::HGFrame(0, 0, 200, 100);
	m_IsDirty = true;
	m_SelfWidget = _selfWidgetReference;
}

HookGui::HGFrameComponent::~HGFrameComponent()
{
}

void HookGui::HGFrameComponent::SetFrame(HookGui::HGFrame _newFrame)
{
    // Set the current frame
    m_CurrentFrame = _newFrame;

	// Apply all anchors
	ApplyAllAnchors();

	// For each referencing frame objects
	for (auto& frameObject : m_ReferencingFrameObjects)
	{
		// Dirty flag this frame object
		frameObject.second.targetWidget->DirtyFlag();
	}
}

HookGui::HGFrame HookGui::HGFrameComponent::GetFrame(bool _validade)
{
	// Validate this frame
	if(_validade) ValidateFrame();

    return m_CurrentFrame;
}

void HookGui::HGFrameComponent::ValidateFrame()
{
	// If we are dirty
	if (m_IsDirty)
	{
		// Apply all anchors
		ApplyAllAnchors();

		// Not dirty anymore
		m_IsDirty = false;
	}
}

void HookGui::HGFrameComponent::RegisterReference(HGWidget* _fromComponent)
{
	// Increment the total number of references for this identifier
	FrameLinkReference& linkReference = m_ReferencingFrameObjects[_fromComponent->GetIdentifier()];
	linkReference.targetWidget = _fromComponent;
	linkReference.totalReferences++;
}

void HookGui::HGFrameComponent::AddAnchor(HGWidget* _targetWidget, HGAnchor::Policy _policy, HGAnchor::Modifier _modifier)
{
    // Create a new anchor object
    HGAnchor newAnchor; newAnchor.CreateAnchor(this, _targetWidget, _policy, _modifier);
    
    // Add the anchor
    m_Anchors.push_back(newAnchor);
    
    // Flag as dirty
	DirtyFlag();

	// Make the target widget register a references
	_targetWidget->RegisterReference(m_SelfWidget);
}

void HookGui::HGFrameComponent::AddAnchor(HGFrame _targetPosition, HGAnchor::Policy _policy, HGAnchor::Modifier _modifier)
{
	// Create a new anchor object
	HGAnchor newAnchor; newAnchor.CreateAnchor(this, _targetPosition, _policy, _modifier);

	// Add the anchor
	m_Anchors.push_back(newAnchor);

	// Flag as dirty
	DirtyFlag();
}

void HookGui::HGFrameComponent::RemoveAnchorsForWidget(HGWidget* _targetWidget) //TODO: Ver se a lógica aqui faz sentido
{
	// For each anchor
	for (int i = 0; i < m_Anchors.size(); i++)
	{
		// Get the current anchor
		HGAnchor& anchor = m_Anchors[i];

		// Compare the identifiers
		if (anchor.GetTargetWidget()->GetIdentifier() == _targetWidget->GetIdentifier())
		{
			// Remove this element
			m_Anchors.erase(m_Anchors.begin() + i);

			i--;
		}
	}

	// Find the referencing link
	auto& it = m_ReferencingFrameObjects.find(_targetWidget->GetIdentifier());

	// Remove the referencing link
	m_ReferencingFrameObjects.erase(it);
}

void HookGui::HGFrameComponent::DetachAllAnchors(HGFrame* _frame) //TODO: Ver se a lógica aqui faz sentido
{
    // For each anchor
    for(int i=0; i<m_Anchors.size(); i++)
    {
		/* DESCOMENTAR ISSO
        // Compare the frame target
        if(m_Anchors[i].m_TargetFrame == _frame)
        {
            // Get the anchor
            // HookGui::Anchor currentAnchor = m_Anchors[i];
            
            // Remove this anchor
            m_Anchors.erase(m_Anchors.begin() + i);
        }
		*/
    }
}

void HookGui::HGFrameComponent::ApplyAllAnchors()
{
    // For each anchor
    for(auto anchor : m_Anchors)
    {
        // Apply this anchor
        anchor.Apply();
    }
}