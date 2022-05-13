#pragma once
#include "Vec4.h"

namespace RavenStd {
	class Matrix {
	public:
		Matrix() : Matrix(1, 1, 1, 1) {}
		Matrix(float x, float y, float z, float a) :
			Matrix(
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, a){}
		Matrix(float v00, float v01, float v02, float v03,
			float v10, float v11, float v12, float v13,
			float v20, float v21, float v22, float v23,
			float v30, float v31, float v32, float v33) : m_M00(v00), m_M01(v01), m_M02(v02), m_M03(v03),
			m_M10(v10), m_M11(v11), m_M12(v12), m_M13(v13),
			m_M20(v20), m_M21(v21), m_M22(v22), m_M23(v23),
			m_M30(v30), m_M31(v31), m_M32(v32), m_M33(v33) {}


		Matrix(const Matrix& m):
			m_M00(m.m_M00), m_M01(m.m_M01), m_M02(m.m_M02), m_M03(m.m_M03),
			m_M10(m.m_M10), m_M11(m.m_M11), m_M12(m.m_M12), m_M13(m.m_M13),
			m_M20(m.m_M20), m_M21(m.m_M21), m_M22(m.m_M22), m_M23(m.m_M23),
			m_M30(m.m_M30), m_M31(m.m_M31), m_M32(m.m_M32), m_M33(m.m_M33) {}

		// Helpers
		static Matrix Identity();
		inline Vec4 MultiplyRow(Vec4 v) const;
		inline Vec4 MultiplyColumn(Vec4 v) const;

		// Properties
		Matrix Transpose() const;
		//Matrix Inverse() const; // Inverts the current matrix
		Vec4 Column(int index) const;

		/// <summary>
		/// Get the inverse of a well behaved coordinate system matrix
		/// </summary>
		/// <param name="rot">Rotation Matrix</param>
		/// <param name="trans">Translation Matrix</param>
		/// <returns></returns>
		static Matrix GetInverseWellBehaved(Matrix& rot, Vec4& trans);

		/**
		 * \brief Generates a translation matrix
		 * \param transX Translation in X direction
		 * \param transY Translation in Y direction
		 * \param transZ Translation in Z direction
		 * \return a Translation Matrix
		 */
		static Matrix CreateTranslation(float transX, float transY, float transZ);

		static Matrix CreateRotationX(float radians);
		static Matrix CreateRotationY(float radians);
		static Matrix CreateRotationZ(float radians);

		static Matrix CreateScale(Vec4 scale);

		// Operator Overloading
		Matrix& operator=(const Matrix& m); // Assignment Operator
		Matrix operator*(Matrix& m) const;

		bool operator==(const Matrix& m) const;

		std::string String() const;

	private:
		static Matrix m_Identity;
		float m_M00, m_M01, m_M02, m_M03;
		float m_M10, m_M11, m_M12, m_M13;
		float m_M20, m_M21, m_M22, m_M23;
		float m_M30, m_M31, m_M32, m_M33;
	};

	// Multiplication with a Vec4
	Vec4 operator*(const Matrix& lhs, const Vec4& rhs);
	Vec4 operator*(const Vec4& lhs, const Matrix& rhs);

}
