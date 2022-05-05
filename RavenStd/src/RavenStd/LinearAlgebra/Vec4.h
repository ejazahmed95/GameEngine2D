#pragma once
#include <string>

namespace RavenStd {
	class Vec4 {
	public:
		Vec4() : m_X(0), m_Y(0), m_Z(0), m_A(0) {}
		explicit Vec4(float const v) : m_X(v), m_Y(v), m_Z(v), m_A(v) {}
		Vec4(float const x, float const y, float const z) : m_X(x), m_Y(y), m_Z(z), m_A(1) {}
		Vec4(float const x, float const y, float const z, float const a) : m_X(x), m_Y(y), m_Z(z), m_A(a) {}

		// Operator Overloading
		Vec4 operator+(Vec4 const& rhs) const;
		Vec4 operator-(Vec4 const& rhs) const;
		Vec4 operator*(Vec4 const& rhs) const;
		Vec4 operator*(float const rhs) const;

		Vec4 operator/(float const rhs) const;
		bool operator==(Vec4 const& rhs) const;
		bool operator!=(Vec4 const& rhs) const;
		Vec4 operator-() const;

		// Modifying operators
		Vec4& operator+=(Vec4 const& rhs);
		Vec4& operator-=(Vec4 const& rhs);
		Vec4& operator*=(Vec4 const& rhs);
		Vec4& operator/=(Vec4 const& rhs);


		//friend std::ostream& operator<<(std::ostream& lhs, const Vec4& rhs);
		std::string toString() const;

		// Getters & Setters
		float X() const { return m_X; }
		float Y() const { return m_Y; }
		float Z() const { return m_Z; }
		float A() const { return m_A; }
		void SetX(float i);
		void SetY(float i);
		void SetZ(float i);
		void SetA(float i);
		float Mag() const;
		float Mag2() const;
		static float Dot(const Vec4& v1, const Vec4& v2);
	private:
		float m_X, m_Y, m_Z, m_A;
	};

	// Outside scope overloading
	Vec4 operator*(float const lhs, Vec4 const& rhs);
}
