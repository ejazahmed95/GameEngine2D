#pragma once
#include "Application.h"
#include "RavenStd/Logger.h"
#include "RavenStd/test/Testing.h"
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
		// app->Run();
		delete app;

	}
	_CrtDumpMemoryLeaks();
}

int WINAPI wWinMain(_In_ HINSTANCE i_hInstance, _In_opt_ HINSTANCE i_hPrevInstance, _In_ LPWSTR i_lpCmdLine, _In_ int i_nCmdShow) {
	// _CrtSetBreakAlloc(682);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		// Tests
		RavenStd::TestMatrix();
		RavenStd::TestSIMD();

		// Raven::TEST_Point2DTest();	
		const auto app = Raven::CreateApplication();

		bool success = GLib::Initialize(i_hInstance, i_nCmdShow, "RavenApp", -1, 800, 600, true);
		if (!success) return 0;
		RavenStd::Log::I("GLib Initialized\n");
		app->App_StartGame();
		
		GLib::Shutdown();
		
		delete app;

		//RavenStd::TestStrongWeakPtr();
	}
	// Dump memory leaks is not needed as _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) is set at the start of program
	// _CrtDumpMemoryLeaks();
	return 0;
}

#else
	#error Raven only supports windows!
#endif // PLATFORM_WINDOWS

