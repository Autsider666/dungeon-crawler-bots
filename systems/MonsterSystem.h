//
// Created by Yorick on 16/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_OUTPUTPROCESSINGSYSTEM_H
#define DUNGEONCRAWLERBOTS_OUTPUTPROCESSINGSYSTEM_H

#include "../external/rltk/rltk/ecs.hpp"

struct MonsterSystem : rltk::base_system {
    void configure ();
    void update(const double duration_ms);
};


#endif //DUNGEONCRAWLERBOTS_OUTPUTPROCESSINGSYSTEM_H
