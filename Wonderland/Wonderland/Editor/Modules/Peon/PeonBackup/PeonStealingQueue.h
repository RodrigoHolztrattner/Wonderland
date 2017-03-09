////////////////////////////////////////////////////////////////////////////////
// Filename: PeonStealingQueue.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <pthread.h>
#include "PeonJob.h"
#include <vector>

///////////////
// NAMESPACE //
///////////////

// Peon
NamespaceBegin(Peon)

/////////////
// DEFINES //
/////////////


////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: PeonStealingQueue
////////////////////////////////////////////////////////////////////////////////
class PeonStealingQueue
{
public:
	PeonStealingQueue();
	PeonStealingQueue(const PeonStealingQueue&);
	~PeonStealingQueue();

	// Initialize the work stealing queue
	bool Initialize(unsigned int _jobBufferSize)
	{
		// Set the size and allocate the ring buffer
		m_JobBufferSize = _jobBufferSize;
		m_JobRingBuffer = new PeonJob[m_JobBufferSize];

		// Alocate the deque buffer
		m_JobDequeBuffer = new PeonJob*[m_JobBufferSize];

		// Set the initial position
		m_JobRingBufferPosition = 0;

		// Set the top and bottom positions
		m_Top = 0;
		m_Bottom = 0;

		return true;
	}

	// Return a valid job from our ring buffer
	PeonJob* GetFreshJob()
	{
		// Get the job
		PeonJob* temp = &m_JobRingBuffer[m_JobRingBufferPosition];

		// Increment the position
		m_JobRingBufferPosition++;

		// Check if we overlap
		if (m_JobRingBufferPosition >= m_JobBufferSize)
		{
			// Zero the position
			m_JobRingBufferPosition = 0;
		}

		return temp;
	}

	void Push(PeonJob* _job)
	{
		long b = m_Bottom;

		// Push the job
		m_JobDequeBuffer[b & (m_JobBufferSize - 1)] = _job;

		// ensure the job is written before b+1 is published to other threads.
		// on x86/64, a compiler barrier is enough.
		_ReadWriteBarrier(); // COMPILER_BARRIER

		m_Bottom = b + 1;
	}

	PeonJob* Pop()
	{
		long b = m_Bottom - 1;

		_InterlockedExchange(&m_Bottom, b);

		long t = m_Top;
		if (t <= b)
		{
			// non-empty queue
			PeonJob* job = m_JobDequeBuffer[b & (m_JobBufferSize - 1)];
			if (t != b)
			{
				// there's still more than one item left in the queue
				return job;
			}

			// this is the last item in the queue
			if (_InterlockedCompareExchange(&m_Top, t + 1, t) != t)
			{
				// failed race against steal operation
				job = nullptr;
			}

			m_Bottom = t + 1;
			return job;
		}
		else
		{
			// deque was already empty
			m_Bottom = t;
			return nullptr;
		}
	}

	PeonJob* Steal()
	{
		long t = m_Top;

		// ensure that top is always read before bottom.
		// loads will not be reordered with other loads on x86, so a compiler barrier is enough.
		_ReadWriteBarrier(); // COMPILER_BARRIER

		long b = m_Bottom;
		if (t < b)
		{
			// non-empty queue
			PeonJob* job = m_JobDequeBuffer[t & (m_JobBufferSize - 1)];

			// the interlocked function serves as a compiler barrier, and guarantees that the read happens before the CAS.
			if (_InterlockedCompareExchange(&m_Top, t + 1, t) != t)
			{
				// a concurrent steal or pop operation removed an element from the deque in the meantime.
				return nullptr;
			}

			return job;
		}
		else
		{
			// empty queue
			return nullptr;
		}
	}

private:

	// The job deque buffer
	PeonJob** m_JobDequeBuffer;

	// The top and bottom deque positions
	volatile long m_Top;
	volatile long m_Bottom;

	// The job buffer size (for the deque and the ring buffer)
	unsigned int m_JobBufferSize;

	// The job ring buffer
	PeonJob* m_JobRingBuffer;

	// The job ring buffer position
	unsigned int m_JobRingBufferPosition;
};

// Peon
NamespaceEnd(Peon)