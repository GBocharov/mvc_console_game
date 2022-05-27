#include <memory>
#include <iostream>
#include "Log/Logger.h"
#include "Player/Player.h"
#include "Game/Game.h"

int main() {
    std::shared_ptr<Game> game{std::make_shared<Game>()};

    try {
        game->Run();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
