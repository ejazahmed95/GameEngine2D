#include "Timing.h"

#include <cassert>

namespace Raven {

	Timing::Timing() {
		BOOL success = QueryPerformanceFrequency(&m_PerformanceFreq);
		assert(success);
	}

	float Timing::GetLastFrameTime_ms() const {
#if defined(CONSTANT_DELTA)
			return DESIRED_DELTA
#elif defined (CLAMP_FRAMETIME)
			if(m_LastFrameTime > MAX_DELTA) {
				return MAX_DELTA;
			}
#endif
		return m_LastFrameTime;
	}

	tick_t Timing::GetCurrentTickCounter() {
		LARGE_INTEGER currentFrameCounter;
		QueryPerformanceFrequency(&currentFrameCounter);

		return currentFrameCounter.QuadPart;
	}

	float Timing::GetTimeDiff_ms(tick_t startTime, tick_t endTime) const {
		return (1000.0f * static_cast<float>(endTime - startTime)) / m_PerformanceFreq.QuadPart;
	}


}
