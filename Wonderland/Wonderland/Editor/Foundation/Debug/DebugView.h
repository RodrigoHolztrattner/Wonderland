////////////////////////////////////////////////////////////////////////////////
// Filename: DebugView.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
/*
#include "..\UI\Widgets\View\View.h"

#include "..\..\Support\Container\Array\Array.h"
#include "..\UI\Widgets\Text\UITextBase.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

// We know the command type
struct CommandType;

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: DebugView
////////////////////////////////////////////////////////////////////////////////
class DebugView : public View
{
public:
	DebugView(UIBase* _parent);
	~DebugView();

	////////////
	// GLOBAL //
	////////////
	
	// Return the global instance for this debug view
	static DebugView* GetGlobalInstance(UIBase* _parent = nullptr)
	{
		static DebugView* globalDebugView = nullptr;
		if (globalDebugView == nullptr)
		{
			
			// Create the global debug view
			globalDebugView = new DebugView(_parent);
			globalDebugView->SetOffset(Vector2(0, 0));
			globalDebugView->SetSize(Vector2(0.5, 0.2));
			globalDebugView->SetPlacement(UIFrame::Horizontal::Left, UIFrame::Vertical::Top);
			globalDebugView->SetFrameColor(Vector4(0.7, 0.1, 0.5, 0.0));
			globalDebugView->RebuildFrame();
			globalDebugView->SetDebugName("Debug Window");

			// Create the font object
			globalDebugView->CreateFontObject();
			
		}

		return globalDebugView;
	}

	// Insert a debug message
	void DebugMessage(std::string _message)
	{
		// Check if we should delete one debug message
		if (m_DebugList.Size() >= 10)
		{
			// Delete the last one
			// ...
		}
		
		// Create the new text view
		UITextBase* textView = new UITextBase(this, m_Font);
		textView->SetOffset(Vector2(0, 0));
		textView->SetSize(Vector2(1, 0.2));
		textView->SetPlacement(UIFrame::Horizontal::Left, UIFrame::Vertical::Top);
		textView->SetFrameColor(Vector4(0.2, 0.5, 0.8, 1.0));
		textView->SetText(_message);
		textView->RebuildFrame();
		textView->SetDebugName("Debug text view");

		// Insert into the array
		m_DebugList.Add(textView);

		// Move each debug message
		for (int i = 0; i < m_DebugList.Size(); i++)
		{
			m_DebugList[i]->SetOffset(Vector2(0, i * 0.2));
			m_DebugList[i]->RebuildFrame();
		}
		
	}

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

protected:

	// Create the font object
	void CreateFontObject()
	{
		m_Font = new UIFont();
		m_Font->Initialize("Roboto-Regular.ttf", 32);
	}

///////////////
// RENDERING //
public: ///////

	// Render this DebugView
	virtual void Render();

private:

	// Our debug list
	Array<UITextBase*> m_DebugList;

	// Our text font
	UIFont* m_Font;
};

*/