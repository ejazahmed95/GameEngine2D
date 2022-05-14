#pragma once
#include <xmmintrin.h>

namespace RavenStd { namespace Opt {

	union V3 {
		__m128 vec;
		float v[4];
	};

	class Vec3SSE {
	public:
		Vec3SSE(float x, float y, float z) {
			// Setting the values in reverse
			m_Vec.vec = _mm_set_ps(0, z, y, x);
			// m_Vec.v[0] = x;
			// m_Vec.v[1] = y;
			// m_Vec.v[2] = z;
			// m_Vec.v[3] = 0;
		}

		Vec3SSE(__m128 v) {
			m_Vec.vec = v;
		}

		float X() const { return m_Vec.v[0]; }
		float Y() const { return m_Vec.v[1]; }
		float Z() const { return m_Vec.v[2]; }

		static inline float Dot(Vec3SSE& v1, Vec3SSE& v2) {
			return _mm_cvtss_f32(_mm_dp_ps(v1.m_Vec.vec, v2.m_Vec.vec, 0x71));
		};

		static inline Vec3SSE Cross(Vec3SSE& v1, Vec3SSE& v2) {
			__m128 v1_yzx = _mm_shuffle_ps(v1.m_Vec.vec, v1.m_Vec.vec, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 v2_zxy = _mm_shuffle_ps(v2.m_Vec.vec, v2.m_Vec.vec, _MM_SHUFFLE(3, 1, 0, 2));

			__m128 v1_zxy = _mm_shuffle_ps(v1.m_Vec.vec, v1.m_Vec.vec, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 v2_yzx = _mm_shuffle_ps(v2.m_Vec.vec, v2.m_Vec.vec, _MM_SHUFFLE(3, 0, 2, 1));

			// Log::D("Temp 0: " + Vec3SSE(tmp0).Print());
			// Log::D("Temp 1: " + Vec3SSE(tmp1).Print());
			// Log::D("Temp 2: " + Vec3SSE(tmp2).Print());
			// Log::D("Temp 3: " + Vec3SSE(tmp3).Print());

			return _mm_sub_ps(
				_mm_mul_ps(v1_yzx, v2_zxy),
				_mm_mul_ps(v1_zxy, v2_yzx)
			);
		}

		std::string Print() {
			// std::string res = "[ X = ";
			return "[ X = " + std::to_string(m_Vec.v[0]) + ", Y = " + std::to_string(m_Vec.v[1]) + ", Z = " + std::to_string(m_Vec.v[2]) + " ]";
		}
	private:
		V3 m_Vec{};
	};

}}
