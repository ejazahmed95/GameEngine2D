#pragma once

#include "Core.h"

namespace Raven {
	class RAVEN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:

	};

	// To be defined in Client
	Application* CreateApplication();
}
