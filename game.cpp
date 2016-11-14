//
// Created by Yorick on 10/11/2016.
//

#include "Game.h"
#include "settings.h"
#include "components/Agent_c.h"
#include "components/Brain_c.h"
#include "components/Position_c.h"
#include "components/Renderable_c.h"
#include "rng.h"

Game *Game::instance = nullptr;

Game::Game() {
    windowHeight = 768;
    windowWidth = 1024;
    fullscreen = true;
    gameFont = "16x16";
    world = nullptr;
    found = false;

    for (int i = 0; i < settings::StartingBots; ++i) {
        rltk::create_entity()
                ->assign(Agent_c{})
                ->assign(Brain_c{})
                ->assign(Position_c{settings::SimulationWidth / 2, settings::SimulationHeight / 2});
    }
    auto target = rltk::create_entity()
            ->assign(Position_c{rng::getRandomIntBetween(0, settings::SimulationWidth-1),
                                rng::getRandomIntBetween(0, settings::SimulationHeight-1)})
            ->assign(Renderable_c{'@', rltk::colors::YELLOW});
    targetId = target->id;
    std::cout << target->component<Position_c>()->x << std::endl;
    std::cout << target->component<Position_c>()->y << std::endl;
}

Game *Game::getInstance() {
    if (!instance) {
        instance = new Game();
    }
    return instance;
}

void Game::setNewTarget() {
    auto targetPosition = rltk::entity(targetId)->component<Position_c>();
    targetPosition->x = rng::getRandomIntBetween(0, settings::SimulationWidth-1);
    targetPosition->y = rng::getRandomIntBetween(0, settings::SimulationHeight-1);
    found = false;
}

void Game::removeEntity(size_t id) {
    rltk::delete_entity(id);
}
