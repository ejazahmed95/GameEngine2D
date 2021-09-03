#include "StandardInputReader.h"

#include <conio.h>
#include <cstring>
#include <iostream>

char StandardInputReader::readChar()
{
	return static_cast<char>(_getch());
}

char* StandardInputReader::readString()
{
    char a[20];
    std::cin >> a;
    int len = 1;
    while (len <= 20 && a[len - 1] != '\n') len++;
    a[len - 1] = '\0';
    //char* str = (char*)malloc(len * sizeof(char));
    char* str = new char[len];
    memcpy(str, a, len);
    return str;
}
