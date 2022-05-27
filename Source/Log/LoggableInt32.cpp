//
// Created by gleb on 1/28/21.
//

#include "LoggableInt32.h"

int32_t LoggableInt32::Get() {
    return value_;
}

void LoggableInt32::Set(int32_t val) {
    logger_ << (name_ + ": " + std::to_string(value_) + " -> " + std::to_string(val));
    value_ = val;
}

LoggableInt32::LoggableInt32(const std::string &name, int32_t value)
        : name_{name}, value_{value} {
}
