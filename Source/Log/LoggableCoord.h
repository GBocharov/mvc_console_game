//
// Created by gleb on 1/28/21.
//

#ifndef GAME_LOGGABLECOORD_H
#define GAME_LOGGABLECOORD_H


#include "Loggable.h"
#include "../Def.h"

class LoggableCoord : public Loggable {
public:
    LoggableCoord(const std::string &name, coord_t value);

    coord_t Get();

    void Set(coord_t val);

private:
    std::string name_;
    coord_t value_;
};


#endif //GAME_LOGGABLECOORD_H
