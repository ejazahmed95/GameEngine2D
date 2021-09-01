#pragma once

#ifdef PLATFORM_WINDOWS
	#ifdef RAVEN_BUILD_DLL
		#define RAVEN_API _declspec(dllexport) // Engine Code
	#else
		#define RAVEN_API _declspec(dllimport) // Application Code
	#endif // RAVEN
#else
	#error Raven only supports windows!
#endif