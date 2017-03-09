////////////////////////////////////////////////////////////////////////////////
// Filename: PeonJob.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PeonJob.h"
#include "PeonWorker.h"

///////////////
// NAMESPACE //
///////////////

Peon::PeonJob::PeonJob()
{
}

Peon::PeonJob::PeonJob(const PeonJob& other)
{
}

Peon::PeonJob::~PeonJob()
{
}

void Peon::PeonJob::Finish()
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