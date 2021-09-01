#pragma once
#include "Application.h"

#ifdef PLATFORM_WINDOWS
	
extern Raven::Application* Raven::CreateApplication();

int main(int argc, char** argv) {
	auto app = Raven::CreateApplication();
	app->Run();
	delete app;
}
#endif // PLATFORM_WINDOWS

