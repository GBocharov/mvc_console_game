#ifndef OOP_GAME_GAME_H_
#define OOP_GAME_GAME_H_

#include <memory>
#include <vector>
#include "../Log/Logger.h"
#include "../Render/Framebuffer.h"
#include "../Saveable/Saveable.h"
#include "../Log/Loggable.h"

class Map;
class Player;
class BaseEnemy;

class Game : std::enable_shared_from_this<Game>, public Loggable, public Saveable {
public:
    Game();

    void Run();

    std::shared_ptr<Map> GetMap() {
        return map_;
    }

    std::shared_ptr<Player> GetPlayer() {
        return player_;
    }

private:
    bool Finished();

    void Update();

    void Draw();

    void Save(std::ofstream &file) override;

    void SetLogger(const std::shared_ptr<ILogger> &logger) override;

    std::shared_ptr<Map> map_;
    std::shared_ptr<Player> player_;
    bool run_{true};
    std::vector<std::shared_ptr<BaseEnemy>> enemies_;

    void NewGame();

    void Load(std::ifstream &file);

    std::shared_ptr<Framebuffer> framebuffer_;
};

#endif // OOP_GAME_GAME_H_

