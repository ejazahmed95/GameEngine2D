#include "Application.h"

namespace Raven {
	Application::Application()
	{
		
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		while (true);
	}

	StandardInputReader Application::standardInputReader() const
	{
		return input_reader_;
	}
}

