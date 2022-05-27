#include <fstream>
#include <iostream>
#include "Game.h"

#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Stream/ConsoleStream.h"
#include "../Stream/MultipleStream.h"
#include "../Stream/FileStream.h"

Game::Game() {
    framebuffer_ = std::make_shared<Framebuffer>(coord_t{6, 5});
    NewGame();
}

void Game::NewGame() {
    logger_ = Logger::Create(std::make_shared<ConsoleStream>());
    /* logger_ = Logger::Create(std::make_shared<MultipleStream>(
              std::vector<std::shared_ptr<Stream>>{
                      std::make_shared<ConsoleStream>(),
                      std::make_shared<FileStream>("1.txt")
              }
      ));*/

    map_ = std::make_shared<Map>(coord_t{6, 5});
    map_->Init();
    map_->SetLogger(logger_);
    player_ = Player::Create(map_->GetEnterCoord());
    player_->SetLogger(logger_);

    enemies_.push_back(std::make_shared<Enemy<SimpleRandMove, SimpleAttack1, 'S'>>(coord_t{2, 1}));
    enemies_.push_back(std::make_shared<Enemy<SimpleRandMove, AttackDecay1, 'D'>>(coord_t{5, 4}));
    enemies_.push_back(std::make_shared<Enemy<SimpleRandMove, AttackManaDrain1, 'A'>>(coord_t{5, 1}));
}

void Game::Run() {
    Draw();
    while (!Finished()) {
        Update();
        Draw();
    }
    std::cout << "Game ended" << std::endl;
}

bool Game::Finished() {
    auto exit_coord = map_->GetExitCoord();
    return !run_ || (player_->coord_.Get() == exit_coord && player_->flesh_heap_.Get() > 3);
}

void Game::Update() {
    Command command = Input::GetCommand(); //!!!
    if (command == Command::EXIT) {
        run_ = false;
        return;
    } else if (command == Command::LOAD_GAME) {
        std::ifstream save{"save.txt"};
        if (!save) {
            throw std::runtime_error("No save file!");
        }
        Load(save);
        return;
    } else if (command == Command::SAVE_GAME) {
        std::ofstream save{"save.txt"};
        Save(save);
        return;
    } else if (command == Command::NEW_GAME) {
        NewGame();
        return;
    } else {
        player_->Move(map_, command);
    }

    for (auto &enemy : enemies_) {
        if (enemy && enemy->Update(this)) {
            enemy.reset();
        }
    }
}

void Game::Save(std::ofstream &file) {
    map_->Save(file);
    player_->Save(file);

    //file << enemies_.size() << std::endl;

    int en_count = 0;
    for (auto &enemy : enemies_) {
        if (enemy)
            en_count++;
    }
    file << en_count << std::endl;
    for (auto &enemy : enemies_) {
        if (enemy)
            enemy->Save(file);
    }
}

void Game::Load(std::ifstream &file) {
    map_ = Map::Load(file);
    player_ = Player::Load(file);


    if (player_->GetCoord().first < 0 || player_->GetCoord().second < 0 ||
        player_->GetCoord().first >= map_->GetSize().first || player_->GetCoord().second >= map_->GetSize().second)
        throw std::runtime_error("Invalid player position");

    if (!map_->GetCell(player_->GetCoord())->Pass())
        throw std::runtime_error("Invalid player position");

    enemies_.clear();
    int enemies_count;
    file >> enemies_count;
    for (int i = 0; i < enemies_count; ++i) {

        auto en = BaseEnemy::Load(file);

        if (en->GetCoord().first < 0 || en->GetCoord().second < 0 ||
            en->GetCoord().first >= map_->GetSize().first || en->GetCoord().second >= map_->GetSize().second)
            throw std::runtime_error("Invalid Bot position");

        if (!map_->GetCell(en->GetCoord())->Pass())
            throw std::runtime_error("Invalid player position");

        enemies_.push_back(en);
    }
    SetLogger(logger_);
}

void Game::Draw() {
    framebuffer_->Clear();
    map_->Draw(framebuffer_);
    player_->Draw(framebuffer_);
    for (auto &enemy : enemies_) {
        if (enemy) {
            enemy->Draw(framebuffer_);
        }
    }
    framebuffer_->Present();
}

void Game::SetLogger(const std::shared_ptr<ILogger> &logger) {
    Loggable::SetLogger(logger);
    if (map_) { map_->SetLogger(logger_); }
    if (player_) { player_->SetLogger(logger_); }
}

