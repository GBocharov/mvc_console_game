#include "Player.h"

#include <fstream>

Player::Player(coord_t coord)
        : child_logger_{std::make_shared<PlayerLogger>()},
          health_{"health", 100},
          mana_{"mana", 20},
          flesh_heap_{"flesh heap", 13},
          coord_{"coord", coord} {
    health_.SetLogger(child_logger_);
    mana_.SetLogger(child_logger_);
    flesh_heap_.SetLogger(child_logger_);
    coord_.SetLogger(child_logger_);
}

std::shared_ptr<Player> Player::Create(coord_t coord) {
    auto res = std::make_shared<Player>(coord);
    res->child_logger_->player_ = res;
    return res;
}

void PlayerLogger::Log(const std::string &str) {
    auto player = player_.lock();
    if (player) { player->logger_ << ("player: " + str); }
}

void Player::Move(std::shared_ptr<Map> &map, Command command) {
    auto old_cell = map->GetCell(coord_.Get());
    auto new_coord = coord_.Get();
    if (command == Command::UP) {
        new_coord.second++;
    } else if (command == Command::DOWN) {
        new_coord.second--;
    } else if (command == Command::RIGHT) {
        new_coord.first++;
    } else if (command == Command::LEFT) {
        new_coord.first--;
    } else {
        return;
    }
    auto new_cell = map->GetCell(new_coord);
    if (new_cell && new_cell->Pass()) {
        coord_.Set(new_coord);
        *new_cell + *this;
    } else {
        //?????????
    }
}

coord_t Player::GetCoord() {
    return coord_.Get();
}

void Player::ChangeHP(int diff) {
    int32_t hp = health_.Get();
    health_.Set(std::max(0, hp + diff));
}

void Player::ChangeMana(int diff) {
    int32_t mana = mana_.Get();
    mana_.Set(std::max(0, mana + diff));
}

void Player::ChangeFH(int diff) {
    int32_t fh = flesh_heap_.Get();
    flesh_heap_.Set(std::max(0, fh + diff));
}

std::shared_ptr<Player> Player::Load(std::ifstream &file) {
    coord_t coord;
    int32_t fh, mp, hp;

    file >> coord.first >> coord.second;
    file >> fh >> mp >> hp;

    auto res = Player::Create(coord);
    res->flesh_heap_.Set(fh);
    res->mana_.Set(mp);
    res->health_.Set(hp);

    return res;
}

void Player::Save(std::ofstream &file) {
    file << coord_.Get().first << " " << coord_.Get().second << std::endl;
    file << flesh_heap_.Get() << std::endl;
    file << mana_.Get() << std::endl;
    file << health_.Get() << std::endl;
}

void Player::Draw(const std::shared_ptr<Framebuffer> &framebuffer) {
    framebuffer->SetPixel(coord_.Get(), 'P');
}

void Player::SetLogger(const std::shared_ptr<ILogger> &logger) {
    Loggable::SetLogger(logger);
    coord_.SetLogger(child_logger_);
    health_.SetLogger(child_logger_);
    mana_.SetLogger(child_logger_);
    flesh_heap_.SetLogger(child_logger_);
}
