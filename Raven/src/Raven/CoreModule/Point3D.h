#pragma once
#include <string>

#include "../Core.h"
#include "../nlohmann/json.hpp"
#include "RavenStd/LinearAlgebra/Vec4.h"

using json = nlohmann::json;

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
		float Mag() const;
		float Mag2() const;
	private:
		float m_X, m_Y, m_Z;
	public:
		void to_json(json& j, const Point3D& p) {
			j = json{ {"x", p.m_X}, {"y", p.m_Y}, {"z", p.m_Z} };
		}

		RavenStd::Vec4 ToVec4(float a = 0) const {
			return { m_X, m_Y, m_Z, a};
		}

		static void from_json(const json& j, Point3D& p) {
			j.at("x").get_to(p.m_X);
			j.at("y").get_to(p.m_Y);
			j.at("z").get_to(p.m_Z);
		}
	};

	// Outside scope overloading
	Point3D operator*(float const lhs, Point3D const& rhs);
}}
