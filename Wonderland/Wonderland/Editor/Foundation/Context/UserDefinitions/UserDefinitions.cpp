////////////////////////////////////////////////////////////////////////////////
// Filename: UserDefinitions.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UserDefinitions.h"

///////////////
// NAMESPACE //
///////////////

UserDefinitions::UserDefinitions()
{
}

UserDefinitions::UserDefinitions(const UserDefinitions& other)
{
}

UserDefinitions::~UserDefinitions()
{
}

bool UserDefinitions::Initialize()
{
	// Set the screen dimension data
	m_ScreenWidth = 1600; // 1900
	m_ScreenHeight = 1024; // 1000

	return true;
}