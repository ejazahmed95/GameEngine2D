#pragma once
#include "../Core.h"

class RAVEN_API IInputReader {
public:
	virtual ~IInputReader() = default;
	virtual char readChar() = 0;
	virtual char* readString() = 0;
};
