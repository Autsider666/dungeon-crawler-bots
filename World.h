//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_MAP_H
#define SOLOMON_MAP_H


#include <vector>
#include <stdint.h>

class World {
    int height;
    int width;

    std::vector<int> tiles;
    std::vector<uint8_t> visible;
    std::vector<bool> revealed;

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

    bool isRevealedAt(const int x, const int y) { return revealed[at(x, y)]; }

    bool isWalkableAt(const int x, const int y) { return (tiles[at(x, y)] == 0); }

    bool isReachable(const int x, const int y) { return (tiles[at(x, y)] <= 0); }

    uint8_t getVisibilityAt(const int x, const int y) { return visible[at(x, y)]; }

    int getTileAt(const int x, const int y) { return tiles[at(x, y)]; }

    void resetVisible();

    void increaseVisibilityAt(const int x, const int y);

    void revealTileAt(const int x, const int y) { revealed[at(x, y)] = true; }
};


#endif //SOLOMON_MAP_H
