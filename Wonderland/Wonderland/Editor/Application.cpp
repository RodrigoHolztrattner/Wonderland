////////////////////////////////////////////////////////////////////////////////
// Filename: FluxApplication.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Application.h"

Application::Application()
{
	// Set the initial data
	// ...

	// Load our metric data
	m_ApplicationMetrics->Initialize("wonderland.metrics");
}

Application::~Application()
{
	// Save our metric data
	m_ApplicationMetrics->Release();
}

VulkanWrapper::VWResourceReference resourceReference;
VulkanWrapper::VWResourceReference resourceReference2;

bool Application::Initialize(InitializationParams _initializationParams)
{
	bool result;

	// Initialie the glfw library
	glfwInit();

	// Initialize our main adapter
	result = m_GraphicAdapter->Initialize();
	if (!result)
	{
		return false;
	}

	// Initialize our peon system
	result = Peon::Initialize(_initializationParams.sTotalNumberPeonThreads, _initializationParams.sThreadRingBufferSize);
	if (!result)
	{
		return false;
	}
	
	// Initialize our resource manager
	result = m_ResourceManager->Initialize(Peon::GetTotalWorkers());
	if (!result)
	{
		return false;
	}
	
	// Create the vulkan instance
	m_GraphicAdapter->CreateVulkanInstance(_initializationParams.sApplicationName, _initializationParams.sEngineName, _initializationParams.sApplicationVersion, _initializationParams.sEngineVersion);

	// Setup the debug callback
	m_GraphicAdapter->SetupDebugCallback();

	//
	//
	//

	ApplicationInstance* app1 = new ApplicationInstance(); m_ApplicationInstances.push_back(app1);
	// ApplicationInstance* app2 = new ApplicationInstance(); m_ApplicationInstances.push_back(app2);
	
	//
	//
	//

	// For each application instance
	for (auto applicationInstance : m_ApplicationInstances)
	{
		// Initialize this application instance
		if (!applicationInstance->Initialize())
		{
			return false;
		}
	}


	// m_ResourceManager->RequestResource(&resourceReference, "images/teste.png", [&] { Release(); });
	// m_ResourceManager->RequestResource(&resourceReference2, "images/teste.png", [&] { Release(); });

	return true;
}

void Application::Release()
{

}

void Application::MainLoop()
{
	// Create a valid working area for the peon system
	Peon::CreateWorkingArea([&] { MainLoopAux(nullptr); }); // Changed from [=]
}

void Application::ValidateApplicationInstances()
{
	// For each application instance
	for (int i = 0; i < m_ApplicationInstances.size(); i++)
	{
		// Check if this application instance is valid
		if (!m_ApplicationInstances[i]->IsValid())
		{
			// Delete this application instance
			delete m_ApplicationInstances[i];

			// Remove it from the array
			m_ApplicationInstances.erase(m_ApplicationInstances.begin() + i);

			i--;
		}
	}
}

void Application::MainLoopAux(void* _dummy)
{
	// The fps data
	double timeElapsed = 0;
	int totalFrames = 0;

	// Get the locked time
	auto lockedTime = glfwGetTime();

	// Do until we have applications to update
	while (m_ApplicationInstances.size())
	{
		// Get the current time
		auto currentTime = glfwGetTime();

		// Calculate the time difference
		double timeDifference = currentTime - lockedTime;

		// Poll events
		glfwPollEvents();

		// For each application instance
		for (auto applicationInstance : m_ApplicationInstances)
		{
			// Update this application instance
			applicationInstance->Update(timeDifference);
		}

		// Validate all application instances
		ValidateApplicationInstances();

		// Set the time elapsed
		timeElapsed += timeDifference;
		totalFrames++;
		if (timeElapsed >= 1.0f)
		{
			// Update the frame data
			m_ApplicationMetrics->UpdateFrameData(totalFrames, 1.0f / totalFrames);

			std::cout << "FPS/FT: " << totalFrames << " / " << 1.0f / totalFrames;
			std::cout << " we are running with " << totalFrames - m_ApplicationMetrics->GetMetricData().lastBuildNormalizedFramerate << " fps difference and ";
			std::cout << 1.0f / totalFrames - m_ApplicationMetrics->GetMetricData().lastBuildNormalizedFrametime << " ft difference" << std::endl;

			timeElapsed = 0;
			totalFrames = 0;
		}

		// Update the locked time
		lockedTime = currentTime;

		// Process all resource requests (we can use another thread)
		m_ResourceManager->ProcessResourceRequestQueues();
	}
}