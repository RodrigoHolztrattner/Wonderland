////////////////////////////////////////////////////////////////////////////////
// Filename: __InternalPeonJob.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <atomic>
#include <pthread.h>
#include <functional>

/////////////
// DEFINES //
/////////////

#define NamespaceBegin(name) namespace name {
#define NamespaceEnd(name) }

// Return if a job is done
#define HasJobCompleted(job)	((job->GetTotalUnfinishedJobs()) <= 0)

///////////////
// NAMESPACE //
///////////////

// __InternalPeon
NamespaceBegin(__InternalPeon)

// WorkerThread class
class __InternalPeonWorker;

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: __InternalPeonJob
////////////////////////////////////////////////////////////////////////////////
class __InternalPeonJob
{
public:
	__InternalPeonJob();
	__InternalPeonJob(const __InternalPeonJob&);
	~__InternalPeonJob();

	// Initialize the job
	bool Initialize()
	{
		// Set the initial data
		m_CurrentWorkerThread = nullptr;
		m_ParentJob = nullptr;
		m_UnfinishedJobs = 1;

		return true;
	}

	// Set the job function (syntax: (*MEMBER, &MEMBER::FUNCTION, DATA))
	void SetJobFunction(__InternalPeonJob* _parentJob, std::function<void()> _function)
	{
		using namespace std::placeholders; // for `_1`

		// Set the function and the data
		m_Function = _function;

		// Set the current worker thread
		m_ParentJob = _parentJob;
	}

	// Finish this job
	void Finish();

	// Run the job function
	void RunJobFunction()
	{
		m_Function();
	}

	// Return the parent job
	__InternalPeonJob* GetParent()
	{
		return m_ParentJob;
	}

	// Set the worker thread
	void SetWorkerThread(__InternalPeon::__InternalPeonWorker* _workerThread)
	{
		m_CurrentWorkerThread = _workerThread;
	}

	// Return the worker thread
	__InternalPeon::__InternalPeonWorker* GetWorkerThread()
	{
		// Set the current job
		__InternalPeonJob* currentJob = this;

		// Check if this job is the root one
		while (currentJob->GetParent() != nullptr)
		{
			// Iterate until we find the root job
			currentJob = currentJob->GetParent();
		}

		return currentJob->m_CurrentWorkerThread;
	}

	// Set the parent job
	void SetParentJob(__InternalPeonJob* _job)
	{
		m_ParentJob = _job;
	}

	// Return the number of unfinished jobs
	int32_t GetTotalUnfinishedJobs()
	{
		return m_UnfinishedJobs;
	}

protected:

	// The job function and data
	std::function<void()> m_Function;

	// The parent job
	__InternalPeonJob* m_ParentJob;

	// The current worker thread
	__InternalPeon::__InternalPeonWorker* m_CurrentWorkerThread;

public: // Arrumar public / private

	// The number of unfinished jobs
	std::atomic<int> m_UnfinishedJobs;
};

static bool IsEmptyJob(__InternalPeonJob* _job)
{
	return _job == nullptr ? true : false;
}

// __InternalPeon
NamespaceEnd(__InternalPeon)