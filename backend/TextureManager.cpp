#include "TextureManager.h"
#include <iostream>

void TextureManager::LoadAllTextures(){
  LoadEachType("rigoberta");
  LoadEachType("poopie");
}

void TextureManager::LoadEachType(string name) {
  LoadTexture(name, "left");
  LoadTexture(name, "right");
  LoadTexture(name, "up");
  LoadTexture(name, "down");
  LoadTexture(name, "neutral");
}

void TextureManager::LoadTexture(string name, string direction){
    string spr = "resources/sprites/" + name + "/"  + name + "_" + direction + ".png";
    static sf::Texture texture;
    if ( !textures[name + "_" + direction].loadFromFile(spr) ){
      std::cout << "error loading " << spr << '\n';
    }
}

sf::Texture& TextureManager::GetTexture(string name, string direction){
    return textures[name + "_" + direction];
}

map<string, sf::Texture> TextureManager::textures;
