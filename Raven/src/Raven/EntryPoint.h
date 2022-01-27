#pragma once
#include "Application.h"
// #include "../../test/Point2DTest.h"

#ifdef PLATFORM_WINDOWS

extern Raven::Application* Raven::CreateApplication();

#include "Windows.h"
#include "GLib.h"

int main(int argc, char** argv) {
	// _CrtSetBreakAlloc(173);
	{
		// Raven::TEST_Point2DTest();
		const auto app = Raven::CreateApplication();
		app->Run();
		delete app;

	}
	_CrtDumpMemoryLeaks();
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow) {
	// _CrtSetBreakAlloc(173);
	{
		// Raven::TEST_Point2DTest();
		const auto app = Raven::CreateApplication();
		bool success = GLib::Initialize(i_hInstance, i_nCmdShow, "RavenApp", -1, 800, 600, true);
		if (!success) return 0;

		//GLib::SetKeyStateChangeCallback(TestKeyCallback);

		app->RunWinApp();
		GLib::Shutdown();
		delete app;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

#else
	#error Raven only supports windows!
#endif // PLATFORM_WINDOWS

