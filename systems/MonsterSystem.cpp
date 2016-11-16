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

void MonsterSystem::configure() {
    system_name = "Agent System";
}

void MonsterSystem::update(const double duration_ms) {
    int amountBots = 0;
    size_t ancientOne = 0;
    std::vector<size_t> luckyFew;
    int totalAge = 0;
    rltk::each<Monster_c, Brain_c, Position_c, Renderable_c>(
            [&amountBots, &luckyFew, &ancientOne, &totalAge](rltk::entity_t &e, Monster_c &agent, Brain_c &brain,
                                                             Position_c &monsterpos, Renderable_c &render) {;
                boost::optional<rltk::entity_t &> target;
                float distance = -1;
                rltk::each<Player_c, Position_c>(
                        [&monsterpos, &target, &distance](rltk::entity_t &entity, Player_c &player,
                                                          Position_c &playerPos) {
                            float x = playerPos.x - monsterpos.x;
                            float y = playerPos.y - monsterpos.y;
                            float d = std::sqrt(x * x + y * y);
                            if (distance == -1 || d < distance) {
                                distance = d;
                                target = entity;
                            }
                        });


                agent.age++;
                totalAge += agent.age;
                if (rltk::entity(ancientOne) == boost::none ||
                    agent.age > rltk::entity(ancientOne)->component<Monster_c>()->age) {
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

                if (dx != 0 && dy != 0) {
                    float dd = std::sqrt(dx * dx + dy * dy);

                    dx = dx / dd;
                    dy = dy / dd;

                    monsterpos.x += dx;
                    monsterpos.y += dy;

                    if (monsterpos.x < 0) {
                        monsterpos.x = 0;
                    }
                    if (monsterpos.y < 0) {
                        monsterpos.y = 0;
                    }
                    if (monsterpos.x > settings::SimulationWidth - 1) {
                        monsterpos.x = settings::SimulationWidth - 1;
                    }
                    if (monsterpos.y > settings::SimulationHeight - 1) {
                        monsterpos.y = settings::SimulationHeight - 1;
                    }
                }

                render.fg = rltk::color_t{round(10 + brain.output[2] * 245),
                                          round(10 + brain.output[3] * 245),
                                          round(10 + brain.output[4] *
                                                     245)};

                agent.health -= 0.005 * ((agent.age / 200) + 1);

                rltk::each<Player_c, Position_c>(
                        [&monsterpos, &e, &agent, &luckyFew](rltk::entity_t &entity, Player_c &player,
                                                             Position_c &playerPos) {
                            float x = playerPos.x - monsterpos.x;
                            float y = playerPos.y - monsterpos.y;
                            float d = std::sqrt(x * x + y * y);
                            if (d < 1.5) {
                                rltk::emit(PlayerAttackedMessage{e, entity});
                                agent.health = 1;
                                luckyFew.push_back(e.id);
                            }
                        });

                if (agent.health <= 0) {
                    rltk::delete_entity(e);
                } else {
                    amountBots++;
                }
            });

    for (size_t id : luckyFew) {
        for (int k = 0; k < settings::Babies; ++k) {
            if (amountBots < settings::MaximumBots) {
                auto parent = rltk::entity(id);
                rltk::create_entity()
                        ->assign(parent->component<Monster_c>()->reproduce())
                        ->assign(parent->component<Brain_c>()->reproduce())
                        ->assign(Position_c{parent->component<Position_c>()->x + rng::getRandomIntBetween(-5, 5),
                                            parent->component<Position_c>()->y + rng::getRandomIntBetween(-5, 5)})
                        ->assign(Renderable_c{'W', rltk::colors::WHITE});
                amountBots++;
            }
        }
    }

    if (amountBots == 0) {
        while (amountBots < settings::MinimumBots) {
            rltk::create_entity()
                    ->assign(Monster_c{})
                    ->assign(Brain_c{})
//                    ->assign(Position_c{rng::getRandomFloatBetween(0, settings::SimulationWidth - 1),
//                                        rng::getRandomFloatBetween(0, settings::SimulationHeight - 1)})
                    ->assign(Position_c{settings::SimulationWidth / 2, settings::SimulationHeight / 2})
                    ->assign(Renderable_c{'W', rltk::colors::WHITE});
            amountBots++;
        }
    }
}
