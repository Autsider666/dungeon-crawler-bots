//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_GAME_H
#define SOLOMON_GAME_H

#include <string>
#include "external/rltk/rltk/ecs.hpp"
#include "World.h"

class Simulation {
    Simulation();

    static Simulation *instance;

    int windowHeight;
    int windowWidth;
    std::string gameFont;
    bool fullscreen;
    World *currentWorld;

    int renderMode;

public:
    static Simulation *getInstance();

    int getWindowHeight() const {
        return windowHeight;
    }

    void setWindowHeight(int windowHeight) {
        Simulation::windowHeight = windowHeight;
    }

    int getWindowWidth() const {
        return windowWidth;
    }

    void setWindowWidth(int windowWidth) {
        Simulation::windowWidth = windowWidth;
    }

    const std::string &getGameFont() const {
        return gameFont;
    }

    bool isFullscreen() const {
        return fullscreen;
    }

    void toggleFullscreen() {
        fullscreen = !fullscreen;
    }

    World *getWorld() const {
        return currentWorld;
    }

    void setWorld(World *world) {
        Simulation::currentWorld = world;
    }

    int getRenderMode() const { return renderMode; };

    void setRenderMode(int mode) {
        Simulation::renderMode = mode;
    }
};


#endif //SOLOMON_GAME_H
