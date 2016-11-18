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
                float PlayerSoundTopLeft = w->getHeatAt(round(monsterPos.x - 1), round(monsterPos.y - 1)) /
                                           Settings::BasicHeatRange;
                float PlayerSoundTopCenter =
                        w->getHeatAt(round(monsterPos.x), round(monsterPos.y - 1)) / Settings::BasicHeatRange;
                float PlayerSoundTopRight = w->getHeatAt(round(monsterPos.x + 1), round(monsterPos.y - 1)) /
                                            Settings::BasicHeatRange;

                float PlayerSoundCenterLeft =
                        w->getHeatAt(round(monsterPos.x - 1), round(monsterPos.y)) / Settings::BasicHeatRange;
                float PlayerSoundCenter =
                        w->getHeatAt(round(monsterPos.x), round(monsterPos.y)) / Settings::BasicHeatRange;
                float PlayerSoundCenterRight =
                        w->getHeatAt(round(monsterPos.x + 1), round(monsterPos.y)) / Settings::BasicHeatRange;

                float PlayerSoundBotLeft = w->getHeatAt(round(monsterPos.x - 1), round(monsterPos.y + 1)) /
                                           Settings::BasicHeatRange;
                float PlayerSoundBotCenter =
                        w->getHeatAt(round(monsterPos.x), round(monsterPos.y + 1)) / Settings::BasicHeatRange;
                float PlayerSoundBotRight = w->getHeatAt(round(monsterPos.x + 1), round(monsterPos.y + 1)) /
                                            Settings::BasicHeatRange;

                std::vector<float> input = {PlayerSoundTopLeft, PlayerSoundTopCenter, PlayerSoundTopRight,
                                            PlayerSoundCenterLeft, PlayerSoundCenter, PlayerSoundCenterRight,
                                            PlayerSoundBotLeft,
                                            PlayerSoundBotCenter, PlayerSoundBotRight,
                                            abs(sin(clock() / monster.clock1)),
                                            abs(sin(clock() / monster.clock1))};
                brain.tick(input);
            });
}
