#pragma once

#if defined(__MSC_VER)
#define BREAK_IN_DEBUGGER() __debugbreak()
#elif defined(__GNU__)
#define BREAK_IN_DEBUGGER() __builtin_trap()
#else
//#error "No implementation provided for BREAK_IN_DEBUGGER()"
#endif
