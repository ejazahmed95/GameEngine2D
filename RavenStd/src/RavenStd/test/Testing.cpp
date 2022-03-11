#include "Testing.h"
#include "../memory/StrongPointer.h"
#include "../memory/WeakPointer.h"

namespace RavenStd {
	void TestStrongWeakPtr() {
		StrongPtr<TestClass> ptr(new TestClass(4));
		WeakPtr<TestClass> weakPtr = ptr;
		{
			auto sPtr = StrongPtr<TestClass>(new TestClass());
			ptr = sPtr;
		}
	}
}

