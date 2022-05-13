#include "Testing.h"

#include <cassert>

#include "../memory/StrongPointer.h"
#include "../memory/WeakPointer.h"
#include "../LinearAlgebra/Matrix.h"

namespace RavenStd {
	void TestStrongWeakPtr() {
		StrongPtr<TestClass> ptr(new TestClass(4));
		WeakPtr<TestClass> weakPtr = ptr;
		{
			auto sPtr = StrongPtr<TestClass>(new TestClass());
			ptr = sPtr;
		}
	}


	void TestMatrix() {
		Matrix tMat = Matrix::CreateTranslation(20, 30, 0);
		float zRot = 0.5f;
		Matrix rMat = Matrix::CreateRotationZ(zRot);

		auto a2worldMat = tMat * rMat;
		auto v4 = tMat.Column(3);
		auto world2AMat = Matrix::GetInverseWellBehaved(rMat, v4);
		assert(tMat == Matrix(1, 0, 0, 20,
			0, 1, 0, 30,
			0, 0, 1, 0,
			0, 0, 0, 1));

		Log::D("A to World Mat = \n" + a2worldMat.String());
		Log::D("World 2 A Matrix = \n" + world2AMat.String());

		assert(rMat == Matrix(cosf(zRot), -sinf(zRot), 0, 0,
			sinf(zRot), cosf(zRot), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1));

		assert(a2worldMat == Matrix(cosf(zRot), -sinf(zRot), 0, 20,
			sinf(zRot), cosf(zRot), 0, 30,
			0, 0, 1, 0,
			0, 0, 0, 1));

		assert(world2AMat == Matrix(cosf(zRot), sinf(zRot), 0, -31.934410f,
			-sinf(zRot), cosf(zRot), 0, -16.738960f,
			0, 0, 1, 0,
			0, 0, 0, 1));

		// assert()
		// Matrix worldMat = tMat * rMat;
	}

}

