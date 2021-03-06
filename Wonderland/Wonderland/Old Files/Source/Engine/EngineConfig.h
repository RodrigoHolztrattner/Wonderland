////////////////////////////////////////////////////////////////////////////////
// Filename: EngineConfig.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////

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
// Class name: EngineConfig
////////////////////////////////////////////////////////////////////////////////
class EngineConfig
{
private:

	// Const configurations
	//const char ResourcePath[] = "/Resources/";

public:
	EngineConfig();
	EngineConfig(const EngineConfig&);
	~EngineConfig();

	// Return the resource path
	const char* GetResourcePath()
	{
		return "/Resources/"/*ResourcePath*/;
	}

private:

};
