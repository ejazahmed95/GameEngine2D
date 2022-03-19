#include "JobSystem.h"

#include "File/LoadFile.h"
#include "Threading/Syncronization/Events.h"
#include "Types/HashedString.h"

#include <assert.h>
#include <string>
#include <vector>
#include <functional>

#include <stdint.h>

namespace Engine
{
	static void ProcessFileContents(std::vector<uint8_t> i_Contents, std::function<void(std::vector<uint8_t>)> i_Processor, Engine::Event* i_pFinishEvent = nullptr)
	{
		if (!i_Contents.empty())
		{
			if (!Engine::JobSystem::ShutdownRequested())
				i_Processor(i_Contents);
		}

		if (i_pFinishEvent)
			i_pFinishEvent->Signal();
	}

	void ProcessFileAsync(const std::string& i_Filename, std::function<void(std::vector<uint8_t>)> i_Processor, JobSystem::JobData i_JobData)
	{
		Engine::JobSystem::RunJob("ProcessFile", [i_Filename, i_Processor, i_JobData]()
		{
			std::vector<uint8_t> Contents = LoadFile(i_Filename);

			if (!Contents.empty())
			{
				if (!Engine::JobSystem::ShutdownRequested())
				{
					// this works around C++11 issue with capturing member variable by value
					std::function<void(std::vector<uint8_t>)> Processor = i_Processor;

					Engine::JobSystem::RunJob("ProcessFileContents", [Contents, Processor]()
					{
						ProcessFileContents(Contents, Processor);
					}
					, i_JobData);
				}
			} }
		, i_JobData);
	}

} // namespace Engine

