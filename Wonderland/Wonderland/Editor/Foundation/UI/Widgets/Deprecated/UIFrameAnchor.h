////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrameAnchor.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Support\Math\Math.h"

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

// We know the UIFrame class
class UIFrame;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIFrameAnchor
////////////////////////////////////////////////////////////////////////////////
class UIFrameAnchor
{
public:

	// The policy type
	enum class Policy
	{
		TopAlign,
		RightAlign,
		BottomAlign,
		LeftAlign,
		TopScale,
		RightScale,
		BottomScale,
		LeftScale
	};

public:
public:
	UIFrameAnchor(Policy _policy, UIBase* _targetWidget);
	UIFrameAnchor(const UIFrameAnchor&);
	~UIFrameAnchor();

	// Release this anchor
	void Release();

	// Update
	void UpdateAnchor(UIBase* _mainWidget);

private:

	// Align adjust
	void TopAlignAdjust(UIBase* _mainWidget);
	void RightAlignAdjust(UIBase* _mainWidget);
	void BottomAlignAdjust(UIBase* _mainWidget);
	void LeftAlignAdjust(UIBase* _mainWidget);

	// Scale adjust
	void TopScaleAdjust(UIBase* _mainWidget);
	void RightScaleAdjust(UIBase* _mainWidget);
	void BottomScaleAdjust(UIBase* _mainWidget);
	void LeftScaleAdjust(UIBase* _mainWidget);

private:

	// The policy
	Policy m_Policy;

	// The linked object
	UIBase* m_LinkedObject;
};