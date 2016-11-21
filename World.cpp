//
// Created by Yorick on 10/11/2016.
//

#include "World.h"
#include "rng.h"
#include "settings.h"

World::World() : height(Settings::SimulationHeight), width(Settings::SimulationWidth) {
    tiles.resize(getSize());
    walls.resize(getSize());
    sound.resize(getSize());
    heat.resize(getSize());

    std::fill(tiles.begin(), tiles.end(), 0);
    std::fill(walls.begin(), walls.end(), -1);
    std::fill(sound.begin(), sound.end(), 0);
    std::fill(heat.begin(), heat.end(), 0);

//    MAPGEN
    for (int i = 0; i < width; ++i) {
        tiles[at(i, 0)] = 1;
        tiles[at(i, height - 1)] = 1;
    }
    for (int i = 0; i < width; ++i) {
        tiles[at(0, i)] = 1;
        tiles[at(width - 1, i)] = 1;
    }


//    for (int i = 0; i < width; ++i) {
//        if (i % 10 != 0) {
//            tiles[at(10, i)] = 1;
//            tiles[at(width - 10, i)] = 1;
//        }
//    }
    // Random debris
//    for (int y = 1; y < height; ++y) {
//        for (int x = 1; x < width; ++x) {
//            if (rng::getRandomIntBetween(1, 10) == 1) {
//                tiles[at(x, y)] = 1;
//            }
//        }
//    }
}

int World::at(const int x, const int y) {
    if (y < 0 || y > height - 1 || x < 0 || x > width - 1) {
        return -1;
    }
    return (y * width) + x;
}

int World::getHeatAt(const int x, const int y) {
    int i = at(x, y);
    if (i < 0) {
        return 0;
    }
    return heat[i];
}

int World::getSoundAt(const int x, const int y) {
    int i = at(x, y);
    if (i < 0) {
        return 0;
    }
    return sound[i];
}

std::vector<int> World::getNewMap() {
    std::vector<int> newMap;
    newMap.resize(getSize());

    std::fill(newMap.begin(), newMap.end(), 0);
    return newMap;
}

std::pair<int, int> World::at(int i) {
    int y = 0;
    while (i > getWidth() - 1) {
        y++;
        i -= getWidth() - 1;
    }
    return std::make_pair(i, y);
}
