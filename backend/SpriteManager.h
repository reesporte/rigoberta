#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class SpriteManager{
    static map<string, sf::Sprite> sprites;
public:
    static void LoadAllSprites();
    static void LoadEachType(string name);
    static void LoadSprite(string name, string direction);
    static sf::Sprite& GetSprite(string name, string direction);
};
