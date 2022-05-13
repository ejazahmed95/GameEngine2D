#pragma once
#include <cmath>

namespace RavenStd {
	inline bool IsEqual(const float& p1, const float& p2) {
		return fabs(p1 - p2) < 0.0001f;
	}
}
