// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

char* readStringFromCIn() {
    char a[20];
    std::cin >> a;
    int len = 1;
    while (len <= 20 && a[len-1] != '\n') len++;
    //char* str = (char*)malloc(len * sizeof(char));
    char* str = new char[len];
    memcpy(str, a, len-1);
    str[len - 1] = '\0';
    return str;
}


void MonsterChase::Run() {
    // _CrtSetBreakAlloc(451);
    {
        int mCount;
        this->mc_ = new MonsterController();

        std::cout << "Enter Player Name" << std::endl;
        char* playerName = readStringFromCIn();
        this->pc_ = new PlayerController(playerName);

        std::cout << "How many monsters do you want?" << std::endl;
        std::cin >> mCount;
        for (int i = 0; i < mCount; i++) {
            std::cout << "Enter the name of monster " << i << ": ";
            mc_->addMonster(readStringFromCIn());
        }
        startGame();
        delete pc_;
        delete mc_;
    }
    _CrtDumpMemoryLeaks();
}

void MonsterChase::startGame() {
    while (true) {
        std::cout << "Please use WASD to move and Q to quit" << std::endl;
        char in = standardInputReader().readChar();
        if (in == 'q' || in == 'Q') break;
        pc_->handleInput(in);
        updateAllObjects();
        std::cout << *pc_ << std::endl;
        std::cout << *mc_ << std::endl;
    }
}

void MonsterChase::updateAllObjects() {
    pc_->update(0);
    mc_->update(0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
