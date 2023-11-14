#pragma once

#include <vector>
#include <typeinfo>

#include "SFML-Includes.hpp"

class Tool : private sf::Mouse {
  public:
    int colors[3] {0,0,255};

    std::vector<sf::Vector2f> posm;

    Tool();
    ~Tool();

     sf::Vector2f getPos(sf::RenderWindow &ref) const{
              return sf::Vector2f(
                this->sf::Mouse::getPosition(ref).x,
                this->sf::Mouse::getPosition(ref).y);
    };
    
    void Render(sf::RenderWindow &ref);
    
    sf::Sprite getSprite() {return m_sprite;};

    private:
    std::string m_filepath = "pointer.png";
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};
