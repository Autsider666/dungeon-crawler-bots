//
// Created by Yorick on 10/11/2016.
//

#include "Simulation.h"

Simulation *Simulation::instance = nullptr;

Simulation::Simulation() {
    windowHeight = 768;
    windowWidth = 1024;
    fullscreen = true;
    gameFont = "16x16";
    currentWorld = nullptr;
    renderMode = 0;
}

Simulation *Simulation::getInstance() {
    if (!instance) {
        instance = new Simulation();
    }
    return instance;
}
