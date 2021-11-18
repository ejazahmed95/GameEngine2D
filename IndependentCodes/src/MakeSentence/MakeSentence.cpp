#include <cassert>
#include <conio.h>

#include "../Utilities/Utils.h"
#include <iostream>

char* readStringFromCIn() {
    char a[20];
    // std::cin >> a;
    size_t len = 0;
	while (len <= 20) {
		char c;
		c = std::getchar();
		if (c != '\n' && c != '\0') {
			a[len++] = c;
		} else break;
	}

    // char* str = (char*)malloc((len+1) * sizeof(char));
	// if (len == 2 && a[0]=='q') return nullptr;
	if (len == 0) return nullptr;
	len++;
    char* str = new char[len];
    memcpy(str, a, len - 1);
    str[len-1] = '\0';
    return str;
}

int len(const char* word) {
	int len = 0;
	while (word[len] != '\n' && word[len]!='\0') len++;
	return len;
}

char* MakeSentence(char** arr) {
	int totalLength = 0;
	for(int i=0;;i++) {
		const char* word = arr[i];
		if (word == nullptr) break;
		totalLength += (len(word) + 1);
	}
	totalLength++;

	char* str = static_cast<char*>(malloc(totalLength * sizeof(char)));
	assert(str);
	str[totalLength - 1] = '\0';

	int currIndex = 0;
	for (int i = 0;; i++) {
		const char* word = arr[i];
		if (word == nullptr) break;
		memcpy(str + currIndex, word, len(word));
		currIndex += len(word);
		str[currIndex++] = ' ';
		// std::cout << str << std::endl;
	}
	if(currIndex > 0) str[currIndex-1] = '.';
	return str;
}


void TestMakeSentence() {
	DynamicArray<char*> words;
	int wordsLen = 0;
	char* currWord;
	do {
		std::cout << "Enter the next word, simply enter to quit: ";
		currWord = readStringFromCIn();
		words.push_back(currWord);
	} while (currWord != nullptr);

	size_t size = words.size();
	char** wordsArr = new char* [size];
	for(size_t i =0;i<size; i++) {
		wordsArr[i] = words[i];
	}
	std::cout << std::endl;
	char* pSentence = MakeSentence(wordsArr);
	printf("The Sentence is: %s\n", pSentence);
	
	// free(pSentence);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
