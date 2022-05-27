#ifndef GAME_MULTIPLESTREAM_H
#define GAME_MULTIPLESTREAM_H


#include <vector>
#include <memory>
#include "Stream.h"

class MultipleStream : public Stream {
public:
    explicit MultipleStream(const std::vector<std::shared_ptr<Stream>> &streams);

    void Write(const std::string &str) override;

private:
    std::vector<std::shared_ptr<Stream>> streams_;
};

#endif //GAME_MULTIPLESTREAM_H
