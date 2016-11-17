//
// Created by Yorick on 12/11/2016.
//

#include <math.h>
#include "MonsterSensorSystem.h"
#include "../components/Position_c.h"
#include "../components/Brain_c.h"
#include "../components/Player_c.h"
#include "../components/Monster_c.h"
#include "../Simulation.h"
#include "../settings.h"

void MonsterSensorSystem::configure() {
    system_name = "Monster Sensor System";
}

void MonsterSensorSystem::update(const double duration_ms) {
    int monsters = 0;

    rltk::each<Monster_c, Position_c, Brain_c>(
            [&monsters](rltk::entity_t &entity, Monster_c &monster, Position_c &monsterPos, Brain_c &brain) {
                World *w = Simulation::getInstance()->getWorld();
                float PlayerSoundTopLeft = w->getPlayerSoundAt(round(monsterPos.x - 1), round(monsterPos.y - 1)) /
                                           Settings::BasicSoundRange;
                float PlayerSoundTopCenter =
                        w->getPlayerSoundAt(round(monsterPos.x), round(monsterPos.y - 1)) / Settings::BasicSoundRange;
                float PlayerSoundTopRight = w->getPlayerSoundAt(round(monsterPos.x + 1), round(monsterPos.y - 1)) /
                                            Settings::BasicSoundRange;
                float PlayerSoundCenterLeft =
                        w->getPlayerSoundAt(round(monsterPos.x - 1), round(monsterPos.y)) / Settings::BasicSoundRange;
                float PlayerSoundCenterRight =
                        w->getPlayerSoundAt(round(monsterPos.x + 1), round(monsterPos.y)) / Settings::BasicSoundRange;
                float PlayerSoundBotLeft = w->getPlayerSoundAt(round(monsterPos.x - 1), round(monsterPos.y + 1)) /
                                           Settings::BasicSoundRange;
                float PlayerSoundBotCenter =
                        w->getPlayerSoundAt(round(monsterPos.x), round(monsterPos.y + 1)) / Settings::BasicSoundRange;
                float PlayerSoundBotRight = w->getPlayerSoundAt(round(monsterPos.x + 1), round(monsterPos.y + 1)) /
                                            Settings::BasicSoundRange;

                std::vector<float> input = {PlayerSoundTopLeft, PlayerSoundTopCenter, PlayerSoundTopRight,
                                            PlayerSoundCenterLeft, PlayerSoundCenterRight, PlayerSoundBotLeft,
                                            PlayerSoundBotCenter, PlayerSoundBotRight,
                                            abs(sin(clock() / monster.clock1)),
                                            abs(sin(clock() / monster.clock1))};
                brain.tick(input);

//        Position_c *targetPosition;
//        float distance = -1;
//        rltk::each<Player_c, Position_c>(
//            [&pos,&targetPosition, &distance](rltk::entity_t &entity, Player_c &player,
//                                              Position_c &playerPos) {
//                float x = playerPos.x - pos.x;
//                float y = playerPos.y - pos.y;
//                float d = std::sqrt(x * x + y * y);
//                if (distance == -1 || d < distance) {
//                    distance = d;
//                    targetPosition = &playerPos;
//                }
//            });
//
//        float x = targetPosition->x - pos.x;
//        float y = targetPosition->y - pos.y;
//
//        float sx = tanh(x);
//        float sy = tanh(y);
//
//        if (distance > 10) {
//            x = 0;
//            y = 0;
//        }
//
//        std::vector<float> input = {x, y, distance, sx,
//                                    sy};//, abs(sin(clock() / agent.clock1)), abs(sin(clock() / agent.clock1))};
//        brain.tick(input);
                monsters++;
            });
    if (monsters > 40) {
        int tt = 1;
        tt = 2;
    }
}
