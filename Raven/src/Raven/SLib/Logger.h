#pragma once
#include "string"
#include "Windows.h"

namespace SLib {
	enum class ELogLevel {
		TRACE = 1, // Debugging
		DEBUG = 2, // For Debug Builds
		INFO = 3, // For Release Builds
		WARN = 4, // Warnings to Resolve
		ERR = 5, // Errors
		FATAL = 6 // Should crash the system
	};
	
	static class Log {
	public:
		// template<typename... Args>
		static void I(std::string arg) {
			if (level > ELogLevel::INFO) return;

			char buffer[100];
			sprintf_s(buffer, 100, "[INFO] %s\n", arg.c_str());
			OutputDebugStringA(buffer);
		}

		static void D(std::string arg) {
			if (level > ELogLevel::DEBUG) return;

			char buffer[400];
			sprintf_s(buffer, 100, "[DEBUG] %s\n", arg.c_str());
			OutputDebugStringA(buffer);
		}
	private:
		//static void log(std::string& arg) {}
	public:
#ifdef _DEBUG
		static ELogLevel level;
#else
		static ELogLevel level;
#endif
	};
}
