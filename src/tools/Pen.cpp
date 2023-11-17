#include "Pen.hpp"
void Pen(sf::Texture &t, sf::Vector2i &pos,sf::Uint8 *c) {  
  // Algorithm:
  // 1. pass an array of Uint8 that has the same colour as the pointer
  // 2. fill an Uint8 array of pixels with corresponding color
  sf::Uint8 pixel_region[36*4];
  for (size_t i = 0  ;i <= 36;i++) {
        pixel_region[i * 4] = c[0];
        pixel_region[i * 4+1] = c[1];
        pixel_region[i * 4+2] = c[2];
        pixel_region[i * 4+3] = c[3];
  }
  // 4. update the texture
  t.update( pixel_region,6,6,pos.x,pos.y);  
}
