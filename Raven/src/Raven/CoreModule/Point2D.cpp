#include "Point2D.h"

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

	std::string Point2D::toString()
	{
		return std::string("[") + std::to_string(x_) + ", " + std::to_string(y_) + "]";
	}

	void Point2D::setX(int i)
	{
		x_ = i;
	}

	void Point2D::setY(int i)
	{
		y_ = i;
	}
/*
	std::ostream& operator<<(std::ostream& lhs, const Raven::Point2D& rhs)
	{
		lhs << "[" << rhs.x() << ", " << rhs.y() << "]";
		return lhs;
	}*/
}
