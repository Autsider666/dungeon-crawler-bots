#include <sstream>
#include <iomanip>
#include "external/rltk/rltk/rltk.hpp"
#include "components/Brain_c.h"
#include "World.h"
#include "Game.h"
#include "components/Agent_c.h"
#include "components/Position_c.h"
#include "settings.h"
#include "rng.h"
#include "components/Renderable_c.h"

// For convenience, import the whole rltk namespace. You may not want to do this
// in larger projects, to avoid naming collisions.
using namespace rltk;
using namespace rltk::colors;

// For convenience, we'll define our GUI section handles here. These are just ID numbers.

// Tick is called every frame. The parameter specifies how many ms have elapsed
// since the last time it was called.
void tick(double duration_ms) {
    Game *game = Game::getInstance();
    World *world = game->getWorld();

    for (int x = 0; x < world->getWidth(); ++x) {
        for (int y = 0; y < world->getHeight(); ++y) {
            switch (world->getTileAt(x, y)) {
                case 1:
                    term(0)->set_char(world->at(x, y), vchar{'#', GREY, BLACK});
                    break;
                default:
                    term(0)->set_char(world->at(x, y), vchar{'.', GREY, BLACK});
                    break;
            }
        }
    }

    auto targetPosition = entity(Game::getInstance()->getTargetId())->component<Position_c>();
    term(0)->set_char(targetPosition->x, targetPosition->y, vchar{'@', YELLOW, BLACK});
    int i = 0;
    vector<size_t> lucky;
    rltk::each<Agent_c, Brain_c, Position_c>(
            [&i, &lucky](rltk::entity_t &e, Agent_c &agent, Brain_c &brain, Position_c &agentPosition) {
                auto targetPosition = entity(Game::getInstance()->getTargetId())->component<Position_c>();

                float x = targetPosition->x - agentPosition.x;
                float y = targetPosition->y - agentPosition.y;

                float sx = tanh(x);
                float sy = tanh(y);

                float distance = std::sqrt(x * x + y * y);
                if (distance > 10) {
                    x = 0;
                    y = 0;
                }

                std::vector<float> input = {x, y, distance, sx, sy, abs(sin(clock() / agent.clock1)), abs(sin(clock() / agent.clock1))};
                brain.tick(input);

                if (brain.output[0] <= 0.4 && agentPosition.x > 0) {
                    agentPosition.x -= 1;
                } else if (brain.output[0] >= 0.6 && agentPosition.x < settings::SimulationWidth - 1) {
                    agentPosition.x += 1;
                }

                if (brain.output[1] <= 0.4 && agentPosition.y > 0) {
                    agentPosition.y -= 1;
                } else if (brain.output[1] >= 0.6 && agentPosition.y < settings::SimulationHeight - 1) {
                    agentPosition.y += 1;
                }

                term(0)->set_char(agentPosition.x, agentPosition.y, vchar{'M', color_t{round(brain.output[2] * 255),
                                                                                       round(brain.output[3] * 255),
                                                                                       round(brain.output[4] *
                                                                                             255)}, BLACK});
                if (targetPosition->x == agentPosition.x && targetPosition->y == agentPosition.y) {
                    Game::getInstance()->targetFound();
                    agent.health += 1;
                    lucky.push_back(e.id);
                } else {
                    agent.health -= 0.005;
                    if (agent.health <= 0) {
                        Game::getInstance()->removeEntity(e.id);
                        i--;
                    }
                }
                i++;
            });

    if (game->isTargetFound()) {
        game->setNewTarget();
    }

    for (size_t id : lucky) {
        for (int k = 0; k < settings::Babies; ++k) {
            if (i < settings::MaximumBots) {
                auto parent = entity(id);
                create_entity()
                        ->assign(parent->component<Agent_c>()->reproduce())
                        ->assign(parent->component<Brain_c>()->reproduce())
                        ->assign(Position_c{parent->component<Position_c>()->x, parent->component<Position_c>()->y});
                i++;
            }
        }
    }

    if (i == 0) {
        while (i < settings::MinimumBots) {
            create_entity()
                    ->assign(Agent_c{})
                    ->assign(Brain_c{})
                    ->assign(Position_c{settings::SimulationWidth / 2, settings::SimulationHeight / 2});
            i++;
        }
    }



//    term(0)->clear(vchar{'.', GREY, BLACK});
//    term(0)->box(GREY, BLACK, true);
    term(1)->clear(vchar{' ', WHITE, DARKEST_GREEN});
    term(1)->box(DARKEST_GREEN, BLACK);
    term(1)->print(1, 1, "Agents: " + std::to_string(i), LIGHT_GREEN, DARKEST_GREEN);

    auto targetPos = entity(Game::getInstance()->getTargetId())->component<Position_c>();

    term(1)->print(1, 2, "Target: " + std::to_string(targetPos->x) + "/" + std::to_string(targetPos->y), LIGHT_GREEN,
                   DARKEST_GREEN);
    term(1)->print(1, 3, "Even more...", LIGHT_GREEN, DARKEST_GREEN);
    term(1)->print(1, 4, "... goes here", LIGHT_GREEN, DARKEST_GREEN);

    std::stringstream ss;
    ss << std::setiosflags(std::ios::fixed) << std::setprecision(0) << (1000.0 / duration_ms) << " FPS";
    term(1)->print(1, 6, ss.str(), WHITE, DARKEST_GREEN);
}

void resize_main(layer_t *l, int w, int h) {
    l->w = w - 160;
    l->h = h;
    if (l->w < 0) l->w = 160; // If the width is too small with the log window, display anyway.
}

void resize_log(layer_t *l, int w, int h) {
    l->w = w - 160;
    l->h = h;

    if (l->w < 0) {
        l->console->visible = false;
    } else {
        l->console->visible = true;
    }
    l->x = w - 160;
}

// Your main function
int main() {
    World *world = new World();
    Game::getInstance()->setWorld(world);


//    clock_t start_time = clock();
//    rltk::each<Agent_c,Brain_c>([] (rltk::entity_t &entity, Agent_c &agent, Brain_c &brain) {
//        std::cout << "----------" << std::endl;
//        std::cout << "Agent " << entity.id << std::endl;
//        for (int i = 0; i < 100; ++i) {
//            std::vector<float> input = {1.0f*i,2,3,4};
//            brain.tick(input);
//            std::cout << "Tick " << i+1 << std::endl;
//            for (float outputField: brain.output){
//                std::cout <<outputField << std::endl;
//            }
//        }
//    });
//    std::cout << "Duration: " << (clock() - start_time) << std::endl;

    init(config_advanced("assets/fonts"));

    gui->add_layer(0, 0, 0, 1024 - 160, 768, "16x16", resize_main);
    gui->add_layer(1, 864, 0, 160, 768, "8x16", resize_log);

    run(tick);

    return 0;
}
