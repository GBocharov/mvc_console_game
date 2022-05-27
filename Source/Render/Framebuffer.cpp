#include "Framebuffer.h"

#include <iostream>

Framebuffer::Framebuffer(const coord_t &size)
        : size_{size} {
    buffer_.resize((size_.first + 1) * size_.second);
    Clear();
}

void Framebuffer::SetPixel(const coord_t &coord, char value) {
    buffer_[coord.first + coord.second * (size_.first + 1)] = value;
}

void Framebuffer::Clear() {
    for (size_t i = 0; i < size_.second; ++i) {
        for (size_t j = 0; j < size_.first; ++j) {
            SetPixel({j, i}, ' ');
        }
        SetPixel({size_.first, i}, '\n');
    }
}

void Framebuffer::Present() {
    std::cout << buffer_;
}
