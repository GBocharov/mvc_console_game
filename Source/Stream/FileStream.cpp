//
// Created by gleb on 1/28/21.
//

#include "FileStream.h"

void FileStream::Write(const std::string &str) {
    file_ << str;
}

FileStream::FileStream(const std::string &filename)
        : file_{filename} {
}
