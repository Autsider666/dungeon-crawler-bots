//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_GAME_H
#define SOLOMON_GAME_H

#include <string>
#include "World.h"
#include "external/rltk/rltk/ecs.hpp"

class Game {
    Game();

    static Game *instance;

    int windowHeight;
    int windowWidth;
    std::string gameFont;
    bool fullscreen;
    World *world;

    size_t targetId;
    bool found;

public:
    static Game *getInstance();

    size_t getTargetId() { return targetId; };

    int getWindowHeight() const {
        return windowHeight;
    }

    void setWindowHeight(int windowHeight) {
        Game::windowHeight = windowHeight;
    }

    int getWindowWidth() const {
        return windowWidth;
    }

    void setWindowWidth(int windowWidth) {
        Game::windowWidth = windowWidth;
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
        return world;
    }

    void setWorld(World *world) {
        Game::world = world;
    }

    void targetFound() { found = true; };

    bool isTargetFound() { return found; }

    void setNewTarget();

    void removeEntity(size_t id);
};


#endif //SOLOMON_GAME_H
