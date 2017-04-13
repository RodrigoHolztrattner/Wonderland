////////////////////////////////////////////////////////////////////////////////
// Filename: FluxApplication.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Application.h"
#include "Modules\Packet\PacketManager.h"
#include "Modules\Reference.h"

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

	// Save our packet data
	// m_PacketManager-> // m_IndexLoader.SaveIndex(m_IndexData, &m_RootFolder);
}

/*
	- Não existe mais o resource "texture", existe apenas array textures, ou melhor, texture groups... Esses são considerados recursos.
	- Existe o objeto textura que nada mais é uma referência à um Texture Group mais um identificador de qual textura utilizar.
	- Com a utilização de array textures, todas as texturas de um grupo devem ter o mesmo tamanho e formato, isso é obrigatório.
	- Cada gerenciador de textura é único para cada instancia e utiliza um resource manager global, isso faz com que caso duas instancias precisem da mesma
	textura, 2 objetos deverão ser criados (mas usaremos o mesmo objeto "Recurso").

*/

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

	// Initialize our packet manager
	result = m_PacketManager->Initialize("wonderland");
	if (!result)
	{
		return false;
	}
	
	// Initialize the resource context
	result = m_ResourceContext->Initialize(m_GraphicAdapter, m_PacketManager);
	if (!result)
	{
		return false;
	}
	
	// Create the vulkan instance
	m_GraphicAdapter->CreateVulkanInstance(_initializationParams.sApplicationName, _initializationParams.sEngineName, _initializationParams.sApplicationVersion, _initializationParams.sEngineVersion);

	// Setup the debug callback
	m_GraphicAdapter->SetupDebugCallback();

	// Initialize the common resources
	InitializeInternalStorage();

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

#include "Modules\TextureCollecion\TextureCollection.h"

void Application::InitializeInternalStorage()
{
	// The texture collection creator
	TextureCollection::Creator textureCollectionCreator;

	// Create a texture collection
	textureCollectionCreator.AddTextureFromFile("Galaxy", "images/teste.png");
	textureCollectionCreator.AddTextureFromFile("Ground", "images/teste3.png");

	// Save the texture collection
	textureCollectionCreator.SaveTextureCollection("MyTextureCollection", "images/texCollection.tc");

	// Set our packet resource data
	m_PacketManager->CreateFile("TextureGroups/MyGroup", "images/texCollection.tc");

	//

	// The model creator
	ModelComposer::Creator modelCreator;

	// Prepare the model
	modelCreator.AddVertex(ModelComposer::VertexFormat(glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 1.0)));
	modelCreator.AddVertex(ModelComposer::VertexFormat(glm::vec3(1.0, 0.0, 0.0), glm::vec2(1.0, 0.0)));
	modelCreator.AddVertex(ModelComposer::VertexFormat(glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0)));
	modelCreator.AddVertex(ModelComposer::VertexFormat(glm::vec3(1.0, 1.0, 0.0), glm::vec2(1.0, 1.0)));
	modelCreator.AddIndex(0);
	modelCreator.AddIndex(1);
	modelCreator.AddIndex(2);
	modelCreator.AddIndex(0);
	modelCreator.AddIndex(3);
	modelCreator.AddIndex(1);

	// Create from the current vertex data
	modelCreator.CreateFromCurrentData();

	// Save the model
	modelCreator.SaveModel("MyModel", "models/model.m");

	// Set our packet resource data
	m_PacketManager->CreateFile("Models/MyModel", "models/model.m");

	//
	//
	//

	VulkanWrapper::VWTextureGroupIndex newTextureGroupIndex = {};
	newTextureGroupIndex.Create(HashedString("textureGroupSky").Hash(), "TextureGroups/MyGroup");

	VulkanWrapper::VWModelIndex newModelIndex = {};
	newModelIndex.Create(HashedString("square").Hash(), "Models/MyModel");

	m_ResourceContext->GetTextureGroupIndexLoader()->AddIndex(m_PacketManager, newTextureGroupIndex);
	m_ResourceContext->GetModelIndexLoader()->AddIndex(m_PacketManager, newModelIndex);
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

			// Get the context reference
			VulkanWrapper::Context* applicationContext = applicationInstance->GetContextReference();

			// Do the application update
			applicationContext->ApplicationUpdate();
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
		m_ResourceContext->ProcessResourceRequests();
	}
}