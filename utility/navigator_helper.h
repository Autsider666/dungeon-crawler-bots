//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_NAVIGATOR_HELPER_H
#define SOLOMON_NAVIGATOR_HELPER_H


#include <vector>
#include "../external/rltk/rltk/geometry.hpp"
#include "../components/Position_c.h"
#include "../World.h"
#include "../Simulation.h"

struct navigator_helper {
    // This lets you define a distance heuristic. Manhattan distance works really well, but
    // for now we'll just use a simple euclidian distance squared.
    // The geometry system defines one for us.
    static float get_distance_estimate(Position_c &pos, Position_c &goal) {
        float d = rltk::distance2d_manhattan(static_cast<float>(pos.x), static_cast<float>(pos.y),
                                             static_cast<float>(goal.x),
                                             static_cast<float>(goal.y));
        return d;
    }

    // Heuristic to determine if we've reached our destination? In some cases, you'd not want
    // this to be a simple comparison with the goal - for example, if you just want to be
    // adjacent to (or even a preferred distance from) the goal. In this case,
    // we're trying to get to the goal rather than near it.
    static bool is_goal(Position_c &pos, Position_c &goal) {
        return pos == goal;
    }

    // This is where we calculate where you can go from a given tile. In this case, we check
    // all 8 directions, and if the destination is walkable return it as an option.
    static bool get_successors(Position_c pos, std::vector<Position_c> &successors) {
        //std::cout << pos.x << "/" << pos.y << "\n";

        World *map = Simulation::getInstance()->getWorld();

        if (map->isReachable(static_cast<int>(pos.x - 1), static_cast<int>(pos.y - 1)))
            successors.push_back(Position_c(static_cast<int>(pos.x - 1), static_cast<int>(pos.y - 1)));
        if (map->isReachable(static_cast<int>(pos.x), static_cast<int>(pos.y - 1)))
            successors.push_back(Position_c(static_cast<int>(pos.x), static_cast<int>(pos.y - 1)));
        if (map->isReachable(static_cast<int>(pos.x + 1), static_cast<int>(pos.y - 1)))
            successors.push_back(Position_c(static_cast<int>(pos.x + 1), static_cast<int>(pos.y - 1)));

        if (map->isReachable(static_cast<int>(pos.x - 1), static_cast<int>(pos.y)))
            successors.push_back(Position_c(static_cast<int>(pos.x - 1), static_cast<int>(pos.y)));
        if (map->isReachable(static_cast<int>(pos.x + 1), static_cast<int>(pos.y)))
            successors.push_back(Position_c(static_cast<int>(pos.x + 1), static_cast<int>(pos.y)));

        if (map->isReachable(static_cast<int>(pos.x - 1), static_cast<int>(pos.y + 1)))
            successors.push_back(Position_c(static_cast<int>(pos.x - 1), static_cast<int>(pos.y + 1)));
        if (map->isReachable(static_cast<int>(pos.x), static_cast<int>(pos.y + 1)))
            successors.push_back(Position_c(static_cast<int>(pos.x), static_cast<int>(pos.y + 1)));
        if (map->isReachable(static_cast<int>(pos.x + 1), static_cast<int>(pos.y + 1)))
            successors.push_back(Position_c(static_cast<int>(pos.x + 1), static_cast<int>(pos.y + 1)));
        return true;
    }

    // This function lets you set a cost on a tile transition. For now, we'll always use a cost of 1.0.
    static float get_cost(Position_c &pos, Position_c &successor) {
//        if (pos.x == successor.x || pos.y == successor.y) {
//            return 1.0f;
//        } else {
//            return 1.4f;
//        }
        return 1.0f;
    }

    // This is a simple comparison to determine if two locations are the same. It just passes
    // through to the location_t's equality operator in this instance (we didn't do that automatically)
    // because there are times you might want to behave differently.
    static bool is_same_state(Position_c &lhs, Position_c &rhs) {
        return lhs == rhs;
    }

    static int get_x(const Position_c &loc) { return static_cast<int>(loc.x); }

    static int get_y(const Position_c &loc) { return static_cast<int>(loc.y); }

    static Position_c get_xy(const float &x, const float &y) { return Position_c{x, y}; }

    static bool is_walkable(const Position_c &loc) {
        return Simulation::getInstance()->getWorld()->isReachable(static_cast<int>(loc.x), static_cast<int>(loc.y));
    }
};


#endif //SOLOMON_NAVIGATOR_HELPER_H
