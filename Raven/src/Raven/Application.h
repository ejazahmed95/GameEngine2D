#pragma once

#include "Core.h"
#include "Input/StandardInputReader.h"

namespace Raven {
	class RAVEN_API Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void Run();
		virtual void RunWinApp();
		StandardInputReader standardInputReader() const;
	private:
		StandardInputReader input_reader_;
	};

	// To be defined in Client
	Application* CreateApplication();
}
