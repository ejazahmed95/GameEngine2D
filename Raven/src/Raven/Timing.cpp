#include "Timing.h"
#include <cassert>
#include "RavenStd/Logger.h"

namespace Raven {
	float Timing::s_LastFrameTime = 0;

	Timing::Timing() {
		BOOL success = QueryPerformanceFrequency(&m_PerformanceFreq);
		assert(success);
	}

	float Timing::GetFrameTime() {
		static tick_t lastFrameStartTick = 0;

		tick_t currentFrameStartTick = GetCurrentTickCounter();
		float frameTime = (lastFrameStartTick == 0) ? (1.0f/60) : (GetTimeDiff_ms(lastFrameStartTick, currentFrameStartTick) / 1000.0f);
		// if(frameTime*1000 < 10) {
		// 	Sleep(16 - static_cast<int>(frameTime * 1000));
		// 	currentFrameStartTick = GetCurrentTickCounter();
		// 	frameTime =  GetTimeDiff_ms(lastFrameStartTick, currentFrameStartTick) / 1000.0f;
		// }
		lastFrameStartTick = currentFrameStartTick;
		s_LastFrameTime = frameTime;
		// Add a debugger check
		return frameTime;
	}

	float Timing::GetLastFrameTime_ms() {
#if defined(CONSTANT_DELTA)
			return DESIRED_DELTA
#elif defined (CLAMP_FRAMETIME)
			if(s_LastFrameTime > MAX_DELTA) {
				return MAX_DELTA;
			}
#endif
		return s_LastFrameTime;
	}

	tick_t Timing::GetCurrentTickCounter() {
		LARGE_INTEGER currentFrameCounter;
		QueryPerformanceCounter(&currentFrameCounter);

		return currentFrameCounter.QuadPart;
	}

	float Timing::GetTimeDiff_ms(tick_t startTime, tick_t endTime) const {
		// SLib::Log::I("Get Time Diff in MS = " + std::to_string(endTime - startTime));
		return (1000.0f * static_cast<float>(endTime - startTime)) / m_PerformanceFreq.QuadPart;
	}


}
