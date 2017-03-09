////////////////////////////////////////////////////////////////////////////////
// Filename: UserDefinitionsIO.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UserDefinitionsIO.h"

///////////////
// NAMESPACE //
///////////////

UserDefinitionsIO::UserDefinitionsIO()
{
}

UserDefinitionsIO::UserDefinitionsIO(const UserDefinitionsIO& other)
{
}

UserDefinitionsIO::~UserDefinitionsIO()
{
}

bool UserDefinitionsIO::Initialize()
{
	// Set the screen dimension data
	m_ScreenWidth = 1600; // 1900
	m_ScreenHeight = 1024; // 1000


	return true;
}