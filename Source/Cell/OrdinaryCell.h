#ifndef OOP_CELL_ORDINARY_CELL_H_
#define OOP_CELL_ORDINARY_CELL_H_

#include "PassableCell.h"
#include "../Buff/Buff.h"
#include "../Log/ILogger.h"
#include "../Log/Loggable.h"
#include "../Def.h"

class OrdinaryCell : public Loggable, public PassableCell {
	friend class OrdinaryCellView;

public:
	OrdinaryCell() = default;

	explicit OrdinaryCell(const std::shared_ptr<Buff> &buff);

	OrdinaryCell(const OrdinaryCell &other);

	std::shared_ptr<Cell> Copy() override;

	void Save(std::ofstream &file) override;

	void operator+(Player &player) override;

	void Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) override;

	void SetLogger(const std::shared_ptr<ILogger> &logger) override;

private:
	std::shared_ptr<Buff> buff_;
};

#endif // OOP_CELL_ORDINARY_CELL_H_

