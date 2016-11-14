//
// Created by Yorick on 12/11/2016.
//

#include "BrainSystem.h"
#include "../components/Position_c.h"
#include "../components/Brain_c.h"

void BrainSystem::configure() {
    system_name = "Brain System";
}

void BrainSystem::update(const double duration_ms) {
    rltk::each<Position_c, Brain_c>([](rltk::entity_t &entity, Position_c &pos, Brain_c &brain) {

    });
}
