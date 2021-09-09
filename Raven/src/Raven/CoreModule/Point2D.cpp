#include "Point2D.h"

namespace Raven
{
	Point2D Point2D::operator+(Point2D const& rhs) const {
		return { x_ + rhs.x(), y_ + rhs.y() };
	}

	Point2D Point2D::operator-(Point2D const& rhs) const {
		return {x_ - rhs.x(), y_ - rhs.y()};
	}

	Point2D Point2D::operator*(Point2D const& rhs) const {
		return {x_ * rhs.x(), y_ * rhs.y()};
	}

	Point2D Point2D::operator*(int const rhs) const{
		return {x_ * rhs, y_ * rhs};
	}

	Point2D Point2D::operator/(int const rhs) const{
		return { x_ / rhs, y_ / rhs };
	}

	bool Point2D::operator==(Point2D const& rhs) const
	{
		return (x_ == rhs.x_) && (y_ == rhs.y_);
	}

	bool Point2D::operator!=(Point2D const& rhs) const
	{
		return !(*this == rhs);
	}

	Point2D Point2D::operator-() const
	{
		return { -x_, -y_ };
	}

	Point2D& Point2D::operator+=(Point2D const& rhs) {
		x_ += rhs.x_;
		y_ += rhs.y_;
		return *this;
	}

	Point2D& Point2D::operator-=(Point2D const& rhs) {
		x_ -= rhs.x_;
		y_ -= rhs.y_;
		return *this;
	}

	Point2D& Point2D::operator*=(Point2D const& rhs) {
		x_ *= rhs.x_;
		y_ *= rhs.y_;
		return *this;
	}

	Point2D& Point2D::operator/=(Point2D const& rhs) {
		x_ /= rhs.x_;
		y_ /= rhs.y_;
		return *this;
	}

	std::string Point2D::toString() const
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

	Point2D operator*(int const lhs, Point2D const& rhs)
	{
		return rhs*lhs;
	}

	/*
	std::ostream& operator<<(std::ostream& lhs, const Raven::Point2D& rhs)
	{
		lhs << "[" << rhs.x() << ", " << rhs.y() << "]";
		return lhs;
	}*/
}
