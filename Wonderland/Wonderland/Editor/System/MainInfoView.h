////////////////////////////////////////////////////////////////////////////////
// Filename: MainInfoView.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\Foundation\UI\UI.h"
#include <string>
#include <iostream>

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
// Class name: MainInfoView
////////////////////////////////////////////////////////////////////////////////
class MainInfoView : public UIView
{
	// UIBase is a friend
	friend UIBase;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	MainInfoView();

	// We cant copy or destruct too
	MainInfoView(const MainInfoView&);
	~MainInfoView();

	// Create this widget (called from the UIBase)
	virtual bool Create();

public:

	// Update the fps data
	void UpdateFrameRate(float _frametime, float _framerate);

/////////////
// VIRTUAL //
public: /////

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

///////////////
// VARIABLES //
private: //////

	// The fps text field
	UITextField* m_FPSIndicator;

};