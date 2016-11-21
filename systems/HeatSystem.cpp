//
// Created by Yorick on 19/11/2016.
//

#include "HeatSystem.h"
#include "../Simulation.h"
#include "../components/HeatSource_c.h"
#include "../settings.h"
#include "../external/rltk/rltk/geometry.hpp"
#include "../external/rltk/rltk/path_finding.hpp"

void HeatSystem::configure() {
    system_name = "Heat System";
}

void HeatSystem::update(const double duration_ms) {
    Simulation::getInstance()->getWorld()->resetHeatMap();
    World *w = Simulation::getInstance()->getWorld();
    rltk::each<Position_c, HeatSource_c>(
            [&w](rltk::entity_t &entity, Position_c &pos, HeatSource_c &heat) {
                std::deque<Position_c> queue;
                queue.push_back(pos);
                w->setHeatAt(pos.x, pos.y, heat.strength);
                while (!queue.empty()) {
                    Position_c currentPos{queue.front().x, queue.front().y};
                    queue.pop_front();
                    int strength = w->getHeatAt(currentPos.x, currentPos.y) - 2;
                    int diagonalStrength = w->getHeatAt(currentPos.x, currentPos.y) - 3;
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
                            w->getHeatAt(edge.x, edge.y) < strength && strength > 0) {

                            if (currentPos.x == edge.x || currentPos.y == edge.y) {
                                w->setHeatAt(edge.x, edge.y, strength);
                            } else if (diagonalStrength > 0) {
                                w->setHeatAt(edge.x, edge.y, diagonalStrength);
                            }
                            queue.push_back(edge);

                        }
                    }
                }
            });
}
