//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_RENDERABLE_H
#define SOLOMON_RENDERABLE_H


#include "../external/rltk/rltk/color_t.hpp"
#include "../external/rltk/rltk/colors.hpp"

struct Renderable_c {
    Renderable_c() { }

    Renderable_c(const char glyph, const rltk::color_t foreground, const int angle = 0) : glyph(glyph), fg(foreground),
                                                                                          angle(angle) { }

    int glyph;
    rltk::color_t fg = rltk::colors::WHITE;
    rltk::color_t bg = rltk::colors::BLACK;

    int angle;
};


#endif //SOLOMON_RENDERABLE_H
