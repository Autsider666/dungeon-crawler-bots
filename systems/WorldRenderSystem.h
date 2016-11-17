//
// Created by Yorick on 16/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_WORLDRENDERSYSTEM_H
#define DUNGEONCRAWLERBOTS_WORLDRENDERSYSTEM_H


#include "../external/rltk/rltk/ecs.hpp"

struct WorldRenderSystem : public rltk::base_system{
    void configure ();
    void update(const double duration_ms);
};


#endif //DUNGEONCRAWLERBOTS_WORLDRENDERSYSTEM_H
