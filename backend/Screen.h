#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
class Screen
{
public :
    int Run (sf::RenderWindow& window, Game& game, int type);
};
