//
// Created by gleb on 1/28/21.
//

#include "LoggableCoord.h"

LoggableCoord::LoggableCoord(const std::string &name, coord_t value)
        : name_{name}, value_{value} {
}

coord_t LoggableCoord::Get() {
    return value_;
}

void LoggableCoord::Set(coord_t val) {
    if (logger_) {
        logger_ << (name_ + ": {" +
                     std::to_string(value_.first) + ", " +
                     std::to_string(value_.second) +
                     "} -> {" +
                     std::to_string(val.first) + ", " +
                     std::to_string(val.second) +
                     "}");
    }

    value_ = val;
}
