#pragma once

#include <Windows.h>

namespace Engine
{
	inline wchar_t* CharsToWChars(const char* i_pChars)
	{
		wchar_t* pWChars = nullptr;

		int BytesNeeded = MultiByteToWideChar(CP_ACP, 0, i_pChars, -1, pWChars, -1);
		if (BytesNeeded)
		{
			pWChars = new wchar_t[BytesNeeded];
			int BytesNeeded = MultiByteToWideChar(CP_ACP, 0, i_pChars, -1, pWChars, -1);
		}

		return pWChars;
	}
}
