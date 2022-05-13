#pragma once
#include <string>

namespace RavenStd {
	struct TestClass {
		int i;
		float f;
		TestClass() : i(0), f(0) {}
		explicit TestClass(int iVal) : i(iVal), f(0) {}
		explicit TestClass(float fVal) : i(0), f(fVal) {}
		explicit TestClass(int iVal, float fVal) : i(iVal), f(fVal) {}
	};

	struct DerivedClass : public TestClass {
		std::string name;
		DerivedClass() : TestClass(), name("derived") {}
	};

	void TestStrongWeakPtr();
	void TestMatrix();
}
