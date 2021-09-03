#pragma once
#include <ostream>

#include "../Core.h"

namespace Raven {
	class RAVEN_API Point2D {
	public:
		Point2D() : x_(0), y_(0) {}
		Point2D(int const a) : x_(a), y_(a) {}
		Point2D(int const x, int const y) : x_(x), y_(y) {}

		// Operator Overloaders
		Point2D operator+(Point2D const& other) const;
		Point2D operator-(Point2D const& other) const;
		Point2D operator*(Point2D const& other) const;
		Point2D operator*(int const value) const;
		friend std::ostream& operator<<(std::ostream& lhs, const Point2D& rhs);

		// Getters & Setters
		int x() const { return x_; }
		int y() const { return y_; }
		void setX(int i);
		void setY(int i);
	private:
		int x_, y_;
	};
};

