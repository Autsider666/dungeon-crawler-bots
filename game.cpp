//
// Created by Yorick on 10/11/2016.
//

#include "Game.h"

Game *Game::instance = nullptr;

Game::Game() {
    windowHeight = 768;
    windowWidth = 1024;
    fullscreen = true;
    gameFont = "16x16";
    world = nullptr;
}

Game *Game::getInstance() {
    if (!instance) {
        instance = new Game();
    }
    return instance;
}
