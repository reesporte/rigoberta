/*
  TODO:
    [] fireball class
    [] extra life
    [] make another level where fireballs go up and down
*/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "backend/Game.h"
#include "backend/SpriteManager.h"
#include "backend/TextureManager.h"
#include "backend/Character.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "backend/Screen.h"

int main()
{
  Game game;
  /* set up music */
  game.setUpMusic();

  /* init window */
  sf::RenderWindow window(sf::VideoMode(800, 800), "the Rigoberta game", sf::Style::Close | sf::Style::Titlebar);
  window.clear(sf::Color(0, 0, 0, 255));
  window.setFramerateLimit(15);

  int screen = 0;

  Screen App;

  /* set up sound effects */
  game.setUpSoundEffects();
  /* set up fonts and text display area */
  game.setUpText();

  while (screen >= 0) {
    screen = App.Run(window, game, screen);
  }

  return 0;
}
