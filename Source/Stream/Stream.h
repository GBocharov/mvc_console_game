#ifndef GAME_STREAM_H
#define GAME_STREAM_H

#include <string>

class Stream {
public:
    virtual void Write(const std::string &str) = 0;

    ~Stream() = default;
};

#endif //GAME_STREAM_H
