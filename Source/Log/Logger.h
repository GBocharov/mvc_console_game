#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <string>
#include <memory>

#include "../Stream/Stream.h"
#include "ILogger.h"

class Logger : std::enable_shared_from_this<Logger>, public ILogger {
public:
    explicit Logger(const std::shared_ptr<Stream> &stream);

    void Log(const std::string &str) override;

    static std::shared_ptr<Logger> Create(const std::shared_ptr<Stream> &stream);

private:
    std::shared_ptr<Stream> stream_;
};

#endif //GAME_LOGGER_H
