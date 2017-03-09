////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrameAnchor.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIFrameAnchor.h"
#include "UIBase.h"

///////////////
// NAMESPACE //
///////////////

UIFrameAnchor::UIFrameAnchor(Policy _policy, UIBase* _targetWidget)
{
	// Set the initial data
	m_Policy = _policy;
	m_LinkedObject = UIBase::TakeOwnership(_targetWidget);
}

UIFrameAnchor::UIFrameAnchor(const UIFrameAnchor& other)
{
}

UIFrameAnchor::~UIFrameAnchor()
{
}

void UIFrameAnchor::Release()
{
	UIBase::ReleaseWidget(m_LinkedObject);
}

void UIFrameAnchor::UpdateAnchor(UIBase* _mainWidget)
{
	// Check if the linked object is valid
	if (!UIBase::IsValid(m_LinkedObject))
	{
		// Release the linked object
		m_LinkedObject = UIBase::ReleaseWidget(m_LinkedObject);

		return;
	}

	// Check if the linked object is up-to-date
	// ...

	// Check our policy
	switch (m_Policy)
	{
		// Top Align
		case Policy::TopAlign:
		{
			TopAlignAdjust(_mainWidget);
			break;
		}
		// Right Align
		case Policy::RightAlign:
		{
			RightAlignAdjust(_mainWidget);
			break;
		}
		// Bottom Align
		case Policy::BottomAlign:
		{
			BottomAlignAdjust(_mainWidget);
			break;
		}
		// Left Align
		case Policy::LeftAlign:
		{
			LeftAlignAdjust(_mainWidget);
			break;
		}
		// Top Scale
		case Policy::TopScale:
		{
			TopScaleAdjust(_mainWidget);
			break;
		}
		// Right Scale
		case Policy::RightScale:
		{
			RightScaleAdjust(_mainWidget);
			break;
		}
		// Bottom Scale
		case Policy::BottomScale:
		{
			BottomScaleAdjust(_mainWidget);
			break;
		}
		// Left Scale
		case Policy::LeftScale:
		{
			LeftScaleAdjust(_mainWidget);
			break;
		}
	}
}

void UIFrameAnchor::TopAlignAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Set the value
	currentPosition.y = m_LinkedObject->GetFramePosition().y + m_LinkedObject->GetFrameSize().height;

	// Set the new value
	_mainWidget->SetFramePosition(currentPosition);
}

void UIFrameAnchor::BottomAlignAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Set the value
	currentPosition.y = m_LinkedObject->GetFramePosition().y - _mainWidget->GetFrameSize().height;

	// Set the new value
	_mainWidget->SetFramePosition(currentPosition);
}

void UIFrameAnchor::RightAlignAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Set the value
	currentPosition.x = m_LinkedObject->GetFramePosition().x - _mainWidget->GetFrameSize().width;

	// Set the new value
	_mainWidget->SetFramePosition(currentPosition);
}

void UIFrameAnchor::LeftAlignAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Set the value
	currentPosition.x = m_LinkedObject->GetFramePosition().x + m_LinkedObject->GetFrameSize().width;

	// Set the new value
	_mainWidget->SetFramePosition(currentPosition);
}

void UIFrameAnchor::TopScaleAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Get the current size
	Vector2 currentSize = _mainWidget->GetFrameSize();

	// Set the value
	// currentSize.height += currentPosition.y - (m_LinkedObject->GetFramePosition.y + m_LinkedObject->GetFrameSize().height);
	currentSize.height = (currentPosition.y + currentSize.height) - (m_LinkedObject->GetFramePosition().y + m_LinkedObject->GetFrameSize().height);
	currentPosition.y = (m_LinkedObject->GetFramePosition().y + m_LinkedObject->GetFrameSize().height);

	// Set the new value
	_mainWidget->SetFrameSize(currentSize);
	_mainWidget->SetFramePosition(currentPosition);
}

void UIFrameAnchor::RightScaleAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Get the current size
	Vector2 currentSize = _mainWidget->GetFrameSize();

	// Set the value
	currentSize.width = m_LinkedObject->GetFramePosition().x - currentPosition.x;

	// Set the new value
	_mainWidget->SetFrameSize(currentSize);
}

void UIFrameAnchor::BottomScaleAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Get the current size
	Vector2 currentSize = _mainWidget->GetFrameSize();

	// Set the value
	currentSize.height = m_LinkedObject->GetFramePosition().y - currentPosition.y;

	// Set the new value
	_mainWidget->SetFrameSize(currentSize);
}

void UIFrameAnchor::LeftScaleAdjust(UIBase* _mainWidget)
{
	// Get the current position
	Vector2 currentPosition = _mainWidget->GetFramePosition();

	// Get the current size
	Vector2 currentSize = _mainWidget->GetFrameSize();

	// Set the value
	currentSize.width = (currentPosition.x + currentSize.width) - (m_LinkedObject->GetFramePosition().x + m_LinkedObject->GetFrameSize().width);
	currentPosition.x = (m_LinkedObject->GetFramePosition().x + m_LinkedObject->GetFrameSize().width);

	// Set the new value
	_mainWidget->SetFrameSize(currentSize);
	_mainWidget->SetFramePosition(currentPosition);
}