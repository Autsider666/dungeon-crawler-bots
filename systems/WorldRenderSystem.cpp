//
// Created by Yorick on 16/11/2016.
//

#include "WorldRenderSystem.h"
#include "../World.h"
#include "../external/rltk/rltk/colors.hpp"
#include "../external/rltk/rltk/rltk.hpp"
#include "../Simulation.h"
#include "../settings.h"

using namespace rltk;
using namespace rltk::colors;

void WorldRenderSystem::configure() {
    system_name = "World Render System";
}

void WorldRenderSystem::update(const double duration_ms) {
    Simulation *sim = Simulation::getInstance();
    World *world = sim->getWorld();

    term(1)->clear();
    for (int x = 0; x < world->getWidth(); ++x) {
        for (int y = 0; y < world->getHeight(); ++y) {
            switch (world->getTileAt(x, y)) {
                case 1:
                    term(1)->set_char(world->at(x, y), vchar{'#', GREY, BLACK});
                    break;
                default:
                    switch (Simulation::getInstance()->getRenderMode()) {
                        case Vision::MonsterSound:
                            term(1)->set_char(world->at(x, y), vchar{' ', BLACK, lerp(BLACK, WHITE,
                                                                                      Simulation::getInstance()->getWorld()->getMonsterSoundAt(
                                                                                              x, y) / 20.0)});
                            break;
                        case Vision::PlayerSound:
                            term(1)->set_char(world->at(x, y), vchar{' ', BLACK, lerp(BLACK, WHITE,
                                                                                      Simulation::getInstance()->getWorld()->getPlayerSoundAt(
                                                                                              x, y) / 20.0)});
                            break;
                        default:
                            term(1)->set_char(world->at(x, y), vchar{' ', GREY, BLACK});
                            break;
                    }
            }
        }
    }
}
