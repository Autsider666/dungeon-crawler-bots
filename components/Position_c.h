//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_POSITION_H
#define SOLOMON_POSITION_H


#include <stdint.h>
#include <sstream>
#include "../Game.h"

struct Position_c {
    Position_c() { }

    Position_c(const int X, const int Y) : x(X), y(Y) { }

    int x, y;

    // Boilerplate required for the ECS
    std::size_t serialization_identity = 1;

    bool operator==(const Position_c &other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Position_c &other) const {
        return (x != other.x || y != other.y);
    }

    void bounds_check() {
        World *map = Game::getInstance()->getWorld();
        if (x < 0) x = 0;
        if (x > map->getWidth()) x = map->getWidth();
        if (y < 0) y = 0;
        if (y > map->getHeight()) y = map->getHeight();
    }
};


#endif //SOLOMON_POSITION_H
