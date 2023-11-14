#include "Pipet.hpp"

void setColorFromPos (const sf::Texture &t,int *a_colors,sf::Vector2f &pos){
  auto [r,g,b,a] = t.copyToImage().getPixel(
    pos.x,
    pos.y
  );
  a_colors[0] = r;
  a_colors[1] = g;
  a_colors[2] = b;
}

sf::Image copyPixels(const sf::Texture &t, sf::Vector2f *a) {
  sf::Vector2i a_int[2];
  a_int[0].x = a[0].x , a_int[0].y = a[0].y;
  a_int[1].x = a[1].x , a_int[1].y = a[1].y;
  sf::Image ret;
  ret.copy(t.copyToImage(),0,0,{{a_int[0].x,a_int[0].y},{a_int[1].x,a_int[1].y}});
  return ret;
}

void pastePixels(sf::Texture &t, sf::Image copied_pixels, sf::Vector2f &pos) {
          t.update( 
            copied_pixels,
            unsigned(pos.x),
            unsigned(pos.y)
        );

}

sf::Image cutPixels(sf::Texture &t,sf::Vector2f *a) {
  sf::Image copied_pixels =  copyPixels(t,a);
  sf::Uint8 pixel[4]  {255,255,255,255};
  t.update( 
    pixel,
    copied_pixels.getSize().x,
    copied_pixels.getSize().y,
    unsigned(a[0].x), // might be wrong here
    unsigned(a[0].y) // twice
  );
  return copied_pixels;
}
