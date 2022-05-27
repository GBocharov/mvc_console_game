#include "OrdinaryCell.h"

#include <fstream>

OrdinaryCell::OrdinaryCell(const OrdinaryCell &other)
        : buff_{other.buff_ ? other.buff_->Copy() : nullptr} {
}

std::shared_ptr<Cell> OrdinaryCell::Copy() {
    return std::make_shared<OrdinaryCell>(*this);
}

void OrdinaryCell::operator+(Player &player) {
    if (buff_) {
        if (buff_->Influence(player)) {
            buff_.reset();
        }
    }
}

OrdinaryCell::OrdinaryCell(const std::shared_ptr<Buff> &buff)
        : buff_{buff} {
}

void OrdinaryCell::Save(std::ofstream &file) {
    file << 1 << std::endl;
    if (buff_) {
        file << 1 << std::endl;
        buff_->Save(file);
    } else {
        file << 0 << std::endl;
    }
}

void OrdinaryCell::Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) {
    if (buff_) { buff_->Draw(framebuffer, coord); }
}

void OrdinaryCell::SetLogger(const std::shared_ptr<ILogger> &logger) {
    if (buff_) {
        buff_->SetLogger(logger);
    }
}

