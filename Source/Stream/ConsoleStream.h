#ifndef GAME_CONSOLESTREAM_H
#define GAME_CONSOLESTREAM_H

#include "Stream.h"

class ConsoleStream : public Stream {
public:
    void Write(const std::string &str) override;
};


#endif //GAME_CONSOLESTREAM_H
