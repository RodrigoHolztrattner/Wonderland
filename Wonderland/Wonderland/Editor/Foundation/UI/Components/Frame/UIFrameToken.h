////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrameToken.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\ECS\ECS_Component.h"
#include "..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\Support\Container\Array\Array.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

/** UIFrameComponent */
class UIFrameComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIFrameToken
////////////////////////////////////////////////////////////////////////////////
class UIFrameToken
{
public:

	// The UIFrameComponent is a friend class
	friend UIFrameComponent;

	// Constructor
	UIFrameToken();
	UIFrameToken(const UIFrameToken&);
	~UIFrameToken();

	// Compare with another token
	bool IsEqual(UIFrameToken& _otherToken);

	// Update the token ID
	// void Update(UIFrameToken& _other);

protected:

	// Increment the token value
	void Increment();

private:

	// The token id
	unsigned int m_TokenId;
};