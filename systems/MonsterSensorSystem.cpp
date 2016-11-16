//
// Created by Yorick on 12/11/2016.
//

#include <math.h>
#include "MonsterSensorSystem.h"
#include "../components/Position_c.h"
#include "../components/Brain_c.h"
#include "../components/Player_c.h"

void MonsterSensorSystem::configure() {
    system_name = "Monster Sensor System";
}

void MonsterSensorSystem::update(const double duration_ms) {
    rltk::each<Position_c, Brain_c>([](rltk::entity_t &entity, Position_c &pos, Brain_c &brain) {
        Position_c *targetPosition;
        float distance = -1;
        rltk::each<Player_c, Position_c>(
                [&targetPosition, &distance](rltk::entity_t &entity, Player_c &player,
                                             Position_c &pos) {
                    float d = std::sqrt(pos.x * pos.x + pos.y * pos.y);
                    if (distance == -1 || d < distance) {
                        distance = d;
                        targetPosition = &pos;
                    }
                });

        float x = targetPosition->x - pos.x;
        float y = targetPosition->y - pos.y;

        float sx = tanh(x);
        float sy = tanh(y);

        if (distance > 10) {
            x = 0;
            y = 0;
        }

        std::vector<float> input = {x, y, distance, sx,
                                    sy};//, abs(sin(clock() / agent.clock1)), abs(sin(clock() / agent.clock1))};
        brain.tick(input);
    });
}
