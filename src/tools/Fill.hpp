#pragma once

#include <queue>

#include "SFML-Includes.hpp"

void FloodFill(sf::Sprite &s,sf::Texture &t ,sf::Color &target,sf::Color &replace,sf::Vector2u &strt_pos);
static bool isValid(const sf::Color &cur_pixel_color, const sf::Color &target, const sf::Color &replace, bool contained);
