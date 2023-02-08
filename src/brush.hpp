#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>

class Brush : sf::RectangleShape ,sf::Mouse{
    //   private:
  public:
    virtual 
    Brush();
    ~Brush();
    void draw();
    int size = 10;
    int color[4]{
        0,   // R
        120, // G
        0,   // B
        100  // a (transparency)
    };
    
};
