#include "brush.hpp"
Brush::Brush()
{}

Brush::~Brush()
{}

void Brush::draw()
{
    int pixel_arr_sz = (size * size) * 4;

    sf::Uint8 pixels[pixel_arr_sz];
    for (int i = 0; i != pixel_arr_sz - 4; i += 4) {
        pixels[i] = colors[0];
        pixels[i + 1] = colors[1];
        pixels[i + 2] = colors[2];
        pixels[i + 3] = colors[3];
    }

    if ((float(mousepos.x) < bckgrnd_box.getSize().x) &&
        (float(mousepos.y) < bckgrnd_box.getSize().y)) {
        bckgrnd.update(pixels,               //
                       unsigned(brush_size), //
                       unsigned(brush_size), //
                       unsigned(mousepos.x) + 1, unsigned(mousepos.y) + 10);
        bckgrnd_sprt.setTexture(bckgrnd);
    }
}
