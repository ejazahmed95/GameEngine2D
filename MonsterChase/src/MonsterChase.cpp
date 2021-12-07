// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

char* readStringFromCIn() {
    char a[50];
    size_t len = 0;
    while (len <= 50) {
        char c;
        c = std::getchar();
        if (c != '\n' && c != '\0') {
            a[len++] = c;
        } else break;
    }
    if (len == 0) return nullptr;
    len++;
    char* str = new char[len];
    memcpy(str, a, len - 1);
    str[len - 1] = '\0';
    return str;

}


void MonsterChase::Run() {
    int mCount;
    this->mc_ = new MonsterController();

    std::cout << "Enter Player Name" << std::endl;
    char* playerName = readStringFromCIn();
    this->pc_ = new PlayerController(playerName);

    std::cout << "How many monsters do you want?" << std::endl;
    std::cin >> mCount;
    std::cin.ignore();
    for (int i = 0; i < mCount; i++) {
        std::cout << "Enter the name of monster " << i + 1 << ": ";
        mc_->addMonster(readStringFromCIn());
    }
    startGame();
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

MonsterChase::~MonsterChase()
{
    delete pc_;
    delete mc_;
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
