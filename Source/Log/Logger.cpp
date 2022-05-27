#include "Logger.h"

Logger::Logger(const std::shared_ptr<Stream> &stream)
        : stream_{stream} {
}

std::shared_ptr<Logger> Logger::Create(const std::shared_ptr<Stream> &stream) {
    auto res = std::make_shared<Logger>(stream);
    return res;
}

void Logger::Log(const std::string &str) {
    stream_->Write(str);
    stream_->Write("\n");
}

