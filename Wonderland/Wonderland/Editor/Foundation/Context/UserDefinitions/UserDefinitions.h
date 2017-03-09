////////////////////////////////////////////////////////////////////////////////
// Filename: UserDefinitions.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
// #include "..\..\Support\Math\Math.h"

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
// Class name: UserDefinitions
////////////////////////////////////////////////////////////////////////////////
class UserDefinitions
{
/////////////////
// DEFINITIONS //
public: /////////

	// Max sizes
	static const int MaxFontNameSize = 25;

/////////////
// STRUCTS //
public: /////

	// The user definition type
	struct UserDefinitionData
	{
		// The menu font
		char menuFontName[MaxFontNameSize];

		// The programming box font
		char programmingBox[MaxFontNameSize];
	};

public:
	UserDefinitions();
	UserDefinitions(const UserDefinitions&);
	~UserDefinitions();

	// Return the global instance
	static UserDefinitions* GetInstance()
	{
		// Check if the context exist
		static UserDefinitions* context = nullptr;
		if (context == nullptr)
		{
			// Create a new instance
			context = new UserDefinitions;

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

///////////////
// VARIABLES //
private: //////

	// Screen dimension
	unsigned int m_ScreenWidth;
	unsigned int m_ScreenHeight;

};