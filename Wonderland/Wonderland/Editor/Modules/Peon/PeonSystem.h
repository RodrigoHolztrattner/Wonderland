////////////////////////////////////////////////////////////////////////////////
// Filename: __InternalPeonSystem.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <atomic>
#include <vector>
#include "PeonJob.h"
#include "PeonWorker.h"

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// __InternalPeon
NamespaceBegin(__InternalPeon)

////////////////////////////////////////////////////////////////////////////////
// Class name: __InternalPeonSystem
////////////////////////////////////////////////////////////////////////////////
class __InternalPeonSystem
{
public:
	__InternalPeonSystem();
	__InternalPeonSystem(const __InternalPeonSystem&);
	~__InternalPeonSystem();

	// Initialize the job system
	template <class ThreadUserDatType = unsigned char>
	bool Initialize(unsigned int _numberWorkerThreads, unsigned int _jobBufferSize, bool _useUserData = false)
	{
		// Block all threads
		BlockThreadsStatus(true);

		// Save the number of worker threads
		m_TotalWokerThreads = _numberWorkerThreads;

		// Alocate space for all threads
		m_JobWorkers = new __InternalPeon::__InternalPeonWorker[_numberWorkerThreads];

		// Set the queue size for each worker thread (WE CANT DO THIS AND INITIALIZE AT THE SAME TIME!)
		for (int i = 0; i < _numberWorkerThreads; i++)
		{
			m_JobWorkers[i].SetQueueSize(_jobBufferSize);
		}

		// Create the thread user data
		for (int i = 0; i < _numberWorkerThreads && _useUserData; i++)
		{
			// Create the thread user data
			ThreadUserDatType* threadUserData = new ThreadUserDatType();
			m_ThredUserData.push_back(threadUserData);
		}

		// Initialize all threads
		for (int i = 0; i < _numberWorkerThreads; i++)
		{
			m_JobWorkers[i].Initialize(this, i, i == 0); // Check for the first thread (the main one)
		}

		// Unblock all threads
		BlockThreadsStatus(false);

		return true;
	}

	// Create a valid area for the job system
	__InternalPeon::__InternalPeonJob* CreateJobArea(std::function<void()> _function)
	{
		// The main thread should take controll of the first __InternalPeonWorker Thread, untill now there is
		// no caution because everything was single threaded, now the critical section begins :)
		
		// Check if we should throw an error
		if (m_JobArea != nullptr)
		{
			return nullptr;
		}

		// Create the new job
		m_JobArea = new __InternalPeon::__InternalPeonJob;

		// Initialize the job
		m_JobArea->Initialize();

		// Set the job function
		m_JobArea->SetJobFunction(nullptr, _function);

		// Get the default worker thread
		__InternalPeon::__InternalPeonWorker* workerThread = GetDefaultWorkerThread();

		// Set the job worker thread
		m_JobArea->SetWorkerThread(workerThread);

		// This must be the first call to enter a __InternalPeonJob!
		__InternalPeon::__InternalPeonSystem::StartJob(m_JobArea);

		// Execute the main worker thread
		workerThread->ExecuteThread(nullptr);

		return m_JobArea;
	}

	// Delete a valid job system area
	void DeleteJobArea()
	{
		// Delete the current job area
		if (m_JobArea)
		{
			delete m_JobArea;
			m_JobArea = nullptr;
		}
	}

	// Return the total worker threads
	unsigned int GetTotalWorkerThreads()
	{
		return m_TotalWokerThreads;
	}

	// Return the job worker array
	__InternalPeonWorker* GetJobWorkers()
	{
		return m_JobWorkers;
	}

	// Return the thread user data by thread index
	template <class ThreadUserDatType>
	ThreadUserDatType* GetUserData(unsigned int _threadIndex)
	{
		return (ThreadUserDatType*)m_ThredUserData[_threadIndex];
	}

	// Reset the actual worker frame
	void ResetWorkerFrame();

	// Job container creation helper
	void JobContainerHelper(void* _data) {}

	////////////
	// STATIC //
	////////////

	// Create a job
	static __InternalPeon::__InternalPeonJob* CreateJob(std::function<void()> _function)
	{
		// Get the default worker thread
		__InternalPeon::__InternalPeonWorker* workerThread = __InternalPeon::__InternalPeonSystem::GetCurrentPeon();

		// Get a fresh job
		__InternalPeon::__InternalPeonJob* freshJob = workerThread->GetFreshJob();

		// Initialize the job
		freshJob->Initialize();

		// Set the job worker thread
		freshJob->SetWorkerThread(workerThread);

		// Set the job function
		freshJob->SetJobFunction(nullptr, _function);

		// Return the new job
		return freshJob;
	}

	// Create a job as child
	static __InternalPeon::__InternalPeonJob* CreateChildJob(std::function<void()> _function)
	{
		return CreateChildJob(__InternalPeon::__InternalPeonWorker::GetCurrentJob(), _function);
	}

	// Create a job as child for the given parent job
	static __InternalPeon::__InternalPeonJob* CreateChildJob(__InternalPeon::__InternalPeonJob* _parentJob, std::function<void()> _function)
	{
		// Não preciso me preocupar com o parent job sendo deletado ou liberando waits caso exista concorrencia pois seguimos da seguinte lógica, apenas o job atual pode criar jobs
		// filhos, e pode apenas adicionar elas para si mesmo, logo se estamos aqui quer dizer que o parent job ainda tem no minimo um trabalho restante (que é adicionar esse job)
		// e por consequencia ele não será deletado ou liberará algum wait.

		// Atomic increment the number of unfinished jobs of our parent
		_parentJob->m_UnfinishedJobs++;

		// Get the worker thread from the parent
		__InternalPeon::__InternalPeonWorker* workerThread = __InternalPeon::__InternalPeonSystem::GetCurrentPeon();

		// Get a fresh job
		__InternalPeon::__InternalPeonJob* freshJob = workerThread->GetFreshJob();

		// Initialize the job
		freshJob->Initialize();

		// Set the job function
		freshJob->SetJobFunction(_parentJob, _function);

		// Set the job parent
		freshJob->SetParentJob(_parentJob);

		// Return the new job
		return freshJob;
	}

	// Run a job
	static void StartJob(__InternalPeonJob* _job);

	// Wait for a job to continue
	static void WaitForJob(__InternalPeonJob* _job);

	// REMOVER ESSAS FUNÇÕES OU USAR DEBUG #DEFINE
	static void BlockThreadsStatus(bool _status);
	static bool ThreadsBlocked();

	// Return the current thread executing this code
	static __InternalPeon::__InternalPeonWorker* GetCurrentPeon()
	{
		return &__InternalPeonSystem::m_JobWorkers[__InternalPeon::CurrentThreadIdentifier];
	}

	////////////
	////////////
	////////////

private:

	// Return the default worker thread
	__InternalPeon::__InternalPeonWorker* GetDefaultWorkerThread()
	{
		return &m_JobWorkers[0];
	}

	// The total of worker threads
	unsigned int m_TotalWokerThreads;

	// The worker thread array
	static __InternalPeon::__InternalPeonWorker* m_JobWorkers;

	// The thread user data
	std::vector<void*> m_ThredUserData;

	// The current job area
	__InternalPeon::__InternalPeonJob* m_JobArea;
};


// __InternalPeon
NamespaceEnd(__InternalPeon)