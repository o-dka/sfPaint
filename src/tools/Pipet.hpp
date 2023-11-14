#pragma once
#include <cmath>
#include "SFML-Includes.hpp"
void setColorFromPos (const sf::Texture &t,int *a_colors,sf::Vector2f &pos);
sf::Image copyPixels(const sf::Texture &t, sf::Vector2f *a);
void pastePixels (sf::Texture &t, sf::Image copied_pixels, sf::Vector2f &pos); // can't paste pics :(
sf::Image cutPixels(sf::Texture &t,sf::Vector2f *a);
