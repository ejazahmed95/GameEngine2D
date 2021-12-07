#pragma once

namespace Engine
{
	namespace Math
	{

		class Vector2
		{
		public:
			// standard constructor
			inline Vector2(float i_x, float i_y);
			// copy constructor - for completeness
			inline Vector2(const Vector2& i_other);
			// assignment operator
			inline Vector2& operator=(const Vector2& i_rhs);

			// element accessors
			// - get individual element
			inline float x(void) const;
			inline float y(void) const;
			// - set individual element
			inline void x(float i_x);
			inline void y(float i_y);
			inline void z(float i_z);

			// modifying operators
			inline Vector2& operator+=(const Vector2& i_rhs);
			inline Vector2& operator-=(const Vector2& i_rhs);

			inline Vector2& operator*=(const Vector2& i_other);
			inline Vector2& operator*=(float i_val);

			inline Vector2& operator/=(const Vector2& i_other);
			inline Vector2& operator/=(float i_val);

			// negate
			inline Vector2 operator-(void);

			inline Vector2& Normalize();
			inline Vector2 Normalized() const;

			inline float Length() const;
			inline float LengthSq() const;

			// - ( 0.0f, 0.0f, 0.0f )
			static const Vector2 Zero;

		private:
			float	m_x, m_y;
		};

		inline Vector2 Normalized(const Vector2& i_vec);

		inline Vector2 operator+(const Vector2& i_lhs, const Vector2& i_rhs);
		inline Vector2 operator-(const Vector2& i_lhs, const Vector2& i_rhs);

		inline Vector2 operator*(const Vector2& i_lhs, float i_rhs);
		inline Vector2 operator*(const Vector2& i_lhs, float i_rhs);

		inline Vector2 operator/(const Vector2& i_lhs, const Vector2& i_rhs);
		inline Vector2 operator/(const Vector2& i_lhs, float i_rhs);

		inline bool operator==(const Vector2& i_lhs, const Vector2& i_rhs);
		inline bool operator!=(const Vector2& i_lhs, const Vector2& i_rhs);

		inline float dot(const Vector2& i_lhs, const Vector2& i_rhs);

	} // namespace Math
} // amespace Engine

#include "Vector2.inl"
