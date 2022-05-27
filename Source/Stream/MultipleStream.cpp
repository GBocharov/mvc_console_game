//
// Created by gleb on 1/28/21.
//

#include "MultipleStream.h"

MultipleStream::MultipleStream(const std::vector<std::shared_ptr<Stream>> &streams)
    : streams_{streams}{
}

void MultipleStream::Write(const std::string &str) {
    for (const auto &stream : streams_) {
        stream->Write(str);
    }
}
