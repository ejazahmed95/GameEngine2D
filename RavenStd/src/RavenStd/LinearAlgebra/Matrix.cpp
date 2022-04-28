#include "Matrix.h"

namespace RavenStd {

	Matrix Matrix::Identity() {
		return Matrix();
	}

	Matrix Matrix::Transpose() const {}
	Matrix Matrix::Inverse() const {}
	Matrix Matrix::Inverse(Matrix& matrix) {}
	Matrix Matrix::CreateTranslation() {}
	Matrix Matrix::CreateRotationX() {}
	Matrix Matrix::CreateRotationY() {}
	Matrix Matrix::CreateRotationZ() {}
	Matrix Matrix::CreateScale(Vec4 scale) {
		
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
}
