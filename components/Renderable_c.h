//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_RENDERABLE_H
#define SOLOMON_RENDERABLE_H


#include "../external/rltk/rltk/color_t.hpp"
#include "../external/rltk/rltk/colors.hpp"

struct Renderable_c {
    Renderable_c() { }

    Renderable_c(const char Glyph, const rltk::color_t foreground) : glyph(Glyph), fg(foreground) { }

    int glyph;
    rltk::color_t fg = rltk::colors::WHITE;
    rltk::color_t bg = rltk::colors::BLACK;

    // Boilerplate required for the ECS
    std::size_t serialization_identity = 2;
};


#endif //SOLOMON_RENDERABLE_H
