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
    pos = sf::Mouse::getPosition(*(w));
    this->sf::RectangleShape::setPosition(
        sf::Vector2f(pos) + sf::Vector2f(10.f, 1.f)         // 
    );
    this->sf::RectangleShape::setFillColor(
        sf::Color(color[0], color[1], color[2], color[3])   //
    );
    this->setSize(sf::Vector2f(float(size), float(size)));
    // *w->draw(this);
}

void Brush::paint(sf::RectangleShape canvas, sf::Texture &t, sf::Sprite s) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        pos = sf::Mouse::getPosition(*(w));

        int pixel_arr_sz = (size * size) * 4;
        sf::Uint8 pixels[pixel_arr_sz];
        for (int i = 0; i != pixel_arr_sz - 4; i += 4) 
        {
            pixels[i] = color[0];
            pixels[i + 1] = color[1];
            pixels[i + 2] = color[2];
            pixels[i + 3] = color[3];
        }
        t.update(pixels,              //
                 unsigned(size),      //
                 unsigned(size),      //
                 unsigned(pos.x) + 1, //
                 unsigned(pos.y) + 10 //
        );
        s.setTexture(t);
    }
}
