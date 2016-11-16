//
// Created by Yorick on 16/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_PLAYERSYSTEM_H
#define DUNGEONCRAWLERBOTS_PLAYERSYSTEM_H


#include "../external/rltk/rltk/ecs.hpp"

struct PlayerSystem : public rltk::base_system {
    void configure ();
    void update(const double duration_ms);
};


#endif //DUNGEONCRAWLERBOTS_PLAYERSYSTEM_H
