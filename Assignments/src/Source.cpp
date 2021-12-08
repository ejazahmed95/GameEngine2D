// IndependentCodes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MakeSentence/MakeSentence.h"
#include "InterviewQuestions/TestQuestions.h"

int main()
{
    // _CrtSetBreakAlloc(181);
    {
        using namespace std;
        int input = 0;

        do {
            std::cout << "Following assignments are available to test in this project (See README.md for other assignments)" << std::endl;
            std::cout << "5 = Make Sentence" << endl;
            std::cout << "7 = Test Interview Questions" << endl;
            std::cout << "Enter 0 to exit the program" << endl;
            std::cout << "Enter your choice:: ";
            cin >> input;
            switch(input) {
            case 5: /* Assignment 1.05 */
                std::cout << "\n========== Welcome to Assignment 5 ============" << std::endl;
                cin.ignore();
                TestMakeSentence();
                std::cout << "=========== ** END ** =============" << std::endl;
                break;
            case 7: /* Assignment 1.07 */
                std::cout << "\n========== Welcome to Assignment 7 ============" << std::endl;
                TestLinkedListHasCycle();
                TestArrayOrderZeros();
                std::cout << "=========== ** END ** =============" << std::endl;
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid Input" << endl;
            }
            std::cout << "\n\n";
        } while (input != 0);
    }

    // Testing memory leaks
    std::cout << "Please Wait... checking for memory leaks in the current session" << std::endl;
    _CrtDumpMemoryLeaks();
    std::cout << "Check Completed" << std::endl;
}

