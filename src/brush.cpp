#include "brush.hpp"
Brush::Brush(sf::Window &win) {
    size = 10;
    w = new sf::Window;
    w = &win;
}

Brush::~Brush() {
    delete this->w;
}

void Brush::pointer_draw(sf::RectangleShape canvas) {
    this->sf::RectangleShape::setPosition(
        sf::Vector2f(sf::Mouse::getPosition(*(w)))  //
    );
    this->sf::RectangleShape::setFillColor(
        sf::Color(color[0], color[1], color[2], color[3]) //
    );
    this->setSize(sf::Vector2f(float(size), float(size)));
}

void Brush::paint(sf::RectangleShape &canvas, sf::Texture &t, sf::Sprite &s) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        int pixel_arr_sz = (size * size) * 4;
        sf::Uint8 pixels[pixel_arr_sz];
        for (int i = 0; i != pixel_arr_sz - 4; i += 4) {
            pixels[i] = color[0];
            pixels[i + 1] = color[1];
            pixels[i + 2] = color[2];
            pixels[i + 3] = color[3];
        }
        t.update(pixels,                                       //
                 unsigned(size),                               //
                 unsigned(size),                               //
                 unsigned(sf::Mouse::getPosition(*(w)).x) + 1, //
                 unsigned(sf::Mouse::getPosition(*(w)).y) + 10 //
        );
        s.setTexture(t);
    }
}
