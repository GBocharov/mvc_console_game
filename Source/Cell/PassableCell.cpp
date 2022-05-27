#include "PassableCell.h"

#include <fstream>

std::shared_ptr<Cell> PassableCell::Copy() {
    return std::make_shared<PassableCell>();
}

bool PassableCell::Pass() {
    return true;
}

void PassableCell::Save(std::ofstream &file) {
    file << 2 << std::endl;
}

void PassableCell::Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) {
    framebuffer->SetPixel(coord, ' ');
}
