////////////////////////////////////////////////////////////////////////////////
// Filename: HGAnchor.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include <vector>
#include <string>
#include "Widget\HGFrame.h"
#include "Widget\HGFrame.h"

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
class HGFrameComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: HGAnchor
////////////////////////////////////////////////////////////////////////////////
class HGAnchor
{

	// The mode
	enum class Mode
	{
		WidgetAnchor,
		PositionAnchor
	};
    
////////////
// POLICY //
public: ////
    
    // The policy type
    enum class Policy
    {
        TopAlign,
        RightAlign,
        BottomAlign,
        LeftAlign
    };
    
    // The modifier type
    enum class Modifier
    {
        Move,
        Scale,
        Pin,
        MovePin
    };

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGAnchor();
	~HGAnchor();

//////////////////
// MAIN METHODS //
public: //////////
    
    // Create this anchor
    void CreateAnchor(HGFrameComponent* _currentWidget, HGWidget* _targetWidget, HookGui::HGAnchor::Policy _policy, HookGui::HGAnchor::Modifier _modifier);
	void CreateAnchor(HGFrameComponent* _currentWidget, HGFrame _targetFrame, HookGui::HGAnchor::Policy _policy, HookGui::HGAnchor::Modifier _modifier);

    // Apply this anchor
    void Apply();
    
    // Move the frame component to the anchor point
    void MoveToAnchorPoint();
    
    // Scale the frame component to the anchor point
    void ScaleToAnchorPoint();
    
    // Pin the frame component to the anchor point
    void PinToAnchorPoint();
    
    // Move pin the frame component to the anchor point
    void MovePinToAnchorPoint();
    
	// Return the target widget
	HGWidget* GetTargetWidget() { return m_TargetWidget; }
    
///////////////
// VARIABLES //
protected: ////

	// Our current mode
	Mode m_OperationMode;
  
	// The policy used
	Policy m_Policy;

	// The modifier
	Modifier m_Modifier;

	// The current widget
	HGFrameComponent* m_CurrentWidget;

	// The target widget (only usable in widget mode)
	HGWidget* m_TargetWidget;

	// The target position (only usable in position mode)
	HookGui::HGFrame m_TargetPosition;

private:

	// The current frame
	HookGui::HGFrame m_CurrentFrame;

	// The target frame value
	HookGui::HGFrame m_TargetFrame;
};

// HookGui workspace
NamespaceEnd(HookGui)
