#include "SpriteManager.h"
#include "TextureManager.h"

void SpriteManager::LoadAllSprites(){
  // loads all sprites into map, has to be edited each time you add a new sprite
  LoadEachType("rigoberta");
  LoadEachType("poopie");
  LoadEachType("fire");
}


void SpriteManager::LoadEachType(string name){
  LoadSprite(name, "left");
  LoadSprite(name, "right");
  LoadSprite(name, "up");
  LoadSprite(name, "down");
  LoadSprite(name, "neutral");

}

void SpriteManager::LoadSprite(string name, string direction){
  // loads sprite into map for later use
    TextureManager::LoadTexture(name, direction);
    static sf::Sprite sprite;
    sprite.setTexture(TextureManager::GetTexture(name, direction));
    sprites[name + "_" + direction] = sprite;
}

sf::Sprite& SpriteManager::GetSprite(string name, string direction){
  // returns reference to sprite by given name
    return sprites[name + "_" + direction];
}

map<string, sf::Sprite> SpriteManager::sprites;
