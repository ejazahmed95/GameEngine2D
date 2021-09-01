#pragma once
#include "../Core.h"

namespace Raven {
	class RAVEN_API Point2D {
	public:
		Point2D() : X(0), Y(0) {}
		Point2D(int a) : X(a), Y(a) {}
		Point2D(int x, int y) : X(x), Y(y) {}
		~Point2D() {}

	private:
		int X, Y;
	};
};

