#include "Point3D.h"
#include <cmath>

namespace Raven { namespace Core {
	Point3D Point3D::operator+(Point3D const& rhs) const {
		return { m_X + rhs.X(), m_Y + rhs.Y(), m_Z + rhs.Z() };
	}

	Point3D Point3D::operator-(Point3D const& rhs) const {
		return {m_X - rhs.X(), m_Y - rhs.Y(), m_Z - rhs.Z()};
	}

	Point3D Point3D::operator*(Point3D const& rhs) const {
		return {m_X * rhs.X(), m_Y * rhs.Y(), m_Z * rhs.Z()};
	}

	Point3D Point3D::operator*(float const rhs) const {
		return {m_X * rhs, m_Y * rhs, m_Z * rhs};
	}

	Point3D Point3D::operator/(float const rhs) const {
		return { m_X / rhs, m_Y / rhs, m_Z / rhs };
	}

	bool Point3D::operator==(Point3D const& rhs) const {
		return (m_X == rhs.m_X) && (m_Y == rhs.m_Y) && (m_Z == rhs.m_Z);
	}

	bool Point3D::operator!=(Point3D const& rhs) const {
		return !(*this == rhs);
	}

	Point3D Point3D::operator-() const {
		return {-m_X, -m_Y, -m_Z};
	}

	Point3D& Point3D::operator+=(Point3D const& rhs) {
		m_X += rhs.m_X;
		m_Y += rhs.m_Y;
		m_Z += rhs.m_Z;
		return *this;
	}

	Point3D& Point3D::operator-=(Point3D const& rhs) {
		m_X -= rhs.m_X;
		m_Y -= rhs.m_Y;
		m_Z -= rhs.m_Z;
		return *this;
	}

	Point3D& Point3D::operator*=(Point3D const& rhs) {
		m_X *= rhs.m_X;
		m_Y *= rhs.m_Y;
		m_Z += rhs.m_Z;
		return *this;
	}

	Point3D& Point3D::operator/=(Point3D const& rhs) {
		m_X /= rhs.m_X;
		m_Y /= rhs.m_Y;
		m_Z /= rhs.m_Z;
		return *this;
	}

	std::string Point3D::toString() const {
		return std::string("[") + std::to_string(m_X) + ", " + std::to_string(m_Y) + ", " + std::to_string(m_Z) + "]";
	}

	void Point3D::SetX(float i) {
		m_X = i;
	}

	void Point3D::SetY(float i) {
		m_Y = i;
	}

	void Point3D::SetZ(float i) {
		m_Z = i;
	}

	float Point3D::Mag() const {
		return sqrt(Mag2());
	}

	float Point3D::Mag2() const {
		return (m_X * m_X + m_Y * m_Y + m_Z * m_Z);
	}

	Point3D operator*(float const lhs, Point3D const& rhs)
	{
		return rhs * lhs;
	}

}}
