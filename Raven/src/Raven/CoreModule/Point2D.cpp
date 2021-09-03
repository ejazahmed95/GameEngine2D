#include "Point2D.h"
#include <iostream>
#include <ostream>
#include <string>

namespace Raven
{
	Point2D Point2D::operator+(Point2D const& other) const {
		return { x_ + other.x(), y_ + other.y() };
	}

	Point2D Point2D::operator-(Point2D const& other) const
	{
		return { x_ - other.x(), y_ - other.y() };
	}

	Point2D Point2D::operator*(Point2D const& other) const
	{
		return { x_ * other.x(), y_ * other.y() };
	}

	Point2D Point2D::operator*(int const value) const
	{
		return { x_ * value, y_ * value };
	}

	void Point2D::setX(int i)
	{
		x_ = i;
	}

	void Point2D::setY(int i)
	{
		y_ = i;
		std::cout << *this;
	}

	std::ostream& operator<<(std::ostream& lhs, const Point2D& rhs)
	{
		lhs << "[" << rhs.x_ << ", " << rhs.y_ << "]";
		return lhs;
	}
}
