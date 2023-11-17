#pragma once

#include <vector>
#include <typeinfo>

#include "SFML-Includes.hpp"

class Tool : private sf::Mouse {
  public:
    sf::Uint8 colors[4] {0,0,255,255}; // 0000ff 

    Tool(sf::RenderWindow &ref);
    ~Tool();

    sf::Vector2f getPos() const{
      return sf::Vector2f(
          this->sf::Mouse::getPosition(*m_ref).x,
          this->sf::Mouse::getPosition(*m_ref).y);
    };

    sf::Color getColorFromPos(sf::Texture &t) {
      return t.copyToImage().getPixel(
          this->getPos().x,
          this->getPos().y
          );
    }
    void Render(sf::RenderWindow &ref);

    sf::Sprite getSprite() {return m_sprite;}

  private:
    sf::RenderWindow* m_ref = nullptr;
    std::string m_filepath = "pointer.png";
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};