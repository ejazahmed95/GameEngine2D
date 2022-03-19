#pragma once

#include "SharedJobQueue.h"

namespace Engine
{
	namespace JobSystem
	{

		struct JobRunnerInput
		{
			SharedJobQueue* m_pQueue;
#ifdef _DEBUG
			std::string		m_ThreadName;
#endif
			JobRunnerInput(SharedJobQueue& i_Queue) :
				m_pQueue(&i_Queue)
			{}
		};

		DWORD WINAPI JobRunner(void* i_pJobRunnerInput);

	} // namespace JobSystem
} // namespace Engine
