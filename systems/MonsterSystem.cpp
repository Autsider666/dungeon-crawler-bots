//
// Created by Yorick on 16/11/2016.
//

#include <vector>
#include <cmath>
#include <math.h>
#include "MonsterSystem.h"
#include "../components/Brain_c.h"
#include "../components/Position_c.h"
#include "../settings.h"
#include "../components/Renderable_c.h"
#include "../rng.h"
#include "../messages/PlayerAttackedMessage.h"
#include "../components/Player_c.h"
#include "../components/Monster_c.h"
#include "../World.h"
#include "../Simulation.h"
#include "../components/SoundSource_c.h"

void MonsterSystem::configure() {
    system_name = "Monster System";
}

void MonsterSystem::update(const double duration_ms) {
    int amountBots = 0;
    std::vector<size_t> luckyFew;

//    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    rltk::each<Monster_c, Brain_c, Position_c, Renderable_c, SoundSource_c>(
            [&amountBots, &luckyFew](rltk::entity_t &e, Monster_c &monster,
                                     Brain_c &brain,
                                     Position_c &monsterpos,
                                     Renderable_c &render,
                                     SoundSource_c &sound) {
//                std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
////
//                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t0 - t1).count();
//
//                std::cout << "+++++++++++" << std::endl << "Time since start of loop: " << duration << std::endl;
                rltk::each<Player_c, Position_c>(
                        [&monster, &luckyFew, &e, &monsterpos](rltk::entity_t &entity,
                                                               Player_c &player,
                                                               Position_c &playerPos) {
                            int x = playerPos.x - monsterpos.x;
                            int y = playerPos.y - monsterpos.y;
//                            double d = std::sqrt(x * x + y * y);
                            if (abs(x) <= 1 && abs(y) <= 1) {
//                            if (playerPos == monsterpos) {
                                rltk::emit(PlayerAttackedMessage{e, entity});
                                monster.health = 1;
                                luckyFew.push_back(e.id);
                            }
                        });

                render.fg = rltk::color_t{round(10 + brain.output[0] * 245),
                                          round(10 + brain.output[1] * 245),
                                          round(10 + brain.output[2] *
                                                     245)};

//                std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//
//                duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t0).count();
//
//                std::cout << "After checking if killed: " << duration << std::endl;

                int dx = 0;
                int dy = 0;

                if (brain.output[3] > brain.output[4] && brain.output[3] >= 0.5) {
                    dy += 1;
                } else if (brain.output[4] > brain.output[3] && brain.output[4] >= 0.5) {
                    dy -= 1;
                }

                if (brain.output[5] > brain.output[6] && brain.output[5] >= 0.5) {
                    dx -= 1;
                } else if (brain.output[6] > brain.output[5] && brain.output[6] >= 0.5) {
                    dx += 1;
                }

                if ((dx != dy || (dx != 0 && dy != 0)) &&
                    Simulation::getInstance()->getWorld()->isWalkableAt(monsterpos.x + dx, monsterpos.y + dy)) {
                    monster.inactivity = 0;
                    monsterpos.x += dx;
                    monsterpos.y += dy;

                    if (monsterpos.x < 0) {
                        monsterpos.x = 0;
                    }
                    if (monsterpos.y < 0) {
                        monsterpos.y = 0;
                    }
                    if (monsterpos.x > Settings::SimulationWidth - 1) {
                        monsterpos.x = Settings::SimulationWidth - 1;
                    }
                    if (monsterpos.y > Settings::SimulationHeight - 1) {
                        monsterpos.y = Settings::SimulationHeight - 1;
                    }
                } else {
                    ++monster.inactivity;
                }
//                monster.age++;
//
//                float dx = 0;
//                float dy = 0;
//
//                if (brain.output[0] < 0.45) {
//                    dx -= 1 - brain.output[0];
//                } else if (brain.output[0] > 0.55) {
//                    dx += brain.output[0];
//                }
//
//                if (brain.output[1] < 0.45) {
//                    dy -= 1 - brain.output[1];
//                } else if (brain.output[1] > 0.55) {
//                    dy += brain.output[1];
//                }
//
//                float dd = std::sqrt(dx * dx + dy * dy);
//
//                if (dd > 1) {
//                    dx = dx / dd;
//                    dy = dy / dd;
//                    monster.speed = 1;
//                } else {
//                    monster.speed = dd;
//                }
//
//                sound.strength = Settings::BasicSoundRange * monster.speed;
//
//                if (Simulation::getInstance()->getWorld()->isWalkableAt(round(monsterpos.x + dx),
//                                                                        round(monsterpos.y + dy))) {
//
//                    monsterpos.x += dx;
//                    monsterpos.y += dy;
//                } else {
//                    while (Simulation::getInstance()->getWorld()->isWalkableAt(round(monsterpos.x + dx),
//                                                                               round(monsterpos.y + dy))) {
//                        if (dx > 0) {
//                            dx -= 0.1;
//                        } else if (dx < 0) {
//                            dx += 0.1;
//                        }
//
//                        if (dy > 0) {
//                            dy -= 0.1;
//                        } else if (dy < 0) {
//                            dy += 0.1;
//                        }
//                    }
//                }
//
//                if (monsterpos.x < 0) {
//                    monsterpos.x = 0;
//                }
//                if (monsterpos.y < 0) {
//                    monsterpos.y = 0;
//                }
//                if (monsterpos.x > Settings::SimulationWidth - 1) {
//                    monsterpos.x = Settings::SimulationWidth - 1;
//                }
//                if (monsterpos.y > Settings::SimulationHeight - 1) {
//                    monsterpos.y = Settings::SimulationHeight - 1;
//                }

//                std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
//
//                duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
//
//                std::cout << "After walking: " << duration << std::endl;

                if (dx == 0 || dy == 0) {
                    monster.health -= 0.005 * ((monster.age / 200) + 1);
                } else {
                    monster.health -= 0.007 * ((monster.age / 200) + 1);
                }

                if (monster.health <= 0 || monster.inactivity >= 10) {
                    rltk::delete_entity(e);
                } else {
                    amountBots++;
                }

//                std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
//
//                duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
//
//                std::cout << "At the end of the loop as we know it: " << duration << std::endl;
            });

//    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
//
//    std::cout << "-----------------" << std::endl << "After loop: " << duration << std::endl;
//
//    if (amountBots > 0) {
//        std::cout << "Avg time / monster: " << duration / amountBots << std::endl;
//    }

    for (size_t id : luckyFew) {
        for (int k = 0; k < Settings::Babies; ++k) {
            if (amountBots < Settings::MaximumMonsters) {
                auto parent = rltk::entity(id);
                int x = parent->component<Position_c>()->x + rng::getRandomIntBetween(-5, 5);
                int y = parent->component<Position_c>()->y + rng::getRandomIntBetween(-5, 5);
                if (Simulation::getInstance()->getWorld()->isWalkableAt(x, y)) {
                    rltk::create_entity()
                            ->assign(parent->component<Monster_c>()->reproduce())
                            ->assign(parent->component<Brain_c>()->reproduce())
                            ->assign(Position_c{x, y})
                            ->assign(SoundSource_c{Settings::BasicSoundRange})
                            ->assign(Renderable_c{'W', rltk::colors::WHITE});
                    amountBots++;
                }
            }
        }
    }

//    if (amountBots == 0) {
    while (amountBots < Settings::MinimumMonsters) {
        int x = rng::getRandomIntBetween(0, Settings::SimulationWidth - 1);
        int y = rng::getRandomIntBetween(0, Settings::SimulationHeight - 1);
        if (Simulation::getInstance()->getWorld()->isWalkableAt(x, y)) {
            rltk::create_entity()
                    ->assign(Monster_c{})
                    ->assign(Brain_c{})
                    ->assign(Position_c{x, y})
                    ->assign(SoundSource_c{Settings::BasicSoundRange})
                    ->assign(Renderable_c{'W', rltk::colors::WHITE});
            amountBots++;
        }
    }
//    }

    if (amountBots > 18) {
        int y = 2;
    }
}