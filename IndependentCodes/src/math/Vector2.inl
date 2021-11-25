#include <math.h>

namespace Engine
{
	namespace Math
	{

		inline Vector2::Vector2(float i_x, float i_y) :
			m_x(i_x),
			m_y(i_y)
		{
		}

		inline Vector2::Vector2(const Vector2& i_other) :
			m_x(i_other.m_x),
			m_y(i_other.m_y)
		{
		}

		// operators
		inline Vector2& Vector2::operator=(const Vector2& i_other)
		{
			m_x = i_other.m_x;
			m_y = i_other.m_y;

			return *this;
		}

		// accessors
		inline float Vector2::x(void) const
		{
			return m_x;
		}

		inline float Vector2::y(void) const
		{
			return m_y;
		}

		inline void Vector2::x(float i_x)
		{
			m_x = i_x;
		}

		inline void Vector2::y(float i_y)
		{
			m_y = i_y;
		}

		inline Vector2& Vector2::operator+=(const Vector2& i_other)
		{
			m_x += i_other.m_x;
			m_y += i_other.m_y;

			return *this;
		}

		inline Vector2& Vector2::operator-=(const Vector2& i_other)
		{
			m_x -= i_other.m_x;
			m_y -= i_other.m_y;

			return *this;
		}

		inline Vector2& Vector2::operator*=(const Vector2& i_other)
		{
			m_x *= i_other.m_x;
			m_y *= i_other.m_y;

			return *this;
		}

		inline Vector2& Vector2::operator*=(float i_other)
		{
			m_x *= i_other;
			m_y *= i_other;

			return *this;
		}

		inline Vector2& Vector2::operator/=(const Vector2& i_other)
		{
			m_x /= i_other.m_x;
			m_y /= i_other.m_y;

			return *this;
		}

		inline Vector2& Vector2::operator/=(float i_other)
		{
			m_x /= i_other;
			m_y /= i_other;

			return *this;
		}
		inline Vector2 Vector2::operator-(void)
		{
			return Vector2(-m_x, -m_y);
		}

		inline float Vector2::LengthSq() const
		{
			return (m_x * m_x) + (m_y * m_y);
		}

		inline float Vector2::Length() const
		{
			return static_cast<float>(sqrt(LengthSq()));
		}

		inline Vector2& Vector2::Normalize()
		{
			*this = Normalized();

			return *this;
		}

		// stand alone operators
		inline Vector2 operator+(const Vector2& i_lhs, const Vector2& i_rhs)
		{
			return Vector2(i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y());
		}

		inline Vector2 operator-(const Vector2& i_lhs, const Vector2& i_rhs)
		{
			return Vector2(i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y());
		}

		inline Vector2 operator*(const Vector2& i_lhs, const Vector2& i_rhs)
		{
			return Vector2(i_lhs.x() * i_rhs.x(), i_lhs.y() * i_rhs.x());
		}

		inline Vector2 operator*(const Vector2& i_lhs, float i_rhs)
		{
			return Vector2(i_lhs.x() * i_rhs, i_lhs.y() * i_rhs);
		}

		inline Vector2 operator*(float i_lhs, const Vector2& i_rhs)
		{
			return Vector2(i_lhs * i_rhs.x(), i_lhs * i_rhs.y());
		}

		inline Vector2 operator/(const Vector2& i_lhs, const Vector2& i_rhs)
		{
			return Vector2(i_lhs.x() / i_rhs.x(), i_lhs.y() / i_rhs.y());
		}

		inline Vector2 operator/(const Vector2& i_lhs, float i_rhs)
		{
			return Vector2(i_lhs.x() / i_rhs, i_lhs.y() / i_rhs);
		}

		inline bool operator==(const Vector2& i_lhs, const Vector2& i_rhs)
		{
			return (i_lhs.x() == i_rhs.x()) && (i_lhs.y() == i_rhs.y());
		}

		inline bool operator!=(const Vector2& i_lhs, const Vector2& i_rhs)
		{
			return !operator==(i_lhs, i_rhs);
		}

		inline float dot(const Vector2& i_lhs, const Vector2& i_rhs)
		{
			return i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y();
		}

	} // namespace Math
} // namespace Engine