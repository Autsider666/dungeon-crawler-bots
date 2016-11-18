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
            switch (Simulation::getInstance()->getRenderMode()) {
                case Vision::MonsterSound:
                    switch (world->getTileAt(x, y)) {
                        case 1:
                            term(1)->set_char(world->at(x, y), vchar{' ', GREY, BLACK});
                            break;
                        default:
                            term(1)->set_char(world->at(x, y), vchar{' ', BLACK, lerp(BLACK, MidnightBlue,
                                                                                      Simulation::getInstance()->getWorld()->getSoundAt(
                                                                                              x, y) /
                                                                                      Settings::BasicSoundRange)});
                    }
                    break;
                case Vision::PlayerSound:
                    switch (world->getTileAt(x, y)) {
                        case 1:
                            term(1)->set_char(world->at(x, y), vchar{' ', GREY, BLACK});
                            break;
                        default:
                            term(1)->set_char(world->at(x, y), vchar{' ', BLACK, lerp(DarkBlue, RED,
                                                                                      Simulation::getInstance()->getWorld()->getHeatAt(
                                                                                              x, y) /
                                                                                      Settings::BasicHeatRange)});
                    }
                    break;
                default:
                    switch (world->getTileAt(x, y)) {
                        case 1:
                            term(1)->set_char(world->at(x, y), vchar{'#', GREY, BLACK});
                            break;
                        default:
                            term(1)->set_char(world->at(x, y), vchar{' ', GREY, BLACK});
                    }
                    break;
            }
        }
    }
}
