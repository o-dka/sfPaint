#include "Tool.hpp"

Tool::Tool(sf::RenderWindow &ref) {
  m_texture.loadFromFile(m_filepath);
  m_sprite.setTexture(m_texture);
  m_sprite.setColor(sf::Color(colors[0],colors[1],colors[2],255));
  m_ref = new sf::RenderWindow();
  m_ref = &ref;
}

Tool::~Tool() {}

void Tool::Render(sf::RenderWindow &ref) {
  m_sprite.setPosition({getPos().x,getPos().y});
  m_sprite.setColor(sf::Color(colors[0],colors[1],colors[2],255));
  ref.draw(m_sprite);
}