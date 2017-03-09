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
	m_InternalOffset = m_Offset = Vector2(0, 0);
	m_InternalSize = m_Size = Vector2(0, 0);
	m_HorizontalPlacement = Horizontal::Left;
	m_VerticalPlacement = Vertical::Top;
	m_FrameParent = nullptr;
	m_AbsolutePosition = Vector2(0, 0);
	m_RebuildVersion = m_ParentRebuildVersion = 0;
}

UIFrame::UIFrame(const UIFrame& other)
{
}

UIFrame::~UIFrame()
{
}

/*
void UIFrame::SetFrame(Vector4 _frame)
{
m_Position.x = _frame.x;
m_Position.y = _frame.y;
m_Size.x = _frame.z;
m_Size.y = _frame.w;

// Update the frame
RebuildFrame();
}
*/

void UIFrame::SetOffset(Vector2 _offset)
{
	// Set the offset
	m_InternalOffset = m_Offset = _offset;
}

void UIFrame::SetSize(Vector2 _size)
{
	// Set the size and if this is the root object, set the absolute size too
	m_InternalSize = m_Size = _size;
	if (m_FrameParent == nullptr)
	{
		m_AbsoluteSize = m_Size;
		m_InternalSize = m_Size = Vector2(1, 1);
	}
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
	// Multiply the parent relative offset and size by ours
	Vector2 relativeOffset = GetOffset();
	Vector2 relativeSize = GetSize();
	UIFrame* currentFrameParent = m_FrameParent;
	while (currentFrameParent != nullptr)
	{
		relativeOffset.x *= currentFrameParent->GetOffset().x;
		relativeOffset.y *= currentFrameParent->GetOffset().y;
		relativeSize.x *= currentFrameParent->GetSize().x;
		relativeSize.y *= currentFrameParent->GetSize().y;
		currentFrameParent = currentFrameParent->m_FrameParent;
	}
	*/
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
}

void UIFrame::NeedRebuild()
{
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
}