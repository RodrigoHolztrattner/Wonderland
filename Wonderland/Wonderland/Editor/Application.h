////////////////////////////////////////////////////////////////////////////////
// Filename: Application.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Modules\VulkanWrapper\VulkanWrapper.h"
#include "ApplicationInstance.h"
#include "ApplicationMetrics.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////
#include "Modules\GlobalInstance.h"
#include "Modules\Peon\Peon.h"

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

////////////////
// FORWARDING //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: Application
////////////////////////////////////////////////////////////////////////////////
class Application
{
public:

	// Our initializator struct
	struct InitializationParams
	{
		// The application name
		char* sApplicationName;

		// The engine name
		char* sEngineName;

		// The application version
		uint32_t sApplicationVersion;

		// The engine version
		uint32_t sEngineVersion;

		// The maximum number of threads
		int sTotalNumberPeonThreads;
		
		// The thread ring buffer size
		uint32_t sThreadRingBufferSize;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	Application();
	~Application();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	virtual bool Initialize(InitializationParams _initializationParams);

	// Release
	virtual void Release();

	// The main loop
	void MainLoop();

private:

	// Validate all application instances
	void ValidateApplicationInstances();

	// The main loop helper
	void MainLoopAux(void* _dummy);

///////////////
// VARIABLES //
private: //////

	// Our application instances
	std::vector<ApplicationInstance*> m_ApplicationInstances;

////////////////
// SINGLETONS //
////////////////

	// Our graphic adapter
	GlobalInstance<VulkanWrapper::GraphicAdapter> m_GraphicAdapter;

	// Our resource manager
	GlobalInstance<VulkanWrapper::ResourceManager> m_ResourceManager;

	// Our application metrics
	GlobalInstance<ApplicationMetrics> m_ApplicationMetrics;
};