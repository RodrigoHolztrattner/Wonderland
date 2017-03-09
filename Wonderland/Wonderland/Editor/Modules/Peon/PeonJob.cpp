////////////////////////////////////////////////////////////////////////////////
// Filename: __InternalPeonJob.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PeonJob.h"
#include "PeonWorker.h"

///////////////
// NAMESPACE //
///////////////

__InternalPeon::__InternalPeonJob::__InternalPeonJob()
{
}

__InternalPeon::__InternalPeonJob::__InternalPeonJob(const __InternalPeonJob& other)
{
}

__InternalPeon::__InternalPeonJob::~__InternalPeonJob()
{
}

void __InternalPeon::__InternalPeonJob::Finish()
{
	// Decrement the number of unfinished jobs
	m_UnfinishedJobs--;
	const int32_t unfinishedJobs = m_UnfinishedJobs;

	// Check if there are no jobs remaining
	if (!unfinishedJobs)
	{
		// If we dont have any remaining jobs, we can decrement the number of jobs from our parent
		// (if we have one).
		if (m_ParentJob)
		{
			// Call the finish job for our parent
			m_ParentJob->Finish();
		}
	}
}