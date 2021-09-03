#pragma once
#include "IInputReader.h"
#include "../Core.h"

class RAVEN_API StandardInputReader: IInputReader
{
public:
	char readChar() override;
	char* readString() override;
};
