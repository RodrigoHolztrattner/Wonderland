////////////////////////////////////////////////////////////////////////////////
// Filename: UITextureComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\UIRenderableComponent.h"
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UITextureComponent
////////////////////////////////////////////////////////////////////////////////
class UITextureComponent : public UIRenderableComponent
{

//////////////////
// CONSTRUCTORS //
public: //////////

	UITextureComponent();
	UITextureComponent(const UITextureComponent&);
	~UITextureComponent();

///////////////
// MODIFIERS //
public: ///////

	// Set the color
	void SetColor(Vector4 _color);

	// Return the color
	Vector4 GetColor();

/////////////
// VIRTUAL //
public: /////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed);

	// The clear method
	virtual void Clear();

//////////////
// CALLBACK //
private: /////

///////////////
// VARIABLES //
private: /////

	 // The color
	Vector4 m_Color;
};