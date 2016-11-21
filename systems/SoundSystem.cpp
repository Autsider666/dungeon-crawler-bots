//
// Created by Yorick on 19/11/2016.
//

#include "SoundSystem.h"
#include "../components/SoundSource_c.h"
#include "../components/Position_c.h"
#include "../Simulation.h"
#include "../settings.h"
#include "../utility/ShadowCaster.h"

void SoundSystem::configure() {
    system_name = "Sound System";
}

void SoundSystem::update(const double duration_ms) {
    Simulation::getInstance()->getWorld()->resetSoundMap();
    std::deque<Position_c> queue;
    rltk::each<Position_c, SoundSource_c>([&queue](rltk::entity_t &entity, Position_c &pos, SoundSource_c &sound) {
        World *w = Simulation::getInstance()->getWorld();

        queue.push_back(pos);
        w->setSoundAt(pos.x, pos.y, sound.strength);
        std::vector<int> fovMap = ShadowCaster::cast(pos.x, pos.y, sound.strength);
//        for (int y = 0; y < w->getHeight(); ++y) {
//            for (int x = 0; x < w->getWidth(); ++x) {
//                std::cout << fovMap[w->at(x, y)];
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;

        while (!queue.empty()) {
            Position_c currentPos{queue.front().x, queue.front().y};
            queue.pop_front();
            int strength = w->getSoundAt(currentPos.x, currentPos.y) - 2;
            int diagonalStrength = w->getSoundAt(currentPos.x, currentPos.y) - 3;
            std::vector<Position_c> edges;
            edges.push_back(Position_c(currentPos.x + 1, currentPos.y));
            edges.push_back(Position_c(currentPos.x, currentPos.y + 1));
            edges.push_back(Position_c(currentPos.x, currentPos.y - 1));
            edges.push_back(Position_c(currentPos.x - 1, currentPos.y));

            edges.push_back(Position_c(currentPos.x + 1, currentPos.y + 1));
            edges.push_back(Position_c(currentPos.x + 1, currentPos.y - 1));
            edges.push_back(Position_c(currentPos.x - 1, currentPos.y + 1));
            edges.push_back(Position_c(currentPos.x - 1, currentPos.y - 1));

            for (Position_c edge : edges) {
                if (edge.x >= 0 && edge.x < Settings::SimulationWidth && edge.y >= 0 &&
                    edge.y < Settings::SimulationHeight && w->isWalkableAt(edge.x, edge.y) &&
                    w->getSoundAt(edge.x, edge.y) < strength && strength > 0) {

                    if (currentPos.x == edge.x || currentPos.y == edge.y) {
                        w->setSoundAt(edge.x, edge.y, strength);
                    } else if (diagonalStrength > 0) {
                        w->setSoundAt(edge.x, edge.y, diagonalStrength);
                    }
                    queue.push_back(edge);
                }
            }
        }
    });
}
