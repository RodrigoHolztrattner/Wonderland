////////////////////////////////////////////////////////////////////////////////
// Filename: PeonSystem.cpp
////////////////////////////////////////////////////////////////////////////////

#include "PeonSystem.h"
#include "PeonWorker.h"

Peon::PeonSystem::PeonSystem()
{
	// Set the initial data
	m_JobArea = nullptr;
}

Peon::PeonSystem::PeonSystem(const Peon::PeonSystem& other)
{
}

Peon::PeonSystem::~PeonSystem()
{
}

// The worker thread array
Peon::PeonWorker* Peon::PeonSystem::m_JobWorkers = nullptr;

bool Peon::PeonSystem::Initialize(unsigned int _numberWorkerThreads, unsigned int _jobBufferSize)
{
	// Save the number of worker threads
	m_TotalWokerThreads = _numberWorkerThreads;

	// Alocate space for all threads
	m_JobWorkers = new Peon::PeonWorker[_numberWorkerThreads];

	// Set the queue size for each worker thread (WE CANT DO THIS AND INITIALIZE AT THE SAME TIME!)
	for (int i = 0; i < _numberWorkerThreads; i++)
	{
		m_JobWorkers[i].SetQueueSize(_jobBufferSize);
	}
	
	// Initialize all threads
	for (int i = 0; i < _numberWorkerThreads; i++)
	{
		m_JobWorkers[i].Initialize(this, i, i == 0); // Check for the first thread (the main one)
	}

	return true;
}

void Peon::PeonSystem::StartJob(Peon::PeonJob* _job)
{
	// Get the worker thread for this job
	Peon::PeonWorker* workerThread = _job->GetWorkerThread();

	// Insert the job into the worker thread queue
	workerThread->GetWorkerQueue()->Push(_job);
}

void Peon::PeonSystem::WaitForJob(Peon::PeonJob* _job)
{
	// Get the job worker thread
	Peon::PeonWorker* workerThread = _job->GetWorkerThread();

	// wait until the job has completed. in the meantime, work on any other job.
	while (!HasJobCompleted(_job))
	{
		// Try to preempt another job (or just yield)
		workerThread->ExecuteThread(nullptr);
	}
}

bool threadsBlocked = false;

void Peon::PeonSystem::BlockThreadsStatus(bool _status)
{
	threadsBlocked = _status;
}

bool Peon::PeonSystem::ThreadsBlocked()
{
	return threadsBlocked;
}

