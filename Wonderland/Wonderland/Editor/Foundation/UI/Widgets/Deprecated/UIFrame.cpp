////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrame.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIFrame.h"
#include "UIBase.h"

///////////////
// NAMESPACE //
///////////////

UIFrame::UIFrame(UIBase* _self)
{
	// Set the self ptr
	m_Self = _self;

	// Set the initial data
	m_HorizontalPlacement = Horizontal::Left;
	m_VerticalPlacement = Vertical::Top;
	m_RebuildVersion = m_ParentRebuildVersion = 0;
}

UIFrame::UIFrame(const UIFrame& other)
{
}

UIFrame::~UIFrame()
{
}

bool UIFrame::InitializeFrameModule()
{

	return true;
}

void UIFrame::ReleaseFrameModule()
{
	// Release all anchors
	while (m_Anchors.Size())
	{
		// Release and delete this anchor
		m_Anchors[0]->Release();
		delete m_Anchors[0];
		m_Anchors.Remove(0);
	}
}

void UIFrame::UpdateFrame()
{
	// For each anchor, apply the adjust
	for (int i = 0; i < m_Anchors.Size(); i++)
	{
		// Call the update for this anchor
		m_Anchors[i]->UpdateAnchor(m_Self);
	}
	
	// Get the screen width and height
	int screenWidth = m_Self->GetRootParent()->GetFrameSize().width;
	int screenHeight = m_Self->GetRootParent()->GetFrameSize().height;

	// Set the screen frame
	m_ScreenFrame.position.x = m_CurrentFrame.position.x / screenWidth;
	m_ScreenFrame.position.y = m_CurrentFrame.position.y / screenHeight;
	m_ScreenFrame.size.width = m_CurrentFrame.size.width / screenWidth;
	m_ScreenFrame.size.height = m_CurrentFrame.size.height / screenHeight;
}

void UIFrame::SetPlacement(UIFrame::Horizontal _horizontal, UIFrame::Vertical _vertical)
{
	// ...
	m_HorizontalPlacement = _horizontal;
	m_VerticalPlacement = _vertical;

	// Update the frame
	RebuildFrame();
}

void UIFrame::RebuildFrame()
{

	/*
	// Get the parent relative offset and size
	Vector2 parentRelativeOffset = (m_FrameParent != nullptr) ? m_FrameParent->GetOffset() : GetOffset();
	Vector2 parentRelativeSize = (m_FrameParent != nullptr) ? m_FrameParent->GetSize() : GetSize();

	// The new offset and size
	Vector2 newOffset = Vector2(0, 0);

	////////////////
	// HORIZONTAL //
	////////////////

	// Check the horizontal placement
	switch (m_HorizontalPlacement)
	{
		// Right
	case UIFrame::Horizontal::Left:
	{
		// Offset x must be zero
		newOffset.x = 0;

		break;
	}
	// Left
	case UIFrame::Horizontal::Right:
	{
		// Offset x must be equal to parentSize.width - m_InternalSize.width
		newOffset.x = parentRelativeSize.width - m_InternalSize.width;

		break;
	}
	// Center
	case UIFrame::Horizontal::Center:
	{
		// Offset x must be equal to (parentSize.width - m_InternalSize.width) / 2
		newOffset.x = (parentRelativeSize.width - m_InternalSize.width) / 2;

		break;
	}
	}

	//////////////
	// VERTICAL //
	//////////////

	// Check the vertical placement
	switch (m_VerticalPlacement)
	{
		// Top
	case UIFrame::Vertical::Top:
	{
		// Offset y must be zero
		newOffset.y = 0;

		break;
	}
	// Bottom
	case UIFrame::Vertical::Bottom:
	{
		// Offset y must be equal to parentSize.height - m_InternalSize.height
		newOffset.y = parentRelativeSize.height - m_InternalSize.height;

		break;
	}
	// Center
	case UIFrame::Vertical::Center:
	{
		// Offset y must be equal to (parentSize.height - m_InternalSize.height) / 2
		newOffset.y = (parentRelativeSize.height - m_InternalSize.height) / 2;

		break;
	}
	}

	/////////////////
	// CALC OFFSET //
	/////////////////

	// Set the new offset
	m_Offset.x = m_InternalOffset.x + newOffset.x;
	m_Offset.y = m_InternalOffset.y + newOffset.y;

	// Check if we are inbounds
	m_Offset = Vector2::Clamp(m_Offset, Vector2(0, 0), Vector2(1, 1));
	m_Size = Vector2::Clamp(m_Size, Vector2(0, 0), Vector2(1.0f - m_Offset.x, 1.0f - m_Offset.y));

	///////////////////////
	// ABSOLUTE POSITION //
	///////////////////////

	// Get the parent absolute position and size
	Vector2 parentAbsolutePosition = (m_FrameParent != nullptr) ? m_FrameParent->GetAbsolutePosition() : GetAbsolutePosition();
	Vector2 parentAbsoluteSize = (m_FrameParent != nullptr) ? m_FrameParent->GetAbsoluteSize() : GetAbsoluteSize();

	// Set the new size
	m_AbsoluteSize.width = m_Size.width * parentAbsoluteSize.width;
	m_AbsoluteSize.height = m_Size.height * parentAbsoluteSize.height;

	// Set the new position
	m_AbsolutePosition.x = m_Offset.x * parentAbsoluteSize.width + parentAbsolutePosition.x;
	m_AbsolutePosition.y = m_Offset.y * parentAbsoluteSize.height + parentAbsolutePosition.y;

	// Check if we are inbounds
	m_AbsolutePosition = Vector2::Clamp(m_AbsolutePosition, parentAbsolutePosition, Vector2(parentAbsolutePosition.x + parentAbsoluteSize.width, parentAbsolutePosition.y + parentAbsoluteSize.height));
	m_AbsoluteSize = Vector2::Clamp(m_AbsoluteSize, Vector2(0, 0), Vector2(parentAbsoluteSize.width - m_AbsolutePosition.x, parentAbsoluteSize.height - m_AbsolutePosition.y));

	// Increment the rebuild version
	m_RebuildVersion++;

	// Callback rebuild
	RebuildCallback();
	*/
}

void UIFrame::NeedRebuild()
{
	/*
	// Check if we have a valid parent
	if (m_FrameParent == nullptr)
	{
		return;
	}

	// Compare the current parent rebuild version with the parent one
	if (m_ParentRebuildVersion != m_FrameParent->GetRebuildVersion())
	{
		// Set the new rebuild version
		m_ParentRebuildVersion = m_FrameParent->GetRebuildVersion();

		// Rebuild our frame data
		RebuildFrame();
	}
	*/
}