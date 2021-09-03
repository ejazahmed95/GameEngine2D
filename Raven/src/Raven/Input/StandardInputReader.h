#pragma once
#include "IInputReader.h"
#include "../Core.h"

class RAVEN_API StandardInputReader
{
public:
	char readChar();
	char* readString();
};
