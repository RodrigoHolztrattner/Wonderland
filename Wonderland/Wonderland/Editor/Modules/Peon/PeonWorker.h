////////////////////////////////////////////////////////////////////////////////
// Filename: __InternalPeonWorker.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <thread>

#include <iostream>
#include <chrono>
#include <thread>

#include "PeonJob.h"
#include "..\ConcurrentQueue.h"

/////////////
// DEFINES //
/////////////

// The debug flag
// #define JobWorkerDebug

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// __InternalPeon
NamespaceBegin(__InternalPeon)

// We know the job system
class __InternalPeonSystem;

// The thread id and current job
thread_local static int			CurrentThreadIdentifier;

////////////////////////////////////////////////////////////////////////////////
// Class name: __InternalPeonWorker
////////////////////////////////////////////////////////////////////////////////
class __InternalPeonWorker
{
public:
	__InternalPeonWorker();
	__InternalPeonWorker(const __InternalPeonWorker&);
	~__InternalPeonWorker();

public:

	// Set the queue size
	void SetQueueSize(unsigned int _jobBufferSize);

	// Initialize this worker thread
	bool Initialize(__InternalPeon::__InternalPeonSystem* _ownerSystem, int _threadId, bool _mainThread = false);

	// Execute this thread
	void ExecuteThread(void* _arg);

	// Try to get a job from the current worker thread, or try to steal one from the others
	bool GetJob(__InternalPeon::__InternalPeonJob** _job);

	// Return a ptr to the work stealing queue
	moodycamel::ConcurrentQueue<__InternalPeon::__InternalPeonJob*>* GetWorkerQueue()
	{
		return m_WorkQueue;
	}

	// Yield the current time slice
	void Yield()
	{
		std::this_thread::yield();
	}

	// Return the thread id
	int GetThreadId()
	{
		return m_ThreadId;
	}

	// Return a fresh (usable) job
	__InternalPeon::__InternalPeonJob* GetFreshJob()
	{
		// Select a valid job
		__InternalPeon::__InternalPeonJob* selectedJob = &m_JobFreeList[m_JobFreeListPosition];

		// Increment the free list position
		m_JobFreeListPosition++;

		return selectedJob;
	}

	// Reset the free list
	void ResetFreeList()
	{
		m_JobFreeListPosition = 0;
	}

public:

	void ExecuteThreadAux();

	static __InternalPeonJob* GetCurrentJob();

///////////////
// VARIABLES //
private: //////

	// The owner (job system)
	__InternalPeon::__InternalPeonSystem* m_OwnerSystem;

	// Array of jobs
	moodycamel::ConcurrentQueue<__InternalPeon::__InternalPeonJob*>* m_WorkQueue;

	// Our job free list
	__InternalPeon::__InternalPeonJob* m_JobFreeList;
	unsigned int m_JobFreeListPosition;
	unsigned int m_JobFreeListMax;

	// The internal thread id
	unsigned int m_ThreadId;


};

// __InternalPeon
NamespaceEnd(__InternalPeon)