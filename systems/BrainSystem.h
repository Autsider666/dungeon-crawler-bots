//
// Created by Yorick on 12/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_BRAINSYSTEM_H
#define DUNGEONCRAWLERBOTS_BRAINSYSTEM_H


#include "../external/rltk/rltk/ecs.hpp"

struct BrainSystem : public rltk::base_system{
    void configure ();
    void update(const double duration_ms);
};


#endif //DUNGEONCRAWLERBOTS_BRAINSYSTEM_H
