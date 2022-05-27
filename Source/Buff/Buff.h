#ifndef OOP_BUFF_BUFF_H_
#define OOP_BUFF_BUFF_H_

#include <memory>
#include "../Log/Loggable.h"
#include "../Def.h"
#include "../Log/LoggableCoord.h"
#include "../Render/Framebuffer.h"
#include "../Saveable/Saveable.h"

class Player;

class Buff : public Loggable, Saveable {
public:
    enum class TYPE : int {
        FLESH_HEAP,
        HEALTH,
        MANA
    };

    Buff(coord_t coord, TYPE type);

    std::shared_ptr<Buff> Copy();

    coord_t GetCooord();

    bool Influence(Player &player);

    void Save(std::ofstream &file) override;

    static std::shared_ptr<Buff> Load(std::ifstream &file);

    void Draw(const std::shared_ptr<Framebuffer> &framebuffer, coord_t coord);

protected :
    coord_t coord_;
    TYPE type_;
};

#endif // OOP_BUFF_BUFF_H_

