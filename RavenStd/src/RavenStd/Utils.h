#pragma once

namespace RavenStd {

	template<typename T>
	inline void Swap(T& first, T& second)
	{
		T temp = first;
		first = second;
		second = temp;
	}

	template<typename T>
	inline T Max(T& first, T& second) {
		if (first >= second) return first;
		return second;
	}

	template<typename T>
	inline T Min(T& first, T& second) {
		if (first <= second) return first;
		return second;
	}
}
