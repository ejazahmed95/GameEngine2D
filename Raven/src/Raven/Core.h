#pragma once
#if 0
	#ifdef PLATFORM_WINDOWS
		#ifdef RAVEN_BUILD_DLL
			#define RAVEN_API _declspec(dllexport) // Engine Code
		#else
			#define RAVEN_API _declspec(dllimport) // Application Code
		#endif // RAVEN
	#else
		#error Raven only supports windows!
	#endif
#endif

#ifndef RAVEN_API
	#define RAVEN_API
#endif

