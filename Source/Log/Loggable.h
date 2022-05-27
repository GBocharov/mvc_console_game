#ifndef GAME_LOGGABLE_H
#define GAME_LOGGABLE_H


#include <memory>
#include "ILogger.h"
#include "ILoggable.h"

class Loggable : public ILoggable {
public:
    void SetLogger(const std::shared_ptr<ILogger> &logger) override;
protected:
    std::shared_ptr<ILogger> logger_;
};

#endif //GAME_LOGGABLE_H
