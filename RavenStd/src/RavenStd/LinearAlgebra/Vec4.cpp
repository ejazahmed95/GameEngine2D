#include "Vec4.h"

namespace RavenStd {
	Vec4 Vec4::operator+(Vec4 const& rhs) const {
		return { m_X + rhs.X(), m_Y + rhs.Y(), m_Z + rhs.Z(), m_A + rhs.A() };
	}

	Vec4 Vec4::operator-(Vec4 const& rhs) const {
		return { m_X - rhs.X(), m_Y - rhs.Y(), m_Z - rhs.Z(), m_A - rhs.A()};
	}

	Vec4 Vec4::operator*(Vec4 const& rhs) const {
		return { m_X * rhs.X(), m_Y * rhs.Y(), m_Z * rhs.Z(), m_A * rhs.A() };
	}

	Vec4 Vec4::operator*(float const rhs) const {
		return { m_X * rhs, m_Y * rhs, m_Z * rhs, m_A * rhs };
	}

	Vec4 Vec4::operator/(float const rhs) const {
		return { m_X / rhs, m_Y / rhs, m_Z / rhs, m_A/rhs };
	}

	bool Vec4::operator==(Vec4 const& rhs) const {
		return (m_X == rhs.m_X) && (m_Y == rhs.m_Y) && m_Z == rhs.m_Z && m_A == rhs.m_A;
	}

	bool Vec4::operator!=(Vec4 const& rhs) const {
		return !(*this == rhs);
	}

	Vec4 Vec4::operator-() const {
		return { -m_X, -m_Y, -m_Z, -m_A };
	}

	Vec4& Vec4::operator+=(Vec4 const& rhs) {
		m_X += rhs.m_X;
		m_Y += rhs.m_Y;
		m_Z += rhs.m_Z;
		m_A += rhs.m_A;
		return *this;
	}

	Vec4& Vec4::operator-=(Vec4 const& rhs) {
		m_X -= rhs.m_X;
		m_Y -= rhs.m_Y;
		m_Z -= rhs.m_Z;
		m_A -= rhs.m_A;
		return *this;
	}

	Vec4& Vec4::operator*=(Vec4 const& rhs) {
		m_X *= rhs.m_X;
		m_Y *= rhs.m_Y;
		m_Z += rhs.m_Z;
		m_A += rhs.m_A;
		return *this;
	}

	Vec4& Vec4::operator/=(Vec4 const& rhs) {
		m_X /= rhs.m_X;
		m_Y /= rhs.m_Y;
		m_Z /= rhs.m_Z;
		m_A /= rhs.m_A;
		return *this;
	}

	std::string Vec4::toString() const {
		return std::string("[") + std::to_string(m_X) + ", " + std::to_string(m_Y) + ", " + std::to_string(m_Z) + ", " + std::to_string(m_A) + "]";
	}

	void Vec4::SetX(float i) {
		m_X = i;
	}

	void Vec4::SetY(float i) {
		m_Y = i;
	}

	void Vec4::SetZ(float i) {
		m_Z = i;
	}

	void Vec4::SetA(float i) {
		m_A = i;
	}

	float Vec4::Mag() const {
		return sqrt(Mag2());
	}

	float Vec4::Mag2() const {
		return (m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_A*m_A);
	}

	float Vec4::Dot(const Vec4& v1, const Vec4& v2) {
		return v1.m_X * v2.m_X + v1.m_Y * v2.m_Y + v1.m_Z * v2.m_Z + v1.m_A * v2.m_A;
	}

	Vec4 operator*(float const lhs, Vec4 const& rhs)
	{
		return rhs * lhs;
	}
}
