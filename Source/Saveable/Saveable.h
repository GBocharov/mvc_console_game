//
// Created by gleb on 2/2/21.
//

#ifndef GAME_SAVEABLE_H
#define GAME_SAVEABLE_H

#include "../Render/Framebuffer.h"

class Saveable {
public:
    virtual void Save(std::ofstream &file) = 0;
};


#endif //GAME_SAVEABLE_H
