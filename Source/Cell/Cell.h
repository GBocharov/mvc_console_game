#ifndef OOP_CELL_CELL_H_
#define OOP_CELL_CELL_H_

#include <memory>
#include "../Def.h"
#include "../Render/Framebuffer.h"
#include "../Saveable/Saveable.h"
#include "../Log/ILoggable.h"

class Player;

class Cell : public ILoggable, public Saveable {
public:
    virtual bool Pass() = 0;

    virtual std::shared_ptr<Cell> Copy() = 0;

    virtual void operator+(Player &player) {};

    virtual ~Cell() = default;

    virtual void Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord) = 0;

    static std::shared_ptr<Cell> Load(std::ifstream &file, coord_t coord);

    void SetLogger(const std::shared_ptr<ILogger> &logger) override {}
};

#endif // OOP_CELL_CELL_H_

