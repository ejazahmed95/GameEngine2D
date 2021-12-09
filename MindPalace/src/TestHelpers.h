#pragma once

void HeapTestFinal();
bool HeapManager_CustomTest();


#if defined(WIN32)
typedef uint32_t t_TestInt;
#else
typedef uint64_t t_TestInt;
#endif

// Custom Tests
void RepresentBits(t_TestInt value);
void RepresentBitsChar(char value);
void TestMemSet();
void TestBitScans();
void TestBitToggle();
void TestNewDelete();