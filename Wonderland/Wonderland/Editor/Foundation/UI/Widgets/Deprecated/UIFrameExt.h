////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrame.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Support\Math\Math.h"
#include "UIFrameAnchor.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

/*

-> The window dimension

(0, 0)
(x, y)
_________________________________
|								|
|								|
|								|
|								|
|								|
|								|
|_______________________________|
(width, height)
(screenW, screenH)



*/

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
		Vector2 position;
		Vector2 size;
	};

public:
	UIFrame(UIBase* _self);
	UIFrame(const UIFrame&);
	~UIFrame();

	///////////////
	// UTILITIES //
	///////////////

	// Check if a given point is inside this object
	inline bool PointIsInsideFrame(Vector2 _point)
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

	// Rebuild the frame data
	void RebuildFrame();

	// Set the horizontal and vertical placements
	void SetPlacement(UIFrame::Horizontal _horizontal, UIFrame::Vertical _vertical);


protected:

	// Return the rebuild version
	unsigned int GetRebuildVersion() { return m_RebuildVersion; }

	// Called when we did a rebuld
	virtual void RebuildCallback() {}

	// Set the positon
	void SetFramePosition(Vector2 _position)
	{
		m_CurrentFrame.position = _position;
	}

	// Set the frame size
	void SetFrameSize(Vector2 _size)
	{
		m_CurrentFrame.size = _size;
	}

private:

	// Check if this frame need to be rebuild
	void NeedRebuild();

private:

	// The self UIBase object
	UIBase* m_Self;

	// The current and the screen space frames
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