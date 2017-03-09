////////////////////////////////////////////////////////////////////////////////
// Filename: PeonWorker.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <pthread.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "PeonJob.h"
#include "PeonStealingQueue.h"

/////////////
// DEFINES //
/////////////

// The debug flag
#define JobWorkerDebug

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Peon
NamespaceBegin(Peon)

// We know the job system
class PeonSystem;

// The thread id
thread_local static int CurrentThreadIdentifier;

////////////////////////////////////////////////////////////////////////////////
// Class name: PeonWorker
////////////////////////////////////////////////////////////////////////////////
class PeonWorker
{
public:
	PeonWorker();
	PeonWorker(const PeonWorker&);
	~PeonWorker();

public:

	// Set the queue size
	void SetQueueSize(unsigned int _jobBufferSize);

	// Initialize this worker thread
	bool Initialize(Peon::PeonSystem* _ownerSystem, int _threadId, bool _mainThread = false);

	// Execute this thread
	void ExecuteThread(void* _arg);

	// Try to get a job from the current worker thread, or try to steal one from the others
	Peon::PeonJob* GetJob();

	// Return a ptr to the work stealing queue
	Peon::PeonStealingQueue* GetWorkerQueue()
	{
		return &m_WorkQueue;
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

private:



///////////////
// VARIABLES //
private: //////

	// The owner (job system)
	Peon::PeonSystem* m_OwnerSystem;

	// Array of jobs
	Peon::PeonStealingQueue m_WorkQueue;

	// The internal thread id
	unsigned int m_ThreadId;


};

// Peon
NamespaceEnd(Peon)