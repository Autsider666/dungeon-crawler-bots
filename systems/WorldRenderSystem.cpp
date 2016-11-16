//
// Created by Yorick on 16/11/2016.
//

#include "WorldRenderSystem.h"
#include "../World.h"
#include "../Game.h"
#include "../external/rltk/rltk/colors.hpp"
#include "../external/rltk/rltk/rltk.hpp"

using namespace rltk;
using namespace rltk::colors;

void WorldRenderSystem::configure() {
    system_name = "World Render System";
}

void WorldRenderSystem::update(const double duration_ms) {
    Game *game = Game::getInstance();
    World *world = game->getWorld();

    if (!rendered) {
        term(1)->clear();
        for (int x = 0; x < world->getWidth(); ++x) {
            for (int y = 0; y < world->getHeight(); ++y) {
                switch (world->getTileAt(x, y)) {
                    case 1:
                        term(1)->set_char(world->at(x, y), vchar{'#', GREY, BLACK});
                        break;
                    default:
                        term(1)->set_char(world->at(x, y), vchar{' ', GREY, BLACK});
                        break;
                }
            }
        }
    }
}
