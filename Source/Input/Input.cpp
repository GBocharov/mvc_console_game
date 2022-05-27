//
// Created by gleb on 1/31/21.
//

#include <iostream>
#include "Input.h"

Command Input::GetCommand() {
    char c;
    while (std::cin.get(c)) {
        if (c == 'q') {
            return Command::EXIT;
        } else if (c == 'l') {
            return Command::LOAD_GAME;
        } else if (c == 'k') {
            return Command::SAVE_GAME;
        } else if (c == 'n') {
            return Command::NEW_GAME;
        } else if (c == 'w') {
            return Command::DOWN;
        } else if (c == 's') {
            return Command::UP;
        } else if (c == 'd') {
            return Command::RIGHT;
        } else if (c == 'a') {
            return Command::LEFT;
        }
    }
    throw std::runtime_error("Unexpected EOF");
}
