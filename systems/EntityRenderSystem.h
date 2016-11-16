//
// Created by Yorick on 16/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_ENTITYRENDERSYSTEM_H
#define DUNGEONCRAWLERBOTS_ENTITYRENDERSYSTEM_H

#include "../external/rltk/rltk/ecs.hpp"

struct EntityRenderSystem : public rltk::base_system {
    void configure();

    void update(const double duration_ms);
};


#endif //DUNGEONCRAWLERBOTS_ENTITYRENDERSYSTEM_H
