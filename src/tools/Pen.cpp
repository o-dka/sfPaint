#include "Pen.hpp"
void copyToTex(sf::Texture &t,sf::Sprite &in_s,sf::Sprite &s,int &size,std::vector<sf::Vector2f> & vof_vf)
{
    in_s.setScale(size,size);
    const sf::Uint8 *cursor = in_s.getTexture()->copyToImage().getPixelsPtr();    
    for (auto a : vof_vf) {
        t.update( 
            cursor,
            size,
            size,
            unsigned(a.x),
            unsigned(a.y)
        );
    }
    s.setTexture(t);
    
}
