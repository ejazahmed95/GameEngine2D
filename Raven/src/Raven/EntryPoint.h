#pragma once
#include "Application.h"

#ifdef PLATFORM_WINDOWS

extern Raven::Application* Raven::CreateApplication();

int main(int argc, char** argv) {
	// _CrtSetBreakAlloc(173);
	{
		const auto app = Raven::CreateApplication();
		app->Run();
		delete app;
	}
	_CrtDumpMemoryLeaks();
}

#else
	#error Raven only supports windows!
#endif // PLATFORM_WINDOWS

