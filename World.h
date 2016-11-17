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
    std::vector<int> MonsterSound;
    std::vector<int> PlayerSound;

public:
    World();

    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    int getSize() const {
        return height * width;
    }

    int at(const int x, const int y) { return (y * width) + x; }

    bool isWalkableAt(const int x, const int y) { return (tiles[at(x, y)] == 0); }

    bool isReachable(const int x, const int y) { return (tiles[at(x, y)] <= 0); }

    int getTileAt(const int x, const int y) { return tiles[at(x, y)]; }

    int getMonsterSoundAt(const int x, const int y) { return MonsterSound[at(x, y)]; }

    void setMonsterSoundAt(const int x, const int y, const int value) { MonsterSound[at(x, y)] = value; }

    void resetMonsterSoundMap() { std::fill(MonsterSound.begin(), MonsterSound.end(), 0); }

    int getPlayerSoundAt(const int x, const int y) { return PlayerSound[at(x, y)]; }

    void setPlayerSoundAt(const int x, const int y, const int value) { PlayerSound[at(x, y)] = value; }

    void resetPlayerSoundMap() { std::fill(PlayerSound.begin(), PlayerSound.end(), 0); }
};


#endif //SOLOMON_MAP_H
