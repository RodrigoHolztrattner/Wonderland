////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrameToken.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIFrameToken.h"

//////////////////
// CONSTRUCTORS //
//////////////////

UIFrameToken::UIFrameToken()
{
	// Set the initial data
	m_TokenId = 0;
}

UIFrameToken::UIFrameToken(const UIFrameToken& other)
{
	m_TokenId = other.m_TokenId;
}

UIFrameToken::~UIFrameToken()
{
}

bool UIFrameToken::IsEqual(UIFrameToken& _otherToken)
{
	// Compare both tokens
	if (m_TokenId == _otherToken.m_TokenId)
	{
		return true;
	}

	// Update the token id
	_otherToken.m_TokenId = m_TokenId;

	return false;
}

/*
void UIFrameToken::Update(UIFrameToken& _other)
{
	_other.m_TokenId = m_TokenId;
}
*/

void UIFrameToken::Increment()
{
	m_TokenId++;
}