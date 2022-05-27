#ifndef OOP_CELL_IMPASSABLE_CELL_H_
#define OOP_CELL_IMPASSABLE_CELL_H_

#include "Cell.h"

class ImpassableCell : public Cell {
public:
	bool Pass() override;

	std::shared_ptr<Cell> Copy() override;

	void Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) override;

	void Save(std::ofstream &file) override;
};

#endif // OOP_CELL_IMPASSABLE_CELL_H_

