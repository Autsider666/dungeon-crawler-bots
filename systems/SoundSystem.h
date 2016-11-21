//
// Created by Yorick on 19/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_SOUNDSYSTEM_H
#define DUNGEONCRAWLERBOTS_SOUNDSYSTEM_H

#include "../external/rltk/rltk/ecs.hpp"

class SoundSystem  : public rltk::base_system {
    void configure();

    void update(const double duration_ms);
};

#endif //DUNGEONCRAWLERBOTS_SOUNDSYSTEM_H
