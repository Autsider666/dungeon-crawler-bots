//
// Created by Yorick on 19/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_HEATSYSTEM_H
#define DUNGEONCRAWLERBOTS_HEATSYSTEM_H

#include "../external/rltk/rltk/ecs.hpp"

class HeatSystem  : public rltk::base_system {
    void configure();

    void update(const double duration_ms);
};

#endif //DUNGEONCRAWLERBOTS_HEATSYSTEM_H
