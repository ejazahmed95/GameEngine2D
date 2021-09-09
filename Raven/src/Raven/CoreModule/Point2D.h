#pragma once
#include "../Core.h"
#include <string>

namespace Raven {
	class RAVEN_API Point2D {
	public:
		Point2D() : x_(0), y_(0) {}
		Point2D(int const a) : x_(a), y_(a) {}
		Point2D(int const x, int const y) : x_(x), y_(y) {}

		// Operator Overloaders
		Point2D operator+(Point2D const& rhs) const;
		Point2D operator-(Point2D const& rhs) const;
		Point2D operator*(Point2D const& rhs) const;
		Point2D operator*(int const rhs) const;

		Point2D operator/(int const rhs) const;
		bool operator==(Point2D const& rhs) const;
		bool operator!=(Point2D const& rhs) const;
		Point2D operator-() const;

		// Modifying operators
		Point2D& operator+=(Point2D const& rhs);
		Point2D& operator-=(Point2D const& rhs);
		Point2D& operator*=(Point2D const& rhs);
		Point2D& operator/=(Point2D const& rhs);
		

		//friend std::ostream& operator<<(std::ostream& lhs, const Point2D& rhs);
		std::string toString() const;

		// Getters & Setters
		int x() const { return x_; }
		int y() const { return y_; }
		void setX(int i);
		void setY(int i);
	private:
		int x_, y_;
	};

	// Outside scope overloading
	Point2D operator*(int const lhs, Point2D const& rhs);

};

