#include "Cell.h"
#include "ImpassableCell.h"
#include "OrdinaryCell.h"

#include <fstream>

std::shared_ptr<Cell> Cell::Load(std::ifstream &file, coord_t coord) {
    int type;
    file >> type;
    if (type == 0) {
        return std::make_shared<ImpassableCell>();
    } else if (type == 1) {
        bool is_buff;
        file >> is_buff;
        std::shared_ptr<Buff> buff;
        if (is_buff) {
            buff = Buff::Load(file);

            if (buff->GetCooord() != coord)
                throw std::runtime_error("Cell coord!=Buff coord");
        }
        return std::make_shared<OrdinaryCell>(buff);
    } else if (type == 2) {
        return std::make_shared<PassableCell>();
    } else {
        throw std::runtime_error("Bad cell");
    }
}
