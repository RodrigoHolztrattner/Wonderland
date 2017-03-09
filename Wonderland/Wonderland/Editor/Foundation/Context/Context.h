////////////////////////////////////////////////////////////////////////////////
// Filename: Context.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\Math.h"

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
// Class name: Context
////////////////////////////////////////////////////////////////////////////////
class Context
{
public:
	Context();
	Context(const Context&);
	~Context();

	// Return the global instance
	static Context* GetInstance()
	{
		// Check if the context exist
		static Context* context = nullptr;
		if (context == nullptr)
		{
			// Create a new instance
			context = new Context;

			// Initialize the new context
			context->Initialize();
		}

		return context;
	}

////////////////////
// INITIALIZATION //
public: ////////////

	// Initialize the context
	bool Initialize();

//////////
// GETS //
public: //

	// Get the screen width/height
	unsigned int GetScreenWidth() { return m_ScreenWidth; }
	unsigned int GetScreenHeight() { return m_ScreenHeight; }

	// Get the world/view/ortho matrix
	WMatrix4 GetWorldMatrix() { return m_WorldMatrix; }
	WMatrix4 GetViewMatrix() { return m_ViewMatrix; }
	WMatrix4 GetOrthoMatrix() { return m_OrthoMatrix; }

///////////////
// VARIABLES //
private: //////

	// Screen dimension
	unsigned int m_ScreenWidth;
	unsigned int m_ScreenHeight;

	// The world view and ortho matrices
	WMatrix4 m_WorldMatrix;
	WMatrix4 m_ViewMatrix;
	WMatrix4 m_OrthoMatrix;
};