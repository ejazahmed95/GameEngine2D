#pragma once

#include <functional>
#include <string>

#include "JobStatus.h"
#include "..\HashedString\HashedString.h"
#include "..\Syncronization\Events.h"

namespace Engine
{
	namespace JobSystem
	{
		void Init();

		HashedString GetDefaultQueue();

		inline const char *GetDefaultQueueName() noexcept {
			static char DefaultQueueName[] = "Default";
			return DefaultQueueName;
		}

		inline HashedString GetDefaultQueue() {
			return HashedString(GetDefaultQueueName());
		}
		HashedString CreateQueue(const std::string& i_Name, unsigned int i_numRunners);

		void RunJob(const HashedString& i_QueueName, std::function<void()> i_JobFunction, JobStatus* i_pJobStatus = nullptr, const char* pJobName = nullptr);
		bool HasJobs( const HashedString& i_QueueName);

		void RequestShutdown();
		bool ShutdownRequested();

	} // namespace JobSystem
} // namespace Engine
