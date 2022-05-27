#ifndef OOP_ENEMY_ENEMY_H_
#define OOP_ENEMY_ENEMY_H_

#include <fstream>

#include "../Def.h"
#include "../Input/Input.h"
#include "../Map/Map.h"
#include "../Game/Game.h"
#include "../Player/Player.h"

void SimpleAttack1(Player *player);

void AttackDecay1(Player *player);

void AttackManaDrain1(Player *player);

coord_t SimpleRandMove(Map *map, coord_t coord);


class BaseEnemy : public Saveable {
public:
    explicit BaseEnemy(coord_t coord)
            : coord_{coord} {}

    bool Update(Game *game);

    static std::shared_ptr<BaseEnemy> Load(std::ifstream &file);

    virtual void Draw(const std::shared_ptr<Framebuffer> &framebuffer) = 0;

    friend void operator+(const std::shared_ptr<Player> &player, BaseEnemy *enemy) {
        enemy->Attack(player.get());
    }

    coord_t GetCoord();

    virtual ~BaseEnemy() = default;

protected:

    virtual coord_t Move(Map *map, coord_t coord) = 0;

    virtual void Attack(Player *player) = 0;
    coord_t coord_;
};



template<coord_t (*MovePolicy)(Map *, coord_t),
        void (*AttackPolicy)(Player *),
        char C>
class Enemy : public BaseEnemy {
public:
    explicit Enemy(coord_t coord)
            : BaseEnemy{coord} {}

    void Save(std::ofstream &file) override;

    void Draw(const std::shared_ptr<Framebuffer> &framebuffer) override;

    coord_t Move(Map *map, coord_t coord) override;

    void Attack(Player *player) override;
};



template<coord_t (*MovePolicy)(Map *, coord_t),
        void (*AttackPolicy)(Player *),
        char C>
void Enemy<MovePolicy, AttackPolicy, C>::Draw(const std::shared_ptr<Framebuffer> &framebuffer) {
    framebuffer->SetPixel(coord_, C);
}

template<coord_t (*MovePolicy)(Map *, coord_t),
        void (*AttackPolicy)(Player *),
        char C>
void Enemy<MovePolicy, AttackPolicy, C>::Save(std::ofstream &file) {
    file << coord_.first << " " << coord_.second << std::endl;
    if (AttackPolicy == SimpleAttack1) {
        file << 0 << std::endl;
    } else if (AttackPolicy == AttackDecay1) {
        file << 1 << std::endl;
    } else if (AttackPolicy == AttackManaDrain1) {
        file << 2 << std::endl;
    }
}

template<coord_t (*MovePolicy)(Map *, coord_t),
        void (*AttackPolicy)(Player *), char C>
void Enemy<MovePolicy, AttackPolicy, C>::Attack(Player *player) {
    AttackPolicy(player);
}

template<coord_t (*MovePolicy)(Map *, coord_t),
        void (*AttackPolicy)(Player *), char C>
coord_t Enemy<MovePolicy, AttackPolicy, C>::Move(Map *map, coord_t coord) {
    return MovePolicy(map, coord);
}


#endif //OOP_ENEMY_ENEMY_H_
