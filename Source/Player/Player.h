#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include <memory>

#include "../Log/Loggable.h"
#include "../Log/LoggableInt32.h"
#include "../Log/LoggableCoord.h"
#include "../Input/Input.h"
#include "../Map/Map.h"

class PlayerLogger;

class Player : public Loggable, std::enable_shared_from_this<Player> {
public:
    explicit Player(coord_t coord);

    LoggableInt32 health_;
    LoggableInt32 mana_;
    LoggableInt32 flesh_heap_;

    LoggableCoord coord_;

    friend class PlayerLogger;

    static std::shared_ptr<Player> Create(coord_t coord);

    void Move(std::shared_ptr<Map> &map, Command command);

    void Draw(const std::shared_ptr<Framebuffer> &framebuffer);

    coord_t GetCoord();

    void ChangeHP(int diff);

    void ChangeMana(int diff);

    void ChangeFH(int diff);

    static std::shared_ptr<Player> Load(std::ifstream &file);

    void Save(std::ofstream &file);

    void SetLogger(const std::shared_ptr<ILogger> &logger) override;

private:
    std::shared_ptr<PlayerLogger> child_logger_;
};

class PlayerLogger : public ILogger {
public:
    friend class Player;

    void Log(const std::string &str) override;

private:
    std::weak_ptr<Player> player_;
};

#endif //GAME_PLAYER_H
