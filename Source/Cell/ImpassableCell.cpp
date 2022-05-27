#include "ImpassableCell.h"

#include <fstream>

bool ImpassableCell::Pass() {
	return false;
}

std::shared_ptr<Cell> ImpassableCell::Copy() {
	return std::make_shared<ImpassableCell>();
}

void ImpassableCell::Save(std::ofstream &file) {
    file << 0 << std::endl;
}

void ImpassableCell::Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) {
    framebuffer->SetPixel(coord, '#');
}
