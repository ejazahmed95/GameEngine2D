#include "JobSystem.h"

#include <Windows.h>
#include <map>

#include "..\Console\ConsolePrint.h"
#include "..\HashedString\HashedString.h"

#include "JobRunner.h"
#include "SharedJobQueue.h"

namespace Engine
{
	namespace JobSystem
	{
		struct JobRunnerData
		{
			JobRunnerInput		m_Input;
			HANDLE				m_ThreadHandle;
			DWORD				m_ThreadID;
			JobRunnerData(SharedJobQueue& i_Queue) :
				m_Input(i_Queue),
				m_ThreadHandle(INVALID_HANDLE_VALUE),
				m_ThreadID(-1)
			{}
		};

		struct JobQueueData
		{
			SharedJobQueue		m_SharedQueue;
			std::vector<JobRunnerData*>	m_Runners;

			JobQueueData(const std::string& i_QueueName) :
				m_SharedQueue(i_QueueName)
			{
			}
		};

		bool bShutdownRequested = false;
		std::map<HashedString, JobQueueData*>	Queues;

		void RequestShutdown()
		{
			DEBUG_PRINT("Job System: Shutting down.");

			bShutdownRequested = true;

			std::vector<HANDLE>	AllThreads;

			std::map<HashedString, JobQueueData*>::iterator iter = Queues.begin();
			while (iter != Queues.end())
			{
				if (iter->second)
				{
					iter->second->m_SharedQueue.RequestShutdown();

					const size_t count = iter->second->m_Runners.size();
					for (size_t i = 0; i < count; i++)
					{
						JobRunnerData* pRunner = iter->second->m_Runners[i];
						if (pRunner && pRunner->m_ThreadHandle != NULL)
						{
							AllThreads.push_back(pRunner->m_ThreadHandle);
						}
					}
				}
				++iter;
			}

			DEBUG_PRINT("Job System: Waiting for Queue runner threads to shut down.");

			DWORD result = WaitForMultipleObjects(static_cast<DWORD>(AllThreads.size()), &AllThreads[0], TRUE, INFINITE);
			assert(result == WAIT_OBJECT_0);

			iter = Queues.begin();
			while (iter != Queues.end())
			{
				if (iter->second)
				{
					const size_t count = iter->second->m_Runners.size();
					for (size_t i = 0; i < count; i++)
					{
						JobRunnerData* pRunner = iter->second->m_Runners[i];
						if (pRunner)
							delete pRunner;
					}

					delete iter->second;
				}

				++iter;
			}

			Queues.clear();

		}

		bool ShutdownRequested()
		{
			return bShutdownRequested;
		}

		void AddRunner(JobQueueData& i_QueueData)
		{
			size_t runners = i_QueueData.m_Runners.size();

			JobRunnerData* pNewRunner = new JobRunnerData(i_QueueData.m_SharedQueue);

#ifdef _DEBUG
			const size_t	sizeThreadName = 32;
			char			ThreadName[sizeThreadName];
			sprintf_s(ThreadName, sizeThreadName, "%s %d", i_QueueData.m_SharedQueue.GetName().c_str(), int(runners + 1));
			pNewRunner->m_Input.m_ThreadName = ThreadName;
#endif

			pNewRunner->m_ThreadHandle = CreateThread(NULL, 0, JobRunner, &pNewRunner->m_Input, CREATE_SUSPENDED, &pNewRunner->m_ThreadID);
			assert(pNewRunner->m_ThreadHandle != NULL);

			i_QueueData.m_Runners.push_back(pNewRunner);
			ResumeThread(pNewRunner->m_ThreadHandle);
		}

		void AddRunner(const HashedString& i_QueueName)
		{
			std::map<HashedString, JobQueueData*>::iterator existing = Queues.find(i_QueueName);
			assert(existing != Queues.end());
			assert(existing->second);

			AddRunner(*existing->second);
		}

		HashedString CreateQueue(const std::string& i_Name, unsigned int i_numRunners)
		{
			HashedString	HashedName(i_Name.c_str());

			assert(Queues.find(HashedName) == Queues.end());

			JobQueueData* pNewJobQueueData = new JobQueueData(i_Name);

			Queues[HashedName] = pNewJobQueueData;

			for (unsigned int i = 0; i < i_numRunners; i++)
				AddRunner(*pNewJobQueueData);

			return HashedName;
		}

		bool HasJobs(const HashedString& i_QueueName)
		{
			std::map<HashedString, JobQueueData*>::iterator existing = Queues.find(i_QueueName);
			if (existing != Queues.end())
			{
				if (existing->second)
					return existing->second->m_SharedQueue.HasJobs();
			}

			return false;
		}

		void RunJob(const HashedString& i_QueueName, std::function<void()> i_JobFunction, JobStatus* i_pJobStatus, const char* i_pJobName)
		{
			std::map<HashedString, JobQueueData*>::iterator existing = Queues.find(i_QueueName);
			assert(existing != Queues.end());
			assert(existing->second);

			DEBUG_PRINT("Job System: Adding Job to Queue \"%s\".", existing->second->m_SharedQueue.GetName().c_str());
			existing->second->m_SharedQueue.Add(new QueuedJob(i_JobFunction, i_QueueName, i_pJobName ? i_pJobName : std::string(), i_pJobStatus));
		}

		void Init()
		{
			CreateQueue(GetDefaultQueueName(), 2);
		}

	} // namespace JobSystem
} // namespace Engine

