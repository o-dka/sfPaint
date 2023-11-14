#pragma once
#include <experimental/filesystem>
#include <SFML/Graphics.hpp>

void fileSave(sf::Texture &t);
bool fileOpen(const std::string &filename,sf::Texture &te,sf::Sprite &sprt);
