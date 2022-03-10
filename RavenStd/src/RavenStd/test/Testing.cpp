#include "Testing.h"
#include "../memory/StrongPointer.h"

namespace RavenStd {
	void TestStrongWeakPtr() {
		StrongPtr<TestClass> ptr;
		{
			auto sPtr = StrongPtr<TestClass>(new TestClass());
			ptr = sPtr;
		}
	}
}

