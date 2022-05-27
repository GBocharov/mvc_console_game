#ifndef OOP_CELL_PASSABLE_CELL_H_
#define OOP_CELL_PASSABLE_CELL_H_

#include "Cell.h"

class PassableCell : public Cell {
public:
    bool Pass() override;

    void Save(std::ofstream &file) override;

    void Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) override;

    std::shared_ptr<Cell> Copy() override;
};

#endif // OOP_CELL_PASSABLE_CELL_H_

