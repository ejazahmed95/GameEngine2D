#pragma once
#include <string>

#include "../Core.h"

namespace Raven { namespace Core {
	class RAVEN_API Point3D {
	public:
		Point3D() : m_X(0), m_Y(0), m_Z(0) {}
		Point3D(float const a) : m_X(a), m_Y(a), m_Z(a) {}
		Point3D(float const x, float const y, float const z) : m_X(x), m_Y(y), m_Z(z) {}

		// Operator Overloading
		Point3D operator+(Point3D const& rhs) const;
		Point3D operator-(Point3D const& rhs) const;
		Point3D operator*(Point3D const& rhs) const;
		Point3D operator*(float const rhs) const;

		Point3D operator/(float const rhs) const;
		bool operator==(Point3D const& rhs) const;
		bool operator!=(Point3D const& rhs) const;
		Point3D operator-() const;

		// Modifying operators
		Point3D& operator+=(Point3D const& rhs);
		Point3D& operator-=(Point3D const& rhs);
		Point3D& operator*=(Point3D const& rhs);
		Point3D& operator/=(Point3D const& rhs);


		//friend std::ostream& operator<<(std::ostream& lhs, const Point3D& rhs);
		std::string toString() const;

		// Getters & Setters
		float X() const { return m_X; }
		float Y() const { return m_Y; }
		float Z() const { return m_Z; }
		void SetX(float i);
		void SetY(float i);
		void SetZ(float i);
	private:
		float m_X, m_Y, m_Z;
	};

	// Outside scope overloading
	Point3D operator*(float const lhs, Point3D const& rhs);
}}
