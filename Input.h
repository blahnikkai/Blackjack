//
// Created by Kai Blahnik on 8/10/22.
//

#ifndef POKER_INPUT_H
#define POKER_INPUT_H

#include <string>
#include <iostream>

std::string userInput() {
    std::string input;
    std::getline(std::cin, input);
    if(input == "quit") exit(1);
    return input;
}

bool okContinue() {
    std::cout << "Type ok to continue\n";
    string input = userInput();
    if(input != "ok") okContinue();
}

#endif //POKER_INPUT_H
