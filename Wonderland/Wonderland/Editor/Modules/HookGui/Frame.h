////////////////////////////////////////////////////////////////////////////////
// Filename: Frame.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "Anchor.h"
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

////////////////////////////////////////////////////////////////////////////////
// Class name: Frame
////////////////////////////////////////////////////////////////////////////////
struct Frame
{
    Frame() : x(0), y(0), width(0), height(0){}
    Frame(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height){};
    
    // Check if a point is inside this frame
    bool PointIsInside(float _x, float _y)
    {
        // Bounds check
        if(_x < x || _x >= (x + width) || _y < y || _y >= (y + height))
        {
            return false;
        }
        
        return true;
    }
    
    // The main data
    float x, y, width, height;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FrameHolder
////////////////////////////////////////////////////////////////////////////////
class FrameHolder
{

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FrameHolder();
	~FrameHolder();
    
//////////////////
// MAIN METHODS //
//////////////////
    
    // Change the frame value
    void ChangeFrame(HookGui::Frame _newFrame);
    
    // Return the frame value
    HookGui::Frame GetFrame();
    
////////////
// ANCHOR //
public: ////
    
    // Add an anchor to this frame
    void AddAnchor(Frame* _targetFrame, HookGui::Anchor::Policy _policy, HookGui::Anchor::Modifier _modifier);

    // Detach all anchors that use the given frame object (delete/remove/destroy)
    void DetachAllAnchors(Frame* _frame);
    
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
public: //////
    
    // The current frame
    HookGui::Frame m_CurrentFrame;
    
    // The frame bounds
    HookGui::Frame m_Bounds;
    
    // The frame center
    HookGui::Point m_Center;
    
private:
    
    // All the other frame objects that use our frame
    std::vector<FrameHolder*> m_ReferencingFrameObjects;
    
    // All the anchor objects
    std::vector<Anchor> m_Anchors;
};

// HookGui workspace
NamespaceEnd(HookGui)
