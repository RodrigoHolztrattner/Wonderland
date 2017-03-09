////////////////////////////////////////////////////////////////////////////////
// Filename: PeonSystem.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <atomic>
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

// Peon
NamespaceBegin(Peon)

////////////////////////////////////////////////////////////////////////////////
// Class name: PeonSystem
////////////////////////////////////////////////////////////////////////////////
class PeonSystem
{
public:
	PeonSystem();
	PeonSystem(const PeonSystem&);
	~PeonSystem();

	// Initialize the job system
	bool Initialize(unsigned int _numberWorkerThreads, unsigned int _jobBufferSize);

	// Create a valid area for the job system
	template <class CallType>
	void CreateJobArea(CallType& _member, void (CallType::* const &_function)(Peon::PeonJob*, void*), void* _data)
	{
		// The main thread should take controll of the first PeonWorker Thread, untill now there is
		// no caution because everything was single threaded, now the critical section begins :)

		// Create the new job
		m_JobArea = new Peon::PeonJob;

		// Initialize the job
		m_JobArea->Initialize();

		// Set the job function
		m_JobArea->SetJobFunction(nullptr, _member, _function, _data);

		// Get the default worker thread
		Peon::PeonWorker* workerThread = GetDefaultWorkerThread();

		// Set the job worker thread
		m_JobArea->SetWorkerThread(workerThread);

		// This must be the first call to enter a PeonJob!
		Peon::PeonSystem::StartJob(m_JobArea);

		// Execute the main worker thread
		workerThread->ExecuteThread(nullptr);
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
	PeonWorker* GetJobWorkers()
	{
		return m_JobWorkers;
	}

	////////////
	// STATIC //
	////////////

	// Create a job
	template <class CallType>
	static Peon::PeonJob* CreateJob(Peon::PeonJob* _from, CallType& _member, void (CallType::* const &_function)(Peon::PeonJob*, void*), void* _data)
	{
		// Get the default worker thread
		Peon::PeonWorker* workerThread = _from->GetWorkerThread(); // Peon::PeonSystem::GetCurrentPeon()

		// Get a fresh job
		Peon::PeonJob* freshJob = workerThread->GetWorkerQueue()->GetFreshJob();

		// Initialize the job
		freshJob->Initialize();

		// Set the job worker thread
		freshJob->SetWorkerThread(workerThread);

		// Set the job function
		freshJob->SetJobFunction(nullptr, _member, _function, _data);

		// Return the new job
		return freshJob;
	}

	// Create a job as child
	template <class CallType>
	static Peon::PeonJob* CreateChildJob(Peon::PeonJob* _parentJob, CallType& _member, void (CallType::* const &_function)(Peon::PeonJob*, void*), void* _data)
	{
		// Não preciso me preocupar com o parent job sendo deletado ou liberando waits caso exista concorrencia pois seguimos da seguinte lógica, apenas o job atual pode criar jobs
		// filhos, e pode apenas adicionar elas para si mesmo, logo se estamos aqui quer dizer que o parent job ainda tem no minimo um trabalho restante (que é adicionar esse job)
		// e por consequencia ele não será deletado ou liberará algum wait.

		// Atomic increment the number of unfinished jobs of our parent
		_parentJob->m_UnfinishedJobs++;

		// Get the worker thread from the parent
		Peon::PeonWorker* workerThread = _parentJob->GetWorkerThread(); // Peon::PeonSystem::GetCurrentPeon()

		// Get a fresh job
		Peon::PeonJob* freshJob = workerThread->GetWorkerQueue()->GetFreshJob();

		// Initialize the job
		freshJob->Initialize();

		// Set the job function
		freshJob->SetJobFunction(_parentJob, _member, _function, _data);

		// Set the job parent
		freshJob->SetParentJob(_parentJob);

		// Return the new job
		return freshJob;
	}

	// Run a job
	static void StartJob(PeonJob* _job);

	// Wait for a job to continue
	static void WaitForJob(PeonJob* _job);

	// REMOVER ESSAS FUNÇÕES OU USAR DEBUG #DEFINE
	static void BlockThreadsStatus(bool _status);
	static bool ThreadsBlocked();

private:

	// Return the current thread executing this code
	Peon::PeonWorker* GetCurrentPeon()
	{
		return &PeonSystem::m_JobWorkers[Peon::CurrentThreadIdentifier];
	}

	////////////
	////////////
	////////////

private:

	// Return the default worker thread
	Peon::PeonWorker* GetDefaultWorkerThread()
	{
		return &m_JobWorkers[0];
	}

	// The total of worker threads
	unsigned int m_TotalWokerThreads;

	// The worker thread array
	static Peon::PeonWorker* m_JobWorkers;

	// The current job area
	Peon::PeonJob* m_JobArea;
};


// Peon
NamespaceEnd(Peon)