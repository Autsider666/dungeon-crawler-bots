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

void MonsterSystem::configure() {
    system_name = "Monster System";
}

void MonsterSystem::update(const double duration_ms) {
    Simulation::getInstance()->getWorld()->resetSoundMap();
    int amountBots = 0;
    size_t ancientOne = 0;
    std::vector<size_t> luckyFew;
    int totalAge = 0;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    rltk::each<Monster_c, Brain_c, Position_c, Renderable_c>(
            [&t1, &amountBots, &luckyFew, &ancientOne, &totalAge](rltk::entity_t &e, Monster_c &monster, Brain_c &brain,
                                                                  Position_c &monsterpos, Renderable_c &render) { ;
                boost::optional<rltk::entity_t &> target;
                float distance = -1;
                rltk::each<Player_c, Position_c>(
                        [&monster, &luckyFew, &e, &monsterpos, &target, &distance](rltk::entity_t &entity,
                                                                                   Player_c &player,
                                                                                   Position_c &playerPos) {
                            float x = playerPos.x - monsterpos.x;
                            float y = playerPos.y - monsterpos.y;
                            float d = std::sqrt(x * x + y * y);
                            if (distance == -1 || d < distance) {
                                distance = d;
                                target = entity;
                            }
                            if (d < 1.5) {
                                rltk::emit(PlayerAttackedMessage{e, entity});
                                monster.health = 1;
                                luckyFew.push_back(e.id);
                            }
                        });


                monster.age++;
                totalAge += monster.age;
                if (rltk::entity(ancientOne) == boost::none ||
                    monster.age > rltk::entity(ancientOne)->component<Monster_c>()->age) {
                    ancientOne = e.id;
                }

                float dx = 0;
                float dy = 0;

                if (brain.output[0] < 0.45) {
                    dx -= 1 - brain.output[0];
                } else if (brain.output[0] > 0.55) {
                    dx += brain.output[0];
                }

                if (brain.output[1] < 0.45) {
                    dy -= 1 - brain.output[1];
                } else if (brain.output[1] > 0.55) {
                    dy += brain.output[1];
                }

                float dd = std::sqrt(dx * dx + dy * dy);

                if (dd > 1) {
                    dx = dx / dd;
                    dy = dy / dd;
                    monster.speed = 1;
                } else {
                    monster.speed = dd;
                }

                if (Simulation::getInstance()->getWorld()->isWalkableAt(round(monsterpos.x + dx),
                                                                        round(monsterpos.y + dy))) {

                    monsterpos.x += dx;
                    monsterpos.y += dy;
                } else {
                    while (Simulation::getInstance()->getWorld()->isWalkableAt(round(monsterpos.x + dx),
                                                                               round(monsterpos.y + dy))) {
                        if (dx > 0) {
                            dx -= 0.1;
                        } else if (dx < 0) {
                            dx += 0.1;
                        }

                        if (dy > 0) {
                            dy -= 0.1;
                        } else if (dy < 0) {
                            dy += 0.1;
                        }
                    }
                }

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

                render.fg = rltk::color_t{round(10 + brain.output[2] * 245),
                                          round(10 + brain.output[3] * 245),
                                          round(10 + brain.output[4] *
                                                     245)};

                monster.health -= 0.005 * ((monster.age / 200) + 1);

                if (monster.health <= 0) {
                    rltk::delete_entity(e);
                } else {
                    World *w = Simulation::getInstance()->getWorld();
                    float distanceMax = Settings::BasicSoundRange * monster.speed;
                    for (int x = 0; x < Settings::SimulationWidth; ++x) {
                        for (int y = 0; y < Settings::SimulationHeight; ++y) {
                            float dx = x - monsterpos.x;
                            float dy = y - monsterpos.y;
                            float strength = distanceMax - std::sqrt(dx * dx + dy * dy);
                            if (strength > 0 && w->getSoundAt(x, y) < strength && w->isWalkableAt(x, y)) {
                                w->setSoundAt(x, y, strength);
                            }
                        }
                    }
                    amountBots++;
                }
            });

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "-----------------" << std::endl << "After loop: " << duration << std::endl;

    if (amountBots > 0) {
        std::cout << "Avg time / monster: " << duration / amountBots << std::endl;
    }

    for (size_t id : luckyFew) {
        for (int k = 0; k < Settings::Babies; ++k) {
            if (amountBots < Settings::MaximumMonsters) {
                auto parent = rltk::entity(id);
                float x = parent->component<Position_c>()->x + rng::getRandomIntBetween(-5, 5);
                float y = parent->component<Position_c>()->y + rng::getRandomIntBetween(-5, 5);
                if (Simulation::getInstance()->getWorld()->isWalkableAt(round(x), round(y))) {
                    rltk::create_entity()
                            ->assign(parent->component<Monster_c>()->reproduce())
                            ->assign(parent->component<Brain_c>()->reproduce())
                            ->assign(Position_c{x, y})
                            ->assign(Renderable_c{'W', rltk::colors::WHITE});
                    amountBots++;
                }
            }
        }
    }


    std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();

    std::cout << "After Kids: " << duration << std::endl;

    if (amountBots == 0) {
        while (amountBots < Settings::MinimumMonsters) {
            float x = rng::getRandomFloatBetween(0, Settings::SimulationWidth - 1);
            float y = rng::getRandomFloatBetween(0, Settings::SimulationHeight - 1);
            if (Simulation::getInstance()->getWorld()->isWalkableAt(round(x), round(y))) {
                rltk::create_entity()
                        ->assign(Monster_c{})
                        ->assign(Brain_c{})
                        ->assign(Position_c{x, y})
                        ->assign(Renderable_c{'W', rltk::colors::WHITE});
                amountBots++;
            }
        }
    }

    std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "After reset:" << duration << std::endl;


    duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t1).count();

    std::cout << "Total Time:" << duration << std::endl;
    std::cout << "Amount Monsters: " << amountBots << std::endl;
}
