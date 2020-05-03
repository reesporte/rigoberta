#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Character{
  // graphics
  sf::Sprite sprite;
  sf::Texture up;
  sf::Texture down;
  sf::Texture left;
  sf::Texture right;
  sf::Texture neutral;

  bool fire_texture;
  bool visible;
  bool bumpable;

  // game related
  float speed;
  int direction;
  int points;
  int lives;

  // position
  float currentX;
  float currentY;

  // size
  float height;
  float width;

public:
  Character();
  Character(string name);

  float getY();
  float getX();

  float getHeight();
  float getWidth();

  void setIsVisible(bool visible);
  bool isVisible();

  void setIsBumpable(bool bumpable);
  bool isBumpable();

  void setSize(int size);

  int getPoints();
  void incrementPoints(int value);

  int getLives();
  void decrementLives(int value);

  float getSpeed();
  void incrementSpeed(float value);

  sf::Sprite& getSprite();

  void movement(sf::Event& event);
  void setPosition(float x, float y);
  bool bumpedInto(Character& guy);

  void lookAtMe();

  void setSpeedandDirection(float speed, int direction);
  void strafe();

  bool isInMySpaceX(int x);
  bool isInMySpaceY(int y);

};
