#include <sstream>
#include <iomanip>
#include "external/rltk/rltk/rltk.hpp"
#include "World.h"
#include "Simulation.h"
#include "systems/WorldRenderSystem.h"
#include "systems/EntityRenderSystem.h"
#include "systems/PlayerSystem.h"
#include "systems/MonsterSystem.h"
#include "systems/MonsterSensorSystem.h"
#include "systems/InputSystem.h"
#include "systems/SoundSystem.h"
#include "systems/HeatSystem.h"
#include "settings.h"

using namespace rltk;
using namespace rltk::colors;

void tick(double duration_ms) {
    ecs_tick(duration_ms);

//    term(0)->clear(vchar{'.', GREY, BLACK});
//    term(0)->box(GREY, BLACK, true);
    term(0)->clear(vchar{' ', WHITE, DARKEST_GREEN});
    term(0)->box(DARKEST_GREEN, BLACK);
    std::string mode;
    switch (Simulation::getInstance()->getRenderMode()) {
        case Vision::Heat:
            mode = "Infrared";
            break;
        case Vision::Sound:
            mode = "Echolocation";
            break;
        default:
            mode = "Default";
            break;
    }
    term(0)->print(1, 1, mode + " mode", LIGHT_GREEN, DARKEST_GREEN);

//    auto targetPos = entity(Simulation::getInstance()->getTargetId())->component<Position_c>();
//
//    term(0)->print(1, 2, "Target: " + std::to_string((int) round(targetPos->x)) + "/" +
//                         std::to_string((int) round(targetPos->y)),
//                   LIGHT_GREEN,
//                   DARKEST_GREEN);
//
//    term(0)->print(1, 3, "Average age: " + std::to_string(totalAge / amountBots), LIGHT_GREEN,
//                   DARKEST_GREEN);
//
//    if (entity(ancientOne) != boost::none) {
//        auto ancient = entity(ancientOne)->component<Monster_c>();
//
//        term(0)->print(1, 4, "The elder: " + std::to_string(ancientOne),
//                       LIGHT_GREEN, DARKEST_GREEN);
//        term(0)->print(1, 5, "Age: " + std::to_string(ancient->age),
//                       LIGHT_GREEN, DARKEST_GREEN);
//    }
    std::stringstream ss;
    ss << std::setiosflags(std::ios::fixed) << std::setprecision(0) << (1000.0 / duration_ms) << " FPS";
    term(0)->print(1, 6, ss.str(), WHITE, DARKEST_GREEN);
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

int main() {
    World *world = new World();
    Simulation::getInstance()->setWorld(world);

    init(config_advanced("assets/fonts", 1024, 768, "SkynetRL"));

    gui->add_layer(0, 864, 0, 160, 768, "8x16", resize_log);
    gui->add_layer(1, 0, 0, 1024 - 160, 768, "16x16", resize_main);
    gui->add_sparse_layer(2, 0, 0, 1024 - 160, 768, "16x16", resize_main);

    get_window()->setVerticalSyncEnabled(false);

    add_system<HeatSystem>();
    add_system<SoundSystem>();
    add_system<MonsterSensorSystem>();
    add_system<PlayerSystem>();
    add_system<MonsterSystem>();
    add_system<WorldRenderSystem>();
    add_system<EntityRenderSystem>();
    add_system<InputSystem>();

    ecs_configure();
    try {
        run(tick);
    } catch (std::exception &e) {
        std::cout << "Exception encountered: " << e.what() << std::endl;
        int x = 4;
        x = 2;
    }

    return 0;
}
