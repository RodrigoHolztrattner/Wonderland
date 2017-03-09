////////////////////////////////////////////////////////////////////////////////
// Filename: Anchor.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include <vector>
#include <string>

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

class Frame;
class FrameHolder;

////////////////////////////////////////////////////////////////////////////////
// Class name: Anchor
////////////////////////////////////////////////////////////////////////////////
class Anchor
{
    // Frame and FrameHolder are friend classes
    friend Frame;
    friend FrameHolder;
    
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
	Anchor();
	~Anchor();

//////////////////
// MAIN METHODS //
public: //////////
    
    // Create this anchor
    void CreateAnchor(Frame* _currentFrame, Frame* _targetFrame, HookGui::Anchor::Policy _policy, HookGui::Anchor::Modifier _modifier);
    
    // Apply this anchor
    void Apply();
    
    // Return the controller frame component
    // UIFrameComponent* GetControllerFrameComponent();
    
    // Move the frame component to the anchor point
    void MoveToAnchorPoint();
    
    // Scale the frame component to the anchor point
    void ScaleToAnchorPoint();
    
    // Pin the frame component to the anchor point
    void PinToAnchorPoint();
    
    // Move pin the frame component to the anchor point
    void MovePinToAnchorPoint();
    
    
    ///////////////
// VARIABLES //
private: //////
  
    // The current frame
    HookGui::Frame* m_CurrentFrame;
    
    // The policy used
    Policy m_Policy;
    
    // The modifier
    Modifier m_Modifier;
    
    // The target frame value (used to check if we should update)
    HookGui::Frame* m_TargetFrame;
};

// HookGui workspace
NamespaceEnd(HookGui)
