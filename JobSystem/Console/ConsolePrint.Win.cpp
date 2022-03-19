
#include "Threading/Syncronization/Mutex.h"
#include "Threading/Syncronization/ScopeLock.h"

#include <assert.h>		// for assert()
#include <stdarg.h>		// for va_<xxx>
#include <stdio.h>		// for vsprintf_s()

#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff

namespace Engine
{
	void ConsolePrint(const char* i_fmt, ...)	
	{
		static Mutex PrintLock;

		assert(i_fmt);
		ScopeLock Lock(PrintLock);

		const size_t lenTemp = 2048;
		char strTemp[lenTemp] = "DEBUG: ";

		strcat_s(strTemp, i_fmt);
		strcat_s(strTemp, "\n");

		const size_t lenOutput = lenTemp + 32;

		char strOutput[lenOutput];

		// define a variable argument list variable 
		va_list args;

		// initialize it. second parameter is variable immediately
		// preceeding variable arguments
		va_start(args, i_fmt);

		// (safely) print our formatted string to a char buffer
		vsprintf_s(strOutput, lenOutput, strTemp, args);

		va_end(args);

		OutputDebugStringA(strOutput);
	}

} // namespace Engine