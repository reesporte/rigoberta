/*
TODO
    [] extra life
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SpriteManager.h"
#include "TextureManager.h"
#include "Character.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

Character* makeFireball(Character& rigo);

class Game{
  // characters
  Character rigoberta;
  Character smiley;

  // fireballs
  std::vector<Character*> fireballs;

  // music
  sf::Music background;
  sf::Music loser;
  sf::Music win;
  sf::Music start;

  // sound effects
  sf::SoundBuffer goodbuffer;
  sf::Sound good;
  sf::SoundBuffer badbuffer;
  sf::Sound bad;

  // text
  bool display_NiceJob;
  sf::Font font;
  sf::Text nicejob;
  sf::Text pointsToWin;
  sf::Text points;
  sf::Text help;
  sf::Text howToPlay;
  sf::Text lives;
  sf::Sprite winScreen;
  sf::Sprite loseScreen;

  // counters
  int fireball_counter;
  int frames_since_point;
  int fireball_timer;
  int points_to_win;
  bool game_over;
  bool winner;

public:
  // init
  Game();

  // main functions
  void setPointsToWin(int value);
  void didRigobertaGetAPoint();
  void didRigobertaLoseAPoint();
  void checkGameOver();
  void drawUpdates(sf::RenderWindow& window);
  void deleteFireball();
  void restartGame();
  int mainLoop(sf::RenderWindow& window);

  // music
  void setUpMusic();
  bool isMusicPlaying(string type);
  void playMusic(string type);
  void stopMusic(string type);

  // sound effects
  void setUpSoundEffects();
  bool isSoundEffectPlaying(string type);
  void playSoundEffect(string type);

  // text
  bool displayNiceJob();
  void setDisplayNiceJob(bool value);
  void setUpText();
  void setText(string type, string text);
  void drawText(sf::RenderWindow& window);

};
