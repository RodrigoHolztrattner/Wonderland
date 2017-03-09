////////////////////////////////////////////////////////////////////////////////
// Filename: PeonJob.h
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

// Peon
NamespaceBegin(Peon)

// WorkerThread class
class PeonWorker;

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: PeonJob
////////////////////////////////////////////////////////////////////////////////
class PeonJob
{
public:
	PeonJob();
	PeonJob(const PeonJob&);
	~PeonJob();

	// Initialize the job
	bool Initialize()
	{
		// Set the initial data
		m_CurrentWorkerThread = nullptr;
		m_ParentJob = nullptr;
		m_Data = nullptr;
		m_UnfinishedJobs = 1;

		return true;
	}

	// Set the job function (syntax: (*MEMBER, &MEMBER::FUNCTION, DATA))
	template <class CallType>
	void SetJobFunction(PeonJob* _parentJob, CallType& _member, void (CallType::* const &_function)(PeonJob*, void*), void* _data)
	{
		using namespace std::placeholders; // for `_1`

		// Set the function and the data
		m_Function = std::bind(_function, &_member, _1, _2);
		m_Data = _data;

		// Set the current worker thread
		m_ParentJob = _parentJob;
	}

	// Finish this job
	void Finish();

	// Run the job function
	void RunJobFunction()
	{
		m_Function(this, m_Data);
	}

	// Return the parent job
	PeonJob* GetParent()
	{
		return m_ParentJob;
	}

	// Set the worker thread
	void SetWorkerThread(Peon::PeonWorker* _workerThread)
	{
		m_CurrentWorkerThread = _workerThread;
	}

	// Return the worker thread
	Peon::PeonWorker* GetWorkerThread()
	{
		// Set the current job
		PeonJob* currentJob = this;

		// Check if this job is the root one
		while (currentJob->GetParent() != nullptr)
		{
			// Iterate until we find the root job
			currentJob = currentJob->GetParent();
		}

		return currentJob->m_CurrentWorkerThread;
	}

	// Set the parent job
	void SetParentJob(PeonJob* _job)
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
	std::function<void(PeonJob*, void*)> m_Function;
public : void* m_Data;

	// The parent job
	PeonJob* m_ParentJob;

	// The current worker thread
	Peon::PeonWorker* m_CurrentWorkerThread;

public: // Arrumar public / private

	// The number of unfinished jobs
	std::atomic<int> m_UnfinishedJobs;
};

static bool IsEmptyJob(PeonJob* _job)
{
	return _job == nullptr ? true : false;
}

// Peon
NamespaceEnd(Peon)