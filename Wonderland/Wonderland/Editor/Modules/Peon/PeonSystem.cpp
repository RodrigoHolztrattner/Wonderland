////////////////////////////////////////////////////////////////////////////////
// Filename: __InternalPeonSystem.cpp
////////////////////////////////////////////////////////////////////////////////

#include "PeonSystem.h"
#include "PeonWorker.h"

__InternalPeon::__InternalPeonSystem::__InternalPeonSystem()
{
	// Set the initial data
	m_JobArea = nullptr;
}

__InternalPeon::__InternalPeonSystem::__InternalPeonSystem(const __InternalPeon::__InternalPeonSystem& other)
{
}

__InternalPeon::__InternalPeonSystem::~__InternalPeonSystem()
{
}

// The worker thread array
__InternalPeon::__InternalPeonWorker* __InternalPeon::__InternalPeonSystem::m_JobWorkers = nullptr;

void __InternalPeon::__InternalPeonSystem::StartJob(__InternalPeon::__InternalPeonJob* _job)
{
	// Get the worker thread for this job
	__InternalPeon::__InternalPeonWorker* workerThread = _job->GetWorkerThread();

	// Insert the job into the worker thread queue
	workerThread->GetWorkerQueue()->enqueue(_job);
}

void __InternalPeon::__InternalPeonSystem::WaitForJob(__InternalPeon::__InternalPeonJob* _job)
{
	// Get the job worker thread
	__InternalPeon::__InternalPeonWorker* workerThread = _job->GetWorkerThread();

	// wait until the job has completed. in the meantime, work on any other job.
	while (!HasJobCompleted(_job))
	{
		// Try to preempt another job (or just yield)
		workerThread->ExecuteThread(nullptr);
	}
}

void __InternalPeon::__InternalPeonSystem::ResetWorkerFrame()
{
	// For each worker
	for (int i = 0; i < m_TotalWokerThreads; i++)
	{
		// Reset the free list
		m_JobWorkers[i].ResetFreeList();
	}
}

bool threadsBlocked = false;

void __InternalPeon::__InternalPeonSystem::BlockThreadsStatus(bool _status)
{
	threadsBlocked = _status;
}

bool __InternalPeon::__InternalPeonSystem::ThreadsBlocked()
{
	return threadsBlocked;
}

