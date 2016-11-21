//
// Created by Yorick on 20/11/2016.
//

#include <cmath>
#include "ShadowCaster.h"
#include "../World.h"
#include "../Simulation.h"

std::vector<int> ShadowCaster::cast(int x, int y, int range) {
    std::vector<int> fovMap = Simulation::getInstance()->getWorld()->getNewMap();

    int multipliers[4][8] = {
            {1, 0, 0,  -1, -1, 0,  0,  1},
            {0, 1, -1, 0,  0,  -1, 1,  0},
            {0, 1, 1,  0,  0,  -1, -1, 0},
            {1, 0, 0,  1,  -1, 0,  0,  -1}
    };

    for (int i = 0; i < 8; i++) {
        cast_light(fovMap, x, y, range, 1, 1.0, 0.0, multipliers[0][i],
                   multipliers[1][i], multipliers[2][i], multipliers[3][i]);
    }
    return fovMap;
}

void ShadowCaster::cast_light(std::vector<int> &map, int x, int y, int radius, int row,
                              double start_slope, double end_slope, int xx, int xy, int yx,
                              int yy) {
    World *w = Simulation::getInstance()->getWorld();
    if (start_slope < end_slope) {
        return;
    }
    double next_start_slope = start_slope;
    for (int i = row; i <= radius; i++) {
        bool blocked = false;
        for (int dx = -i, dy = -i; dx <= 0; dx++) {
            double l_slope = (dx - 0.5) / (dy + 0.5);
            double r_slope = (dx + 0.5) / (dy - 0.5);
            if (start_slope < r_slope) {
                continue;
            } else if (end_slope > l_slope) {
                break;
            }

            int sax = dx * xx + dy * xy;
            int say = dx * yx + dy * yy;
            if ((sax < 0 && (int)std::abs(sax) > x) ||
                (say < 0 && (int)std::abs(say) > y)) {
                continue;
            }
            int ax = x + sax;
            int ay = y + say;
            if (ax >= w->getWidth() || ay >= w->getHeight()) {
                continue;
            }

            int radius2 = radius * radius;
            if ((int)(dx * dx + dy * dy) < radius2) {
                map[w->at(ax,ay)] = 1;
            }

            if (blocked) {
                if (w->isWalkableAt(ax,ay)) {
                    next_start_slope = r_slope;
                    continue;
                } else {
                    blocked = false;
                    start_slope = next_start_slope;
                }
            } else if (w->isWalkableAt(ax,ay)) {
                blocked = true;
                next_start_slope = r_slope;
                cast_light(map, x, y, radius, i + 1, start_slope, l_slope, xx,
                           xy, yx, yy);
            }
        }
        if (blocked) {
            break;
        }
    }
}

//void ShadowCaster::cast_light(std::vector<int> &map, int x, int y, int radius, int row,
//                              double start_slope, double end_slope, int xx, int xy, int yx,
//                              int yy) {
//    World *w = Simulation::getInstance()->getWorld();
//    if (start_slope < end_slope) {
//        return;
//    }
//    double next_start_slope = start_slope;
//    for (int i = row; i <= radius; i++) {
//        bool blocked = false;
//        for (int dx = -i, dy = -i; dx <= 0; dx++) {
//            double l_slope = (dx - 0.5) / (dy + 0.5);
//            double r_slope = (dx + 0.5) / (dy - 0.5);
//            if (start_slope < r_slope) {
//                continue;
//            } else if (end_slope > l_slope) {
//                break;
//            }
//
//            int sax = dx * xx + dy * xy;
//            int say = dx * yx + dy * yy;
//            if ((sax < 0 && (int)std::abs(sax) > x) ||
//                (say < 0 && (int)std::abs(say) > y)) {
//                continue;
//            }
//            int ax = x + sax;
//            int ay = y + say;
//            if (ax >= w->getWidth() || ay >= w->getHeight()) {
//                continue;
//            }
//
//            int radius2 = radius * radius;
//            if ((int)(dx * dx + dy * dy) < radius2) {
//                map[w->at(ax,ay)] = 1;
//            }
//
//            if (blocked) {
//                if (w->isWalkableAt(ax,ay)) {
//                    next_start_slope = r_slope;
//                    continue;
//                } else {
//                    blocked = false;
//                    start_slope = next_start_slope;
//                }
//            } else if (w->isWalkableAt(ax,ay)) {
//                blocked = true;
//                next_start_slope = r_slope;
//                cast_light(map, x, y, radius, i + 1, start_slope, l_slope, xx,
//                           xy, yx, yy);
//            }
//        }
//        if (blocked) {
//            break;
//        }
//    }
//}
