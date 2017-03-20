////////////////////////////////////////////////////////////////////////////////
// Filename: __InternalPeonWorker.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PeonWorker.h"
#include "PeonSystem.h"

__InternalPeon::__InternalPeonWorker::__InternalPeonWorker()
{
}

__InternalPeon::__InternalPeonWorker::__InternalPeonWorker(const __InternalPeon::__InternalPeonWorker& other)
{
}

__InternalPeon::__InternalPeonWorker::~__InternalPeonWorker()
{
}

#ifdef JobWorkerDebug
static unsigned int JobWorkerId = 0;
#endif



void __InternalPeon::__InternalPeonWorker::SetQueueSize(unsigned int _jobBufferSize)
{
	// Initialize our concurrent queue
	m_WorkQueue = new moodycamel::ConcurrentQueue<__InternalPeon::__InternalPeonJob*>(_jobBufferSize);

	// Initialize our job free list
	m_JobFreeList = new __InternalPeon::__InternalPeonJob[_jobBufferSize]();
	m_JobFreeListPosition = 0;
	m_JobFreeListMax = _jobBufferSize;
}

bool __InternalPeon::__InternalPeonWorker::Initialize(__InternalPeon::__InternalPeonSystem* _ownerSystem, int _threadId, bool _mainThread)
{
	// pthread_t thread;

	// Set the thread id and owner system
	m_ThreadId = _threadId;
	m_OwnerSystem = _ownerSystem;



	// 
	std::cout << "Thread with id: " << m_ThreadId << " created" << std::endl;

	// ?????????
	// Check if this worker thread is the main one
	if (!_mainThread)
	{
		// Create the new thread
		std::thread* t = new std::thread(&__InternalPeonWorker::ExecuteThreadAux, this);
	}

	return true;
}


void __InternalPeon::__InternalPeonWorker::ExecuteThreadAux()
{
	// Set the global per thread id
	__InternalPeon::CurrentThreadIdentifier = m_ThreadId;

	// Run the execute function
	while (true)
	{
		ExecuteThread(nullptr);
	}
}

thread_local __InternalPeon::__InternalPeonJob*	CurrentThreadJob;

void __InternalPeon::__InternalPeonWorker::ExecuteThread(void* _arg)
{
	if (__InternalPeon::__InternalPeonSystem::ThreadsBlocked())
	{
		Yield();
		return;
	}

	// Try to get a job
	__InternalPeon::__InternalPeonJob* job = nullptr;
	bool result = GetJob(&job);
	if (result)
	{

// If debug mode is on
#ifdef JobWorkerDebug

		// Print the function message
		printf("Thread with id %d will run a function", m_ThreadId);
	
#endif

		// Set the current job for this thread
		CurrentThreadJob = job;

		// Run the selected job
		job->RunJobFunction();

		// Finish the job
		job->Finish();
	}
}


__InternalPeon::__InternalPeonJob* __InternalPeon::__InternalPeonWorker::GetCurrentJob()
{
	return CurrentThreadJob;
}

bool __InternalPeon::__InternalPeonWorker::GetJob(__InternalPeon::__InternalPeonJob** _job)
{
	bool result				= {};
	
	// Primeira coisa, vamos ver se conseguimos pegar algum work do nosso queue interno
	result = m_WorkQueue->try_dequeue(*_job);
	if (result)
	{
		// Conseguimos! Retornamos ele agora
		return true;
	}

	// Primeiramente pegamos um index aleatório de alguma thread e a array de threads
	unsigned int randomIndex = rand() % m_OwnerSystem->GetTotalWorkerThreads();
	__InternalPeon::__InternalPeonWorker* workers = m_OwnerSystem->GetJobWorkers();

	// Pegamos então o queue desta thread aleatória
	moodycamel::ConcurrentQueue<__InternalPeon::__InternalPeonJob*>* stolenQueue = workers[randomIndex].GetWorkerQueue();

	// Verificamos se não estamos roubando de nós mesmos
	if (stolenQueue == m_WorkQueue)
	{
		Yield();
		return false;
	}

	// Roubamos então um work desta thread
	result = stolenQueue->try_dequeue(*_job);
	if (!result)
	{
		// Não foi possível roubar um work desta thread, melhor parar por aqui!
		Yield();
		return false;
	}

	// Conseguimos roubar um work!
	return true;
}