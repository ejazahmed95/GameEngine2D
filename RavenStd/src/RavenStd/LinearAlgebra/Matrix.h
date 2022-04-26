#pragma once
#include "Vec4.h"

namespace RavenStd {
	class Matrix {
	public:
		Matrix(float v00, float v01, float v02, float v03,
			float v10, float v11, float v12, float v13,
			float v20, float v21, float v22, float v23,
			float v30, float v31, float v32, float v33) : m_M00(v00), m_M01(v01), m_M02(v02), m_M03(v03),
			m_M10(v10), m_M11(v11), m_M12(v12), m_M13(v13),
			m_M20(v20), m_M21(v21), m_M22(v22), m_M23(v23),
			m_M30(v30), m_M31(v31), m_M32(v32), m_M33(v33) {}

		Matrix Identity();
		Matrix RotationMatrixX();
		Matrix RotationMatrixY();
		Matrix RotationMatrixZ();





		// Matrix(float x, float y, float z, float a) {
		// 	
		// }
		// static Matrix Identity() {
		// 	return Matrix()
		// }
		static Matrix CreateScale(float x, float y, float z) {
			// Copy of Identity
			
		};
	private:
		static Matrix m_Identity;
		float m_M00, m_M01, m_M02, m_M03;
		float m_M10, m_M11, m_M12, m_M13;
		float m_M20, m_M21, m_M22, m_M23;
		float m_M30, m_M31, m_M32, m_M33;
	};
}
