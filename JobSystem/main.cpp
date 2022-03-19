#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG

#include <conio.h>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include "JobSystem/JobSystem.h"
#include "Syncronization/Events.h"

#include "HashedString\HashedString.h"

void BasicSample();
void GameObjectSample();

int main(int i_argc, char** i_argl)
{
#if defined _DEBUG
	_CrtSetBreakAlloc(159);
#endif // _DEBUG
	{

	Engine::JobSystem::Init();

	BasicSample();
	GameObjectSample();

	Engine::JobSystem::RequestShutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;

}

void ProcessFileContents(uint8_t* i_pFileContents, size_t i_sizeFileContents, std::function<void(uint8_t*, size_t)> i_Processor)
{
	if (i_pFileContents)
	{
		if (i_sizeFileContents  && !Engine::JobSystem::ShutdownRequested())
			i_Processor(i_pFileContents, i_sizeFileContents);
	}

	delete[] i_pFileContents;

	std::cout << "ProcessFileContents finished processing file.\n";
}

class ProcessFile
{
public:
	ProcessFile(const char* i_pFilename, std::function<void(uint8_t*, size_t)> i_Processor, const Engine::HashedString i_QueueName = Engine::JobSystem::GetDefaultQueue(), Engine::JobSystem::JobStatus* i_pJobStatus = nullptr) :
		m_pFilename(i_pFilename),
		m_Processor(i_Processor),
		m_QueueName(i_QueueName),
		m_pJobStatus(i_pJobStatus)
	{
		assert(m_pFilename);
	}

	void operator() ()
	{
		if (m_pFilename)
		{
			size_t sizeFileContents = 0;
			uint8_t* pFileContents = LoadFile(m_pFilename, sizeFileContents);

			if (pFileContents && sizeFileContents)
			{
				if (!Engine::JobSystem::ShutdownRequested())
				{
					std::cout << "ProcessFile finished loading file.\n";

					// this works around C++11 issue with capturing member variable by value
					std::function<void(uint8_t*, size_t)> Processor = m_Processor;

					Engine::JobSystem::RunJob(
						m_QueueName,
						[pFileContents, sizeFileContents, Processor]()
						{
							ProcessFileContents(pFileContents, sizeFileContents, Processor);
					},
					m_pJobStatus,
					"ProcessFileContents"						
					);
				}
				else
				{
					delete[] pFileContents;
				}
			}
		}
	}

	static uint8_t* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
	{
		assert(i_pFilename != NULL);

		FILE* pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;

		assert(pFile != NULL);

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(FileIOError == 0);

		long FileSize = ftell(pFile);
		assert(FileSize >= 0);

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(FileIOError == 0);

		uint8_t* pBuffer = new uint8_t[FileSize];
		assert(pBuffer);

		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		assert(FileRead == FileSize);

		fclose(pFile);

		o_sizeFile = FileSize;

		return pBuffer;
	}
private:
	const char* m_pFilename;
	std::function<void(uint8_t*, size_t)>  m_Processor;
	Engine::HashedString m_QueueName;
	Engine::JobSystem::JobStatus* m_pJobStatus;
};

void PrintFileContents(uint8_t* i_pFileContents, size_t i_sizeFileContents)
{
	assert(i_pFileContents && i_sizeFileContents);

	std::cout << "File Contents:\n";
	while (i_sizeFileContents--)
		std::cout << *(i_pFileContents++);

	std::cout << "\n";
}

void PrintOnInterval(std::string i_String, unsigned int i_IntervalMilliseconds, unsigned int i_Count = 1)
{
	bool bCounted = i_Count > 0;

	do
	{
		std::cout << i_String << "\n";
		Sleep(i_IntervalMilliseconds);
	} while ((!bCounted || (bCounted && --i_Count)) && !Engine::JobSystem::ShutdownRequested());
}

void BasicSample()
{
	using namespace std::placeholders;

	{
		// use a lambda function to run a job
		Engine::JobSystem::JobStatus JobStatus;

		Engine::JobSystem::RunJob(
			Engine::JobSystem::GetDefaultQueueName(),
			[]()
			{
				PrintOnInterval("Wahoo!!", 500, 10);
			},
			&JobStatus
		);

		JobStatus.WaitForZeroJobsLeft();
	}

	{
		Engine::JobSystem::JobStatus JobStatus;

		// use std::bind to bind a function to a std::function
		// _1 and _2 are placeholders that get replaced when actually executing the function
		ProcessFile ProcessFileInstance("File.txt", std::bind(PrintFileContents, _1, _2), Engine::JobSystem::GetDefaultQueue(), &JobStatus);

		// use std::bind to bind an instance of a class that has operator() () (a functor)
		Engine::JobSystem::RunJob(Engine::JobSystem::GetDefaultQueue(), std::bind(ProcessFileInstance), &JobStatus);

		// wait for FinishEvent to be signaled
		JobStatus.WaitForZeroJobsLeft();

		std::cout << "ProcessFile finished running.\n";
	}

}

#include "Syncronization/Mutex.h"
#include "Syncronization/ScopeLock.h"

// a super basic GameObject
class GameObject
{
public:
	GameObject(const std::string& i_Name) :
		m_Name(i_Name)
	{
	}
	
	std::string GetName() const { return m_Name;  }

private:
	std::string	m_Name;
};

// this is our master list of GameObjects
std::vector<GameObject*> AllGameObjects;

// this is the list of new GameObjects created via our JobSystem (on other threads)
std::vector<GameObject*> NewGameObjects;
// This is the mutex we use to guard against accessing NewGameObjects simultaneously on multiple threads
Engine::Mutex NewGameObjectMutex;

// This adds a new GameObject to NewGameObjects
void AddNewGameObject(GameObject* i_pNewGameObject)
{
	if (i_pNewGameObject)
	{
		// Acquire a scoped lock on the mutex
		Engine::ScopeLock Lock(NewGameObjectMutex);
		
		NewGameObjects.push_back(i_pNewGameObject);
	}
}

// This will move GameObjects from NewGameObjects -> AllGameObjects
void CheckForNewGameObjects()
{
	Engine::ScopeLock Lock(NewGameObjectMutex);

	if (!NewGameObjects.empty())
	{
		for (GameObject* p : NewGameObjects)
		{
			if (p)
			{
				std::cout << "Moving " << p->GetName() << " to AllObjects.\n";
				AllGameObjects.push_back(p);
			}
		}

		NewGameObjects.clear();
	}
}

// Helper function to create new GameObjects from a list of names in a text file
void CreateGameObjects(uint8_t* i_pFileContents, size_t i_sizeFileContents)
{
	assert(i_pFileContents && i_sizeFileContents);

	uint8_t* pEndFileContents = i_pFileContents + i_sizeFileContents;

	while (i_pFileContents < pEndFileContents)
	{
		size_t NameLength = 0;
		const char* i_pNextName = reinterpret_cast<const char*>(i_pFileContents);
		
		while ((i_pFileContents < pEndFileContents) && *i_pFileContents++ != '\r')
			NameLength++;

		if (NameLength)
		{
			std::string Name(i_pNextName, NameLength);
			AddNewGameObject(new GameObject(Name));
		}

		i_pFileContents++;
	}
}

void GameObjectSample()
{
	using namespace std::placeholders;

	{
		const char* CustomQueueName = "GameObjectLoader";

		Engine::HashedString QueueName = Engine::JobSystem::CreateQueue(CustomQueueName, 2);

		{
			Engine::JobSystem::RunJob(QueueName, std::bind(ProcessFile("GameObjects.txt", std::bind(CreateGameObjects, _1, _2))));

			do
			{
				CheckForNewGameObjects();
				Sleep(10);
			} while (Engine::JobSystem::HasJobs(CustomQueueName));
		}
		CheckForNewGameObjects();
	}

	{
		for (GameObject* p : AllGameObjects)
		{
			if (p)
				delete p;
		}

		AllGameObjects.clear();
	}
}