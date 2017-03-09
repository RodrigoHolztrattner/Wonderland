////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrame.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Support\Math\Math.h"
#include "..\..\..\Support\Container\Array\Array.h"
#include "UIFrameAnchor.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

// We know the UIBase class
class UIBase;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIFrame
////////////////////////////////////////////////////////////////////////////////
class UIFrame
{
	// The UIFrameAnchor is a friend class
	friend UIFrameAnchor;

public:
	// The horizontal placement
	enum class Horizontal
	{
		Right,
		Left,
		Center
	};

	// The vertical placement
	enum class Vertical
	{
		Top,
		Bottom,
		Center
	};

	// The frame type
	struct WidgetFrame
	{
		WidgetFrame() {}
		WidgetFrame(Vector2 _position, Vector2 _size)
		{
			position = _position;
			size = _size;
		}

		Vector2 position;
		Vector2 size;
	};

public:
	UIFrame(UIBase* _self);
	UIFrame(const UIFrame&);
	~UIFrame();

//////////////
// INTERNAL //
protected: ///

	// Initialize the frame module
	bool InitializeFrameModule();

	// Release the frame module
	void ReleaseFrameModule();

	// Update this frame object
	void UpdateFrame();

////////////
// ANCHOR //
public: ////

	// Add a new anchor
	void AddFrameAnchor(UIFrameAnchor* _anchor) { m_Anchors.Add(_anchor); }

//////////////////////
// FRAME MANAGEMENT //
public: //////////////

	// Set the frame
	void SetFrame(UIFrame::WidgetFrame _frame) { m_OriginalFrame = m_CurrentFrame = _frame; }

	// Return the frame
	UIFrame::WidgetFrame GetFrame() { return m_CurrentFrame; }

	// Return the screen frame
	WidgetFrame GetScreenFrame() { return m_ScreenFrame; }

protected:

	// Set the horizontal and vertical placements
	void SetPlacement(UIFrame::Horizontal _horizontal, UIFrame::Vertical _vertical);

	// Set the frame positon
	void SetFramePosition(Vector2 _position){m_CurrentFrame.position = _position;}

	// Get the frame position
	Vector2 GetFramePosition() { return m_CurrentFrame.position; }

	// Set the frame size
	void SetFrameSize(Vector2 _size){m_CurrentFrame.size = _size;}

	// Get the frame size
	Vector2 GetFrameSize() { return m_CurrentFrame.size; }

/////////////
// REBUILD //
private: ////

	// Rebuild the frame data
	void RebuildFrame();

	// Return the rebuild version
	unsigned int GetRebuildVersion() { return m_RebuildVersion; }

private:

	// Check if this frame need to be rebuild
	void NeedRebuild();

//////////////
// CALLBACK //
protected: ///

	// Called when we did a rebuld
	virtual void RebuildCallback() {}

///////////////
// UTILITIES //
public: ///////

	// Check if a given point is inside this object
	bool PointIsInsideFrame(Vector2 _point)
	{
		// Check if this frame object need to be rebuilt
		NeedRebuild();

		// Get the current position and size
		Vector2 position = m_CurrentFrame.position;
		Vector2 size = m_CurrentFrame.size;

		// Rectangle bound check
		if (_point.x < position.x || _point.y < position.y || _point.x >(position.x + size.width) || _point.y >(position.y + size.height))
		{
			return false;
		}

		return true;
	}

///////////////
// VARIABLES //
private: //////

	// The self UIBase object
	UIBase* m_Self;

	// The original, current and the screen space frames
	WidgetFrame m_OriginalFrame;
	WidgetFrame m_CurrentFrame;
	WidgetFrame m_ScreenFrame;

	// The anchor array
	Array<UIFrameAnchor*> m_Anchors;

	





	// The horizontal and vertical placements
	UIFrame::Horizontal m_HorizontalPlacement;
	UIFrame::Vertical m_VerticalPlacement;

	// The rebuild version and the parent rebuild version
	unsigned int m_RebuildVersion;
	unsigned int m_ParentRebuildVersion;
};