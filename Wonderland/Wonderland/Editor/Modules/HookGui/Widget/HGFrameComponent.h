////////////////////////////////////////////////////////////////////////////////
// Filename: HGFrame.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\NamespaceDefinitions.h"
#include "HGFrame.h"
#include "..\HGAnchor.h"
#include <vector>
#include <string>
#include <map>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// HookGui workspace
NamespaceBegin(HookGui)

////////////////
// FORWARDING //
////////////////

class HGWidget;


////////////////////////////////////////////////////////////////////////////////
// Class name: HGFrameComponent
////////////////////////////////////////////////////////////////////////////////
class HGFrameComponent
{
	struct FrameLinkReference
	{
		FrameLinkReference() {};
		FrameLinkReference(HGFrameComponent* _targetWidget) : targetWidget(_targetWidget), totalReferences(0) {}

		// The target widget
		HGFrameComponent* targetWidget;

		// The number of references
		uint32_t totalReferences;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGFrameComponent(HGWidget* _selfWidgetReference);
	~HGFrameComponent();
    
//////////////////
// MAIN METHODS //
//////////////////
    
    // Set the frame value
    virtual void SetFrame(HookGui::HGFrame _newFrame);
    
    // Return the frame value
    HookGui::HGFrame GetFrame(bool _validade = true);

protected:

	friend HGAnchor;

	// Return our frame reference
	HookGui::HGFrame* GetFrameReference() { return &m_CurrentFrame; }

	// Validate this frame component
	void ValidateFrame();

	// Flag this widget as dirty
	void DirtyFlag(){ m_IsDirty = true; }

private:

	// Register a reference from another frame component
	void RegisterReference(HGWidget* _fromComponent);

////////////
// ANCHOR //
public: ////
    
    // Add an anchor to this frame
    void AddAnchor(HGWidget* _targetWidget, HGAnchor::Policy _policy, HGAnchor::Modifier _modifier);
	void AddAnchor(HGFrame _targetPosition, HGAnchor::Policy _policy, HGAnchor::Modifier _modifier);

	// Remove all anchors for widget
	void RemoveAnchorsForWidget(HGWidget* _targetWidget);

    // Detach all anchors that use the given frame object (delete/remove/destroy)
    void DetachAllAnchors(HGFrame* _frame);
    
private:
    
    // Apply all anchors
    void ApplyAllAnchors();
    
///////////
// UTILS //
public: ///

    // Check if a point is inside this frame
	bool PointIsInside(float _x, float _y) { return m_CurrentFrame.PointIsInside(_x, _y); }
    
///////////////
// VARIABLES //
protected: ////
    
    // The current frame
    HookGui::HGFrame m_CurrentFrame;
    
    // The frame bounds
    HookGui::HGFrame m_Bounds;
    
    // The frame center
    HookGui::Point m_Center;

	// If this frame component is dirty
	bool m_IsDirty;
    
private:

    // All the other frame objects that use our frame
    std::map<uint32_t, FrameLinkReference> m_ReferencingFrameObjects;
    
    // All the anchor objects
    std::vector<HGAnchor> m_Anchors;

	// Self widget reference
	HGWidget* m_SelfWidget;
};

// HookGui workspace
NamespaceEnd(HookGui)
