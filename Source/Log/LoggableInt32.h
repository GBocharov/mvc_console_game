
#ifndef GAME_LOGGABLEINT32_H
#define GAME_LOGGABLEINT32_H


#include "Loggable.h"

class LoggableInt32 : public Loggable {
public:
    LoggableInt32(const std::string &name, int32_t value);
    int32_t Get();

    void Set(int32_t val);

private:
    std::string name_;
    int32_t value_;
};


#endif //GAME_LOGGABLEINT32_H
