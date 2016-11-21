//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_MAP_H
#define SOLOMON_MAP_H


#include <vector>
#include <stdint.h>
#include "components/Position_c.h"

class World {
    int height;
    int width;

    std::vector<int> tiles;
    std::vector<int> walls;
    std::vector<int> sound;
    std::vector<int> heat;
public:
    World();

    std::vector<int> getNewMap();

    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    int getSize() const {
        return height * width;
    }

    int at(const int x, const int y);

    std::pair<int,int> at(int i);

    bool isWalkableAt(const int x, const int y) { return (tiles[at(x, y)] == 0); }

    bool isReachable(const int x, const int y) { return (tiles[at(x, y)] <= 0); }

    int getTileAt(const int x, const int y) { return tiles[at(x, y)]; }

    int getSoundAt(const int x, const int y);

    void setSoundAt(const int x, const int y, const int value) { sound[at(x, y)] = value; }

    void resetSoundMap() { std::fill(sound.begin(), sound.end(), 0); }

    int getHeatAt(const int x, const int y);

    void setHeatAt(const int x, const int y, const int value) { heat[at(x, y)] = value; }

    void resetHeatMap() { std::fill(heat.begin(), heat.end(), 0); }
};


#endif //SOLOMON_MAP_H
