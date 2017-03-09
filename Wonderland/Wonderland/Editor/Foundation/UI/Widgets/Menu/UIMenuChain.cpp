////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenuChain.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIMenuChain.h"
#include "UIMenuButton.h"

///////////////
// NAMESPACE //
///////////////

UIMenuChain::UIMenuChain()
{
	// Set the initial data
	m_ChainOwner = nullptr;
}

UIMenuChain::UIMenuChain(const UIMenuChain& other)
{
}

UIMenuChain::~UIMenuChain()
{
}

void UIMenuChain::RegisterChainOwner(UIMenuChain* _chainOwner)
{
	m_ChainOwner = _chainOwner;
}

void UIMenuChain::ForceVisibleStatus(bool _status)
{

}

void UIMenuChain::SetChainStatus(bool _status)
{
	// Force visible status
	ForceVisibleStatus(_status);

	/*
	// If we have a menubutton owner
	if (m_MenuButtonOwner != nullptr)
	{
		// Confirm the chain
		m_MenuButtonOwner->ConfirmChain();
	}
	*/
}

void UIMenuChain::EchoChainStatus(bool _status)
{
	// Force visible status
	ForceVisibleStatus(_status);
}