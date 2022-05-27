#ifndef GAME_ILOGGER_H
#define GAME_ILOGGER_H

#include <string>

class ILogger {
public:
    virtual void Log(const std::string &str) = 0;

    friend std::shared_ptr<ILogger> operator<<(const std::shared_ptr<ILogger> &logger, const std::string &str) {
        if (logger) { logger->Log(str); }
        return logger;
    }

    ~ILogger() = default;
};


#endif //GAME_ILOGGER_H
