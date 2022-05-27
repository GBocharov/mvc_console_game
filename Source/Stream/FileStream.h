#ifndef GAME_FILESTREAM_H
#define GAME_FILESTREAM_H

#include <fstream>
#include "Stream.h"

class FileStream : public Stream {
public:
    FileStream(const std::string &filename);

    void Write(const std::string &str) override;

private:
    std::ofstream file_;
};


#endif //GAME_FILESTREAM_H
