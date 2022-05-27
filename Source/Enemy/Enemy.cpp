#include "Enemy.h"

void SimpleAttack1(Player *player) {
    player->ChangeHP(-1);
}

void AttackDecay1(Player *player) {
    player->ChangeFH(-1);
}

void AttackManaDrain1(Player *player) {
    player->ChangeMana(-1);
}

coord_t SimpleRandMove(Map *map, coord_t coord) {
    coord_t new_coord = coord;
    new_coord.first += rand() % 2 - 1;
    new_coord.second += rand() % 2 - 1;
    if (map->GetCell(new_coord) && map->GetCell(new_coord)->Pass()) {
        return new_coord;
    } else {
        return coord;
    }
}

std::shared_ptr<BaseEnemy> BaseEnemy::Load(std::ifstream &file) {
    coord_t coord;
    file >> coord.first >> coord.second;
    int attack_policy;
    file >> attack_policy;
    if (attack_policy == 0) {
        return std::make_shared<Enemy<SimpleRandMove, SimpleAttack1, 'S'>>(coord);
    } else if (attack_policy == 1) {
        return std::make_shared<Enemy<SimpleRandMove, AttackDecay1, 'D'>>(coord);
    } else if (attack_policy == 2) {
        return std::make_shared<Enemy<SimpleRandMove, AttackManaDrain1, 'A'>>(coord);
    } else {
        throw std::runtime_error("Wrong Enemy");
    }
}

bool BaseEnemy::Update(Game *game) {
    coord_t new_coord = Move(game->GetMap().get(), coord_);

    auto player = game->GetPlayer();

    coord_ = new_coord;
    if (new_coord == player->GetCoord()) {
        player + this;
        return true;
    }
    return false;
}


coord_t BaseEnemy:: GetCoord()
{
    return coord_;
};
