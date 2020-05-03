#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class TextureManager{
    static map<string, sf::Texture> textures;
public:
    static void LoadAllTextures();
    static void LoadEachType(string name);
    static void LoadTexture(string name, string direction);
    static sf::Texture& GetTexture(string name, string direction);
};
