#include <stdarg.h>		// for va_<xxx>
#include <stdio.h>		// for vsprintf_s()
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff

#include "..\Syncronization\Mutex.h"
#include "..\Syncronization\ScopeLock.h"

namespace Engine
{
	Engine::Mutex ConsolePrintMutex;

	void ConsolePrint(const char* i_pFmt, const char* i_pFile, unsigned int i_Line, ...)
	{
		ScopeLock Lock(ConsolePrintMutex);

		const size_t		lenTemp = 128;
		char				strTemp[lenTemp] = "DEBUG: %s %u: ";

		strcat_s(strTemp, i_pFmt);

		const size_t		lenOutput = 256;
		char				strOutput[lenOutput];

		// define a variable argument list variable 
		va_list				args;

		// initialize it. second parameter is variable immediately
		// preceding variable arguments
		va_start(args, i_pFmt);

		// (safely) print our formatted string to a char buffer
		vsprintf_s(strOutput, lenOutput, strTemp, args);

		va_end(args);

		OutputDebugStringA(strOutput);
		OutputDebugStringA("\n");
	}
} // namespace Engine