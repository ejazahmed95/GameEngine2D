#include "JobRunner.h"

#include <assert.h>

#include "JobSystem.h"
#include "..\Console\ConsolePrint.h"

namespace Engine
{
	namespace JobSystem
	{

		DWORD WINAPI JobRunner(void* i_pThreadInput)
		{
			assert(i_pThreadInput);

			JobRunnerInput* pInput = reinterpret_cast<JobRunnerInput*>(i_pThreadInput);
			assert(pInput->m_pQueue);

			DEBUG_PRINT("JobRunner \"%s\": Starting Queue \"%s\".", pInput->m_ThreadName.c_str(), pInput->m_pQueue->GetName().c_str());

			bool bDone = false;

			do
			{
				DEBUG_PRINT("JobRunner \"%s\": Acquiring Job.", pInput->m_ThreadName.c_str());
				QueuedJob* pJob = pInput->m_pQueue->GetWhenAvailable();
				if (pJob)
				{
					DEBUG_PRINT("JobRunner \"%s\": Starting Job \"%s\" on Processor %d.", pInput->m_ThreadName.c_str(), pJob->JobName.c_str(), GetCurrentProcessorNumber());
					pInput->m_pQueue->StartingJob(pJob);
					pJob->Function();

					DEBUG_PRINT("JobRunner \"%s\": Finished Job \"%s\".", pInput->m_ThreadName.c_str(), pJob->JobName.c_str());
					pInput->m_pQueue->FinishedJob(pJob);
				}

				bDone = pInput->m_pQueue->ShutdownRequested();

			} while (bDone == false);

#ifdef _DEBUG
			DEBUG_PRINT("JobRunner \"%s\": Shutting down.", pInput->m_ThreadName.c_str());
#endif
			return 0;
		}

	} // namespace JobSystem
} // namespace Engine
