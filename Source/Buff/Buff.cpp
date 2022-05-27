#include "Buff.h"

#include <fstream>

#include "../Player/Player.h"

std::shared_ptr<Buff> Buff::Copy() {
    return std::make_shared<Buff>(coord_, type_);
}


coord_t Buff::GetCooord() {
    return coord_;
}

bool Buff::Influence(Player &player) {
    std::string type_str;
    switch (type_) {
        case Buff::TYPE::HEALTH:
            player.ChangeHP(1);
            type_str = "health";
            break;
        case Buff::TYPE::FLESH_HEAP:
            player.ChangeFH(1);
            type_str = "flesh heap";
            break;
        case Buff::TYPE::MANA:
            player.ChangeMana(1);
            type_str = "mana";
            break;
    }

    if (logger_) {
        logger_->Log("buff(" + type_str + ")"
                     + "[" +
                     std::to_string(coord_.first) + ", " +
                     std::to_string(coord_.second) +
                     "]: disappeared");
    }
    return true;
}

Buff::Buff(coord_t coord, TYPE type)
        : coord_{coord}, type_{type} {
}

void Buff::Save(std::ofstream &file) {
    file << coord_.first << " " << coord_.second << std::endl;
    file << (int) type_ << std::endl;
}

std::shared_ptr<Buff> Buff::Load(std::ifstream &file) {
    coord_t coord;
    file >> coord.first >> coord.second;
    int type;
    file >> type;

    if ((int) Buff::TYPE::FLESH_HEAP > type || (int) Buff::TYPE::MANA < type)
        throw std::runtime_error("Bad Buff type");

    return std::make_shared<Buff>(coord, (Buff::TYPE) type);
}

void Buff::Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) {
    char c;
    if (type_ == TYPE::FLESH_HEAP) {
        c = 'F';
    } else if (type_ == TYPE::MANA) {
        c = 'M';
    } else if (type_ == TYPE::HEALTH) {
        c = 'H';
    } else {
        c = ' ';
    }
    framebuffer->SetPixel(coord, c);
}

