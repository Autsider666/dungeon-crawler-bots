//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_POSITION_H
#define SOLOMON_POSITION_H


#include <stdint.h>
#include <sstream>

struct Position_c {
    Position_c() { }

    Position_c(const float X, const float Y) : x(X), y(Y) { }

    float x, y;

    bool operator==(const Position_c &other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Position_c &other) const {
        return (x != other.x || y != other.y);
    }
};


#endif //SOLOMON_POSITION_H
