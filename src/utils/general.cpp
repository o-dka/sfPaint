#include "general.hpp"

void fileSave(sf::Texture &t) {
  namespace fs = std::experimental::filesystem;
  std::string filename = "Unnamed_0.png";
  for (int x = 0;; x++) {
      if (fs::exists(filename) == false) {
        t.copyToImage().saveToFile(filename);
        break;
      }
      else 
        filename.replace(8, 1, std::to_string(x + 1));
  }
}

bool fileOpen(const std::string &filename,sf::Texture &te,sf::Sprite &sprt) {
  if (te.loadFromFile(filename)){
    sprt.setTexture(te);
    return true;
  }
  return false; 
}

