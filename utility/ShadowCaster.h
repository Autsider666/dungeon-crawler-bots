//
// Created by Yorick on 20/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_SHADOWCASTER_H
#define DUNGEONCRAWLERBOTS_SHADOWCASTER_H

#include <vector>
#include <stdint.h>

class ShadowCaster {
    static void cast_light(std::vector<int> &map, int x, int y, int radius, int row,
                           double start_slope, double end_slope, int xx, int xy, int yx,
                           int yy);

public:
    static std::vector<int> cast(int x, int y, int range);
};


#endif //DUNGEONCRAWLERBOTS_SHADOWCASTER_H
