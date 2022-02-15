#pragma once

#define DESIRED_FPS 60.0f;
#define DESIRED_DELTA (1000.0f /DESIRED_FPS)
#define MAX_DELTA (2*DESIRED_DELTA)
#include <cstdint>
#include "Windows.h"

namespace Raven {
	typedef uint64_t tick_t;
	class Timing {
	public:
		Timing();
		float GetLastFrameTime_ms() const;

		float GetTimeDiff_ms(tick_t startTime, tick_t endTime = GetCurrentTickCounter()) const;
		static tick_t GetCurrentTickCounter();

	private:
		float m_LastFrameTime = 0;
		LARGE_INTEGER m_PerformanceFreq = { 0 };
	};
}

