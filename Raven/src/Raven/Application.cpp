#include "Application.h"

namespace Raven {
	Application::Application() = default;

	Application::~Application() = default;

	void Application::Run() {
		while (true);
	}

	void Application::RunWinApp() {
		while (true);
	}

	StandardInputReader Application::standardInputReader() const
	{
		return input_reader_;
	}
}

