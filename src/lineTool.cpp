#include "lineTool.hpp"

lineTool::lineTool(sf::Window &w) 
{
    p_pos = new sf::Vector2i[2];
    dots = new sf::RectangleShape[2];
    for (int i = 0;i < 2; i++)
    {
        dots[i].setSize(sf::Vector2f(2.f,2.f));
        dots[i].setOutlineColor(sf::Color::Black);
        dots[i].setFillColor(sf::Color::White);
    }
    wt = new sf::Window;
    wt = &w;
}

lineTool::~lineTool()
{
    delete[] p_pos;
    delete[] dots;
}

void lineTool::paint(sf::RectangleShape &canvas,sf::Texture &t,sf::Sprite &s,sf::RenderWindow &window)
{
    // copies from buffer to texture to sprite
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        p_pos[0] = sf::Mouse::getPosition(); // sets first point
        dots[0].setPosition( sf::Vector2f(p_pos[0]));
       
        while (true) 
         // looks for second point , right click to cancel  
        {
            window.draw(dots[0]); // draws it to screen 
            p_pos[1] = sf::Mouse::getPosition(*(wt)); // sets second point continusly
            dots[1].setPosition(sf::Vector2f(p_pos[1]));
            window.draw(dots[1]); // draws it to screen
            if((sf::Mouse::isButtonPressed(sf::Mouse::Right)))
            {
                break;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                
                sf::Uint8 pxl_buf[
                    (p_pos[0].x - p_pos[1].x) * (p_pos[0].y - p_pos[1].y) * 4
                ]; // draws it to pixel buffer
                for (int i = 0;i  <  sizeof(pxl_buf)/sizeof(sf::Uint8) ;i++)
                {

                } 
            }
        }
    }
     
}



