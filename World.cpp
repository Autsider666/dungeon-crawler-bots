//
// Created by Yorick on 10/11/2016.
//

#include "World.h"
#include "rng.h"
#include "settings.h"

World::World() : height(settings::SimulationHeight), width(settings::SimulationWidth) {
    tiles.resize(getSize());
    visible.resize(getSize());
    revealed.resize(getSize());

    std::fill(tiles.begin(), tiles.end(), 0);
    std::fill(visible.begin(), visible.end(), false);
    std::fill(revealed.begin(), revealed.end(), false);

//    for (int i = 0; i < width; ++i) {
//        tiles[at(i, 0)] = 1;
//        tiles[at(i, height - 1)] = 1;
//    }
//    for (int i = 0; i < width; ++i) {
//        tiles[at(0, i)] = 1;
//        tiles[at(width - 1, i)] = 1;
//    }
//    // Random debris
//    for (int y = 1; y < height - 1; ++y) {
//        for (int x = 1; x < width - 1; ++x) {
//            if (rng::getRandomIntBetween(1,5) == 1 && (x != width / 2 || y != height / 2)){
//                tiles[at(x, y)] = 1;
//            } else if (rng::getRandomIntBetween(1,25) == 1 && (x != width / 2 || y != height / 2)){
//                tiles[at(x, y)] = -1;
//            }
//        }
//    }
}

void World::resetVisible() {
    std::fill(visible.begin(), visible.end(), 0);
}

void World::increaseVisibilityAt(const int x, const int y) {
    if (visible[at(x,y)] < 8) {
        ++visible[at(x,y)];
    }
}
