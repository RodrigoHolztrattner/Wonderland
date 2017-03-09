////////////////////////////////////////////////////////////////////////////////
// Filename: SystemClass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <pthread.h>
#include "Systems\Job System\JobSystem.h"
#include <iostream>
#include "string"
#include <atomic>
#include <future>

///////////////
// NAMESPACE //
///////////////
using namespace WonderlandTS;

// ThreadTest
namespace System
{
	/////////////
	// DEFINES //
	/////////////

	////////////
	// GLOBAL //
	////////////

	////////////////////////////////////////////////////////////////////////////////
	// Class name: SystemClass
	////////////////////////////////////////////////////////////////////////////////
	class SystemClass
	{
	public:
		SystemClass();
		SystemClass(const SystemClass&);
		~SystemClass();

		void WorkToBeDone(Job* _parentJob, void* _arg)
		{

			// printf("Work done! \n");
			// m_InternalCounterAtomic.fetch_add(m_One, std::memory_order_relaxed);

			std::lock_guard<std::mutex> guard(m_Mutex);
			
			int old = m_InternalCounterLock;
			old += m_One;
			m_InternalCounterLock = old;
			
			
		}

	
		void MainFrame(Job* _parentJob, void* _arg)
		{
			// The number of jobs we will create
			const int totalJobs = 65535;

			// Initialize the internal counter
			m_InternalCounterAtomic = 0;
			m_InternalCounterLock = 0;
			m_One = 1;

			// Block the threads
			JobSystem::BlockThreadsStatus(true);
			
			// Create the root job
			Job* rootJob = JobSystem::CreateJobAsChild(_parentJob, *this, &SystemClass::WorkToBeDone, nullptr);

			for (int i = 0; i < totalJobs; i++)
			{
				Job* newJob = JobSystem::CreateJobAsChild(rootJob, *this, &SystemClass::WorkToBeDone, nullptr);
				JobSystem::StartJob(newJob);
			}

			clock_t begin = clock();

			JobSystem::BlockThreadsStatus(false);
			JobSystem::StartJob(rootJob);
			JobSystem::WaitForJob(rootJob);

			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

			std::cout << "Tempo decorrido: " << elapsed_secs << std::endl;
			std::cout << m_InternalCounterAtomic << std::endl;
			std::cout << m_InternalCounterLock << std::endl;
			int gg;

			std::cin >> gg;

			exit(0);
		}

	private:

		std::atomic<int> m_InternalCounterAtomic;
		int m_InternalCounterLock;
		int m_One;
		std::mutex m_Mutex;
	};
}