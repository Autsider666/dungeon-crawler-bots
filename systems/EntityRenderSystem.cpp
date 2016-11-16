//
// Created by Yorick on 16/11/2016.
//

#include "EntityRenderSystem.h"
#include "../components/Position_c.h"
#include "../components/Renderable_c.h"
#include "../external/rltk/rltk/rltk.hpp"

using namespace rltk;
using namespace rltk::colors;

void EntityRenderSystem::configure() {
    system_name = "Entity Render System";
}

void EntityRenderSystem::update(const double duration_ms) {
    sterm(2)->clear();
    rltk::each<Position_c, Renderable_c>([](rltk::entity_t &entity, Position_c &pos, Renderable_c &renderable) {
        sterm(2)->add(xchar(renderable.glyph, renderable.fg, round(pos.x), round(pos.y),
                            renderable.angle));
    });
}
