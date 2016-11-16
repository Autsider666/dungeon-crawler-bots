//
// Created by Yorick on 16/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_INPUTSYSTEM_H
#define DUNGEONCRAWLERBOTS_INPUTSYSTEM_H


#include "../external/rltk/rltk/ecs.hpp"

struct InputSystem : public rltk::base_system {
    void configure();

    void update(const double duration_ms);
};

#endif //DUNGEONCRAWLERBOTS_INPUTSYSTEM_H
