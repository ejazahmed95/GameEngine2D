#include "Matrix.h"

namespace RavenStd {

	Matrix Matrix::Identity() {
		return {};
	}

	inline Vec4 Matrix::MultiplyRow(Vec4 v) const {
		return {
			v.X() * m_M00 + v.Y() * m_M10 + v.Z() * m_M20 + v.A() * m_M30,
			v.X() * m_M01 + v.Y() * m_M11 + v.Z() * m_M21 + v.A() * m_M31,
			v.X() * m_M02 + v.Y() * m_M12 + v.Z() * m_M22 + v.A() * m_M32,
			v.X() * m_M03 + v.Y() * m_M13 + v.Z() * m_M23 + v.A() * m_M33,
		};
	};

	inline Vec4 Matrix::MultiplyColumn(Vec4 v) const {
		return {
			v.X() * m_M00 + v.Y() * m_M01 + v.Z() * m_M02 + v.A() * m_M03,
			v.X() * m_M10 + v.Y() * m_M11 + v.Z() * m_M12 + v.A() * m_M13,
			v.X() * m_M20 + v.Y() * m_M21 + v.Z() * m_M22 + v.A() * m_M23,
			v.X() * m_M30 + v.Y() * m_M31 + v.Z() * m_M32 + v.A() * m_M33
		};
	};


	Matrix Matrix::Transpose() const {
		return {
			m_M00,m_M10,m_M20,m_M30,
			m_M01,m_M11,m_M21,m_M31,
			m_M02,m_M12,m_M22,m_M32,
			m_M03,m_M13,m_M23,m_M33
		};
	}

	Matrix Matrix::Inverse() const {
		//
		return *this;
	}

	Matrix Matrix::GetInverseWellBehaved(Matrix& rot, Matrix& trans) {
		auto m = rot.Transpose() * trans;
		return {
			rot.m_M00, rot.m_M10, rot.m_M20, -m.m_M00,
			rot.m_M01, rot.m_M11, rot.m_M21, -m.m_M11,
			rot.m_M02, rot.m_M12, rot.m_M22, -m.m_M22,
			0, 0, 0, 1
		};
	}


	// Matrix Matrix::Inverse(Matrix& matrix) {}
	Matrix Matrix::CreateTranslation(float transX, float transY, float transZ) {
		return {
			1, 0, 0, transX,
			0, 1, 0, transY,
			0, 0, 1, transZ,
			0, 0, 0, 1,
		};
	}

	// Rotation form [ [C, -S] [S, C] ]
	Matrix Matrix::CreateRotationX(float radians) {
		const float c = cosf(radians); // Cosine
		const float s = sinf(radians); // Sine
		return {
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		};
	}

	Matrix Matrix::CreateRotationY(float radians) {
		const float c = cosf(radians); // Cosine
		const float s = sinf(radians); // Sine
		return {
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		};
	}
	Matrix Matrix::CreateRotationZ(float radians) {
		const float c = cosf(radians); // Cosine
		const float s = sinf(radians); // Sine
		return {
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	Matrix Matrix::CreateScale(Vec4 scale) {
		return {
			scale.X(), 0, 0, 0,
			0, scale.Y(), 0, 0,
			0, 0, scale.Z(), 0,
			0, 0, 0, scale.A()
		};
	}

	Matrix& Matrix::operator=(const Matrix& m) {
		m_M00 = m.m_M00;
		m_M01 = m.m_M01;
		m_M02 = m.m_M02;
		m_M03 = m.m_M03;

		m_M10 = m.m_M10;
		m_M11 = m.m_M11;
		m_M12 = m.m_M12;
		m_M13 = m.m_M13;

		m_M20 = m.m_M20;
		m_M21 = m.m_M21;
		m_M22 = m.m_M22;
		m_M23 = m.m_M23;

		m_M10 = m.m_M30;
		m_M11 = m.m_M31;
		m_M12 = m.m_M32;
		m_M13 = m.m_M33;

		return *this;
	}

	Matrix Matrix::operator*(Matrix& m) const {
		return *this;
	}

	Vec4 operator*(const Matrix& lhs, const Vec4& rhs) {
		return lhs.MultiplyColumn(rhs);
	}

	Vec4 operator*(const Vec4& lhs, const Matrix& rhs) {
		return rhs.MultiplyRow(lhs);
	}
}
