////////////////////////////////////////////////////////////////////////////////
// Filename: PeonWorker.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PeonWorker.h"
#include "PeonSystem.h"

Peon::PeonWorker::PeonWorker()
{
}

Peon::PeonWorker::PeonWorker(const Peon::PeonWorker& other)
{
}

Peon::PeonWorker::~PeonWorker()
{
}

#ifdef JobWorkerDebug
static unsigned int JobWorkerId = 0;
#endif

void* ExecuteThreadAux(void* _data)
{
	// Cast to a worker thread object
	Peon::PeonWorker* jobWorker = (Peon::PeonWorker*)_data;

	// Set the global per thread id
	Peon::CurrentThreadIdentifier = jobWorker->GetThreadId();

	// Run the execute function
	while (true)
	{
		jobWorker->ExecuteThread(nullptr);
	}
}

void Peon::PeonWorker::SetQueueSize(unsigned int _jobBufferSize)
{
	// Initialize the work queue
	// m_WorkQueue.Initialize(_jobBufferSize);
}

bool Peon::PeonWorker::Initialize(Peon::PeonSystem* _ownerSystem, int _threadId, bool _mainThread)
{
	pthread_t thread;

	// Set the thread id
	m_ThreadId = _threadId;

	// Set the owner
	m_OwnerSystem = _ownerSystem;

	// 
	std::cout << "Thread created" << std::endl;

	// Check if this worker thread is the main one
	if (!_mainThread)
	{
		// Create the new thread
		pthread_create(&thread, NULL, ExecuteThreadAux, this);
	}

	return true;
}

Peon::PeonJob* Peon::PeonWorker::GetJob()
{
	Peon::PeonStealingQueue* queue = GetWorkerQueue();

	Peon::PeonJob* job = queue->Pop();
	if (IsEmptyJob(job))
	{
		
		// this is not a valid job because our own queue is empty, so try stealing from some other queue
		// unsigned int randomIndex = GenerateRandomNumber(0, g_JobWorkerCount + 1);
		unsigned int randomIndex = rand() % m_OwnerSystem->GetTotalWorkerThreads();
		Peon::PeonStealingQueue* stealQueue = m_OwnerSystem->GetJobWorkers()[randomIndex].GetWorkerQueue();
		if (stealQueue == queue)
		{
			// don't try to steal from ourselves
			Yield();
			return nullptr;
		}

		Peon::PeonJob* stolenJob = stealQueue->Steal();
		if (IsEmptyJob(stolenJob))
		{
			// we couldn't steal a job from the other queue either, so we just yield our time slice for now
			Yield();
			return nullptr;
		}

		return stolenJob;
	}

	return job;
}

void Peon::PeonWorker::ExecuteThread(void* _arg)
{
	if (Peon::PeonSystem::ThreadsBlocked())
	{
		Yield();
		return;
	}

	// Try to get a job
	Peon::PeonJob* job = GetJob();
	if (job)
	{

// If debug mode is on
#ifdef JobWorkerDebug

		// Print the function message
		printf("Thread with id %d will run a function with data: %d\n", m_ThreadId, (int)job->m_Data);
	
#endif
		// Run the selected job
		job->RunJobFunction();

		// Finish the job
		job->Finish();
	}
}