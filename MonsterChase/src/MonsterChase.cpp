// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MCGameManager.h"
#include "PlayerController.h"
#include "MonsterController.h"
#include "MonsterChase.h"
#include "Raven.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

void MonsterChase::Run() {
    bool hasQuit = false;
    int gridSize, mCount;
    std::string playerName;
    while (!hasQuit) {
        std::cout << "Enter Name" << std::endl;
        std::cin >> playerName;
        std::cout << "Enter the grid size and the number of monsters you want to add" << std::endl;
        std::cin >> gridSize >> mCount;
        break;
    }
    PlayerController pc(playerName);
    MonsterController mc(mCount);
    MCGameManager gm(pc, mc, gridSize);

    gm.Play();
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
