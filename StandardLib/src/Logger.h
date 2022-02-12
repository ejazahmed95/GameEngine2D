#pragma once
#include "string"
#include "Windows.h"

namespace SLib {
	enum ELogLevel {
		TRACE = 1, // Debugging
		DEBUG = 2, // For Debug Builds
		INFO = 3, // For Release Builds
		WARN = 4, // Warnings to Resolve
		ERR = 5, // Errors
		FATAL = 6 // Should crash the system
	};
	
	static class Log {
	public:
		template<typename... Args>
		void I(Args&&... args) {
			if (level < INFO) return;

			char buffer[100];
			sprintf_s(buffer, 50, "%s %s %s %s", args...);
			OutputDebugStringA(buffer);
		}
	private:
	public:
#ifdef _DEBUG
		ELogLevel level = DEBUG;
#else
		ELogLevel level = INFO;
#endif
	};
}
