#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Mouse.hpp>

class Line : public sf::Drawable {
  private:
    sf::VertexArray line_pr;
    //
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  public:
    // default color : green
    Line();
    // while the left button is pressed the position is getting set
    void set_points(sf::Window &window);
    void set_color(sf::Color color_in);
    // void paint_on_texture(sf::Texture &t);
};