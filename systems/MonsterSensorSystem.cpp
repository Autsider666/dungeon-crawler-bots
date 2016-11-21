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
    rltk::each<Monster_c, Position_c, Brain_c>(
            [](rltk::entity_t &entity, Monster_c &monster, Position_c &monsterPos, Brain_c &brain) {
                World *w = Simulation::getInstance()->getWorld();
//                EACH DIRECTION NORMALIZED
                float PlayerSoundTopLeft = 1.0f * w->getHeatAt(monsterPos.x - 1, monsterPos.y - 1) /
                                           Settings::BasicHeatRange;
                float PlayerSoundTopCenter =
                        1.0f * w->getHeatAt(monsterPos.x, monsterPos.y - 1) / Settings::BasicHeatRange;
                float PlayerSoundTopRight = 1.0f * w->getHeatAt(monsterPos.x + 1, monsterPos.y - 1) /
                                            Settings::BasicHeatRange;

                float PlayerSoundCenterLeft =
                        1.0f * w->getHeatAt(monsterPos.x - 1, monsterPos.y) / Settings::BasicHeatRange;
                float PlayerSoundCenter =
                        1.0f * w->getHeatAt(monsterPos.x, monsterPos.y) / Settings::BasicHeatRange;
                float PlayerSoundCenterRight =
                        1.0f * w->getHeatAt(monsterPos.x + 1, monsterPos.y) / Settings::BasicHeatRange;

                float PlayerSoundBotLeft = 1.0f * w->getHeatAt(monsterPos.x - 1, monsterPos.y + 1) /
                                           Settings::BasicHeatRange;
                float PlayerSoundBotCenter =
                        1.0f * w->getHeatAt(monsterPos.x, monsterPos.y + 1) / Settings::BasicHeatRange;
                float PlayerSoundBotRight = 1.0f * w->getHeatAt(monsterPos.x + 1, monsterPos.y + 1) /
                                            Settings::BasicHeatRange;

//                std::vector<float> input = {PlayerSoundTopLeft, PlayerSoundTopCenter, PlayerSoundTopRight,
//                                            PlayerSoundCenterLeft, PlayerSoundCenter, PlayerSoundCenterRight,
//                                            PlayerSoundBotLeft,
//                                            PlayerSoundBotCenter, PlayerSoundBotRight};//,
////                                            abs(sin(clock() / monster.clock1)),
////                                            abs(sin(clock() / monster.clock1))};
                float x = 0, y = 0;
                float top = (PlayerSoundTopLeft+PlayerSoundTopCenter+PlayerSoundTopRight)/3;
                float bot = (PlayerSoundBotLeft,PlayerSoundBotCenter,PlayerSoundBotRight)/3;
                float left = (PlayerSoundTopLeft+PlayerSoundCenterLeft+PlayerSoundBotLeft)/3;
                float right = (PlayerSoundTopRight+PlayerSoundCenterRight+PlayerSoundBotRight)/3;

                if (top > bot){
                    y -=1;
                } else if (top < bot) {
                    y+=1;
                }

                if (left > right) {
                    x -=1;
                } else if (left > right) {
                    x+=1;
                }

                std::vector<float> input = {x,y, abs(sin(clock() / monster.clock1))};//, abs(sin(clock() / monster.clock2))};


////                EACH DIRECTION UNNORMALIZED
//                float PlayerSoundTopLeft = w->getHeatAt(monsterPos.x - 1, monsterPos.y - 1);
//                float PlayerSoundTopCenter = w->getHeatAt(monsterPos.x, monsterPos.y - 1);
//                float PlayerSoundTopRight = w->getHeatAt(monsterPos.x + 1, monsterPos.y - 1);
//
//                float PlayerSoundCenterLeft = w->getHeatAt(monsterPos.x - 1, monsterPos.y);
//                float PlayerSoundCenter = w->getHeatAt(monsterPos.x, monsterPos.y);
//                float PlayerSoundCenterRight = w->getHeatAt(monsterPos.x + 1, monsterPos.y);
//
//                float PlayerSoundBotLeft = w->getHeatAt(monsterPos.x - 1, monsterPos.y + 1);
//                float PlayerSoundBotCenter = w->getHeatAt(monsterPos.x, monsterPos.y + 1);
//                float PlayerSoundBotRight = w->getHeatAt(monsterPos.x + 1, monsterPos.y + 1);
//
//
//
//                std::vector<float> input = {PlayerSoundTopLeft, PlayerSoundTopCenter, PlayerSoundTopRight,
//                                            PlayerSoundCenterLeft, PlayerSoundCenter, PlayerSoundCenterRight,
//                                            PlayerSoundBotLeft,
//                                            PlayerSoundBotCenter, PlayerSoundBotRight};//,
////                                            abs(sin(clock() / monster.clock1)),
////                                            abs(sin(clock() / monster.clock2))};

////                LETERAL ONLY
//                float PlayerSoundTopCenter = w->getHeatAt(monsterPos.x, monsterPos.y - 1);
//                float PlayerSoundCenterLeft = w->getHeatAt(monsterPos.x - 1, monsterPos.y);
//                float PlayerSoundCenterRight = w->getHeatAt(monsterPos.x + 1, monsterPos.y);
//                float PlayerSoundBotCenter = w->getHeatAt(monsterPos.x, monsterPos.y + 1);
//
//                std::vector<float> input = {PlayerSoundTopCenter, PlayerSoundCenterLeft, PlayerSoundCenterRight,
//                                            PlayerSoundBotCenter, abs(sin(clock() / monster.clock1))};


                brain.tick(input);
            });
}
