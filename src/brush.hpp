#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
class Brush : public sf::RectangleShape ,private sf::Mouse
{
  private:
  public:
    sf::Window *w = nullptr;
    Brush(sf::Window &win);
    ~Brush();
    int color[4] {
      0,   // R
      120, // G
      0,   // B
      255  // a (transparency)
    };
    int size;
    void pointer_draw(sf::RectangleShape canvas);
    void paint(sf::RectangleShape &canvas, sf::Texture &t, sf::Sprite &s);
};
