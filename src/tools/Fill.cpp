#include "Fill.hpp"

void Fill::FloodFill(sf::Sprite &s,sf::Texture &t ,sf::Color &target,sf::Color &replace,sf::Vector2u &strt_pos)
{
  // https://en.wikipedia.org/wiki/Flood_fill#Stack-based_recursive_implementation_(four-way)

  std::queue<sf::Vector2u> q_pixels; // queue of positions of pixels

  q_pixels.push(strt_pos);
  sf::Image i = t.copyToImage();
  sf::Uint8 replace_enc[4] = {replace.r,replace.g,replace.b,replace.a};
  sf::FloatRect bounds = s.getLocalBounds();
  
  // t.update (replace_enc,1,1,q_pixels.back().x,q_pixels.back().y);
  while (!q_pixels.empty()) {
    sf::Vector2u pixel = q_pixels.front();
    q_pixels.pop();
    if (isValid(i.getPixel(pixel.x,pixel.y),target,replace,bounds.contains(static_cast<sf::Vector2f>(pixel))))
    {
      pixel.x -=1;
      t.update (replace_enc,1,1,pixel.x,pixel.y);
      q_pixels.push(pixel);
    }

    if (isValid(i.getPixel(pixel.x,pixel.y),target,replace,bounds.contains(static_cast<sf::Vector2f>(pixel))))
    {
      pixel.x +=1;
      t.update (replace_enc,1,1,pixel.x,pixel.y);
      q_pixels.push(pixel);
    }
    if (isValid(i.getPixel(pixel.x,pixel.y),target,replace,bounds.contains(static_cast<sf::Vector2f>(pixel))))
    {
       pixel.y += 1;
       t.update (replace_enc,1,1,pixel.x,pixel.y);
        q_pixels.push(pixel);
    }

    if (isValid(i.getPixel(pixel.x,pixel.y),target,replace,bounds.contains(static_cast<sf::Vector2f>(pixel)))) 
    {
        pixel.y -= 1;
        t.update(replace_enc,1,1,pixel.x,pixel.y);
        q_pixels.push(pixel);
    }
  }
}

bool Fill::isValid(const sf::Color &cur_pixel_color, const sf::Color &target, const sf::Color &replace, bool contained) {
  if (contained && cur_pixel_color == target &&  cur_pixel_color != replace) {
    return true;
  }
  return false;
}
