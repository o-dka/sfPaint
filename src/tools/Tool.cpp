#include "Tool.hpp"

Tool::Tool() {
    m_texture.loadFromFile(m_filepath);
    m_sprite.setTexture(m_texture);
    m_sprite.setColor(sf::Color(colors[0],colors[1],colors[2],255));
}

Tool::~Tool() {}

void Tool::Render(sf::RenderWindow &ref) {
    m_sprite.setPosition({this->getPos(ref).x,this->getPos(ref).y  });
    m_sprite.setColor(sf::Color(colors[0],colors[1],colors[2],255));
    ref.draw(m_sprite);
}

