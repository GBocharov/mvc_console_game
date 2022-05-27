#include <fstream>
#include "Map.h"

#include "../Cell/OrdinaryCell.h"
#include "../Cell/ImpassableCell.h"
#include "../Render/Framebuffer.h"

void Map::AllocCellsPointers(const coord_t &size) {
    size_ = size;
    cells_ = std::make_unique<std::shared_ptr<Cell>[]>(size.first * size.second);
}

void Map::Copy(const Map &other) {
    if (this == &other) {
        return;
    }

    AllocCellsPointers(other.size_);
    for (size_t i = 0; i < size_.first * size_.second; ++i) {
        cells_[i] = other.cells_[i]->Copy();
    }

    enter_coord_ = other.enter_coord_;
    exit_coord_ = other.exit_coord_;
}

Map::Map(coord_t size)
        : size_{size} {
}

void Map::Init() {
    AllocCellsPointers(size_);
    for (size_t y = 0; y < size_.second; ++y) {
        for (size_t x = 0; x < size_.first; ++x) {
            std::shared_ptr<Buff> buff;
            int r = rand() % 12;
            if (r == 0) {
                buff = std::make_shared<Buff>(coord_t{x, y}, Buff::TYPE::HEALTH);
            } else if (r == 1) {
                buff = std::make_shared<Buff>(coord_t{x, y}, Buff::TYPE::MANA);
            } else if (r == 2) {
                buff = std::make_shared<Buff>(coord_t{x, y}, Buff::TYPE::FLESH_HEAP);
            }
            cells_[y * size_.first + x] = std::make_shared<OrdinaryCell>(buff);
        }
    }

    enter_coord_ = {0, 0};
    exit_coord_ = {size_.first - 1, size_.second - 1};
    GetCellRef(enter_coord_) = std::make_shared<PassableCell>();
    GetCellRef(exit_coord_) = std::make_shared<PassableCell>();

    GetCellRef({size_.first / 2, size_.second / 2}) = std::make_shared<ImpassableCell>();
}

Map::Map(const Map &other) {
    Copy(other);
}

Map &Map::operator=(const Map &other) {
    Copy(other);

    return *this;
}

void Map::Move(Map &other) {
    if (this == &other) {
        return;
    }

    enter_coord_ = other.enter_coord_;
    exit_coord_ = other.exit_coord_;
    size_ = other.size_;
    cells_ = std::move(other.cells_);
}

Map::Map(Map &&other) {
    Move(other);
}

Map &Map::operator=(Map &&other) {
    Move(other);

    return *this;
}

std::shared_ptr<Cell> &Map::GetCellRef(const coord_t &coord) {
    return cells_[coord.first + coord.second * size_.first];
}

std::shared_ptr<Cell> Map::GetCell(const coord_t &coord) {
    if (coord.first < size_.first && coord.second < size_.second) {
        return GetCellRef(coord);
    } else {
        return nullptr;
    }
}

coord_t Map::GetEnterCoord() {
    return enter_coord_;
}

coord_t Map::GetExitCoord() {
    return exit_coord_;
}


coord_t Map::GetSize() {
    return size_;
};

void Map::Save(std::ofstream &file) {
    file << size_.first << " " << size_.second << std::endl;
    file << enter_coord_.first << " " << enter_coord_.second << std::endl;
    file << exit_coord_.first << " " << exit_coord_.second << std::endl;
    for (int i = 0; i < size_.first * size_.second; ++i) {
        cells_[i]->Save(file);
    }
}

std::shared_ptr<Map> Map::Load(std::ifstream &file) {
    coord_t size, enter, exit;
    file >> size.first >> size.second;
    file >> enter.first >> enter.second;
    file >> exit.first >> exit.second;

    auto res = std::make_shared<Map>(size);
    res->enter_coord_ = enter;
    res->exit_coord_ = exit;
    res->AllocCellsPointers(size);
    for (int i = 0; i < size.first * size.second; ++i) {
        res->cells_[i] = Cell::Load(file, coord_t{i % size.first, i / size.first,});
    }
    return res;
}

void Map::Draw(const std::shared_ptr<Framebuffer> &framebuffer) {
    for (int y = 0; y < size_.second; ++y) {
        for (int x = 0; x < size_.first; ++x) {
            cells_[x + y * size_.first]->Draw(framebuffer, {x, y});
        }
    }
}

void Map::SetLogger(const std::shared_ptr<ILogger> &logger) {
    for (int i = 0; i < size_.first * size_.second; ++i) {
        if (cells_[i]) {
            cells_[i]->SetLogger(logger);
        }
    }
}
