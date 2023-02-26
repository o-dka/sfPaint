#pragma once
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cmath>
class lineTool : public sf::Vertex , public sf::Mouse
{
private:
  const static float thickness = 1.f;
  sf::Vector2i *p_pos = nullptr; // position of points
  sf::Window *wt = nullptr;
  sf::RectangleShape *dots = nullptr;
public:
  // sf::Window &win;
  
  lineTool(sf::Window &w);
  ~lineTool();
  void lineTool::paint(sf::RectangleShape &canvas, sf::Texture &t,
                       sf::Sprite &s, sf::RenderWindow &window);
};
