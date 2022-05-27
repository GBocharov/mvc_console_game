//
// Created by gleb on 1/31/21.
//

#ifndef GAME_INPUT_H
#define GAME_INPUT_H

enum class Command {
    EXIT,
    NEW_GAME,
    LOAD_GAME,
    SAVE_GAME,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Input {
public:
    static Command GetCommand();
};


#endif //GAME_INPUT_H
