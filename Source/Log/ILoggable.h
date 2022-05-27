//
// Created by gleb on 2/2/21.
//

#ifndef GAME_ILOGGABLE_H
#define GAME_ILOGGABLE_H


#include <memory>
#include "ILogger.h"

class ILoggable {
public:
    virtual void SetLogger(const std::shared_ptr<ILogger> &logger) = 0;

    ~ILoggable() = default;
};


#endif //GAME_ILOGGABLE_H
