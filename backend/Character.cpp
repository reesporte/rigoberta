#include <SFML/Graphics.hpp>
#include "SpriteManager.h"
#include "TextureManager.h"
#include "Character.h"

#include <iostream>

Character::Character(){
  // nothing
}

Character::Character(string name){
  /* has to be run after LoadAllSprites() has been called. */

  // sprite
  sprite = SpriteManager::GetSprite(name, "neutral");
  // textures
  left = TextureManager::GetTexture(name, "left");
  right = TextureManager::GetTexture(name, "right");
  up = TextureManager::GetTexture(name, "up");
  down = TextureManager::GetTexture(name, "down");
  neutral = TextureManager::GetTexture(name, "neutral");
  // numbers
  speed = 25.f;
  points = 0;
  // position
  currentX = 0;
  currentY = 0;
  // size
  height = left.getSize().y;
  width = left.getSize().x;

  direction = -1;
  visible = true;
  bumpable = true;
  fire_texture = false;
  lives = 3;
}

sf::Sprite& Character::getSprite(){
  return sprite;
}

float Character::getY(){
  return currentY;
}
float Character::getX(){
  return currentX;
}
float Character::getWidth(){
  return width;
}
float Character::getHeight(){
  return height;
}
void Character::setIsVisible(bool visible){
  this->visible = visible;
}
bool Character::isVisible(){
  return visible;
}
void Character::setIsBumpable(bool bumpable){
  this->bumpable = bumpable;
}
bool Character::isBumpable(){
  return bumpable;
}
void Character::setSize(int size){
  sprite.setTextureRect(sf::IntRect(0, 0, size, size));
}
int Character::getPoints(){
  return points;
}
void Character::incrementPoints(int value){
  points += value;
}
int Character::getLives(){
  return lives;
}
void Character::decrementLives(int value){
  lives -= value;
}

void Character::incrementSpeed(float value){
  speed += value;
}
float Character::getSpeed(){
  return speed;
}
void Character::movement(sf::Event& event){
  if (event.type == sf::Event::KeyPressed){
    switch (event.key.code) {
      case sf::Keyboard::Left:
      case sf::Keyboard::A:
        // left key is pressed: move our character
        sprite.setTexture(left);
        if (currentX - speed >= 0) {
          sprite.move(-1 * speed, 0.f);
          currentX -= speed;
        }
        else{
          setPosition(800-(width/2), currentY);
          currentX = 800-(width/2);
        }
        break;
      case sf::Keyboard::Right:
      case sf::Keyboard::D:
        // right key is pressed: move our character
        sprite.setTexture(right);
        if (currentX + width + speed <= 800) {
          sprite.move(speed, 0.f);
          currentX += speed;
        }
        else{
          setPosition(0-(width/2), currentY);
          currentX = 0-(width/2);
        }
        break;
      case sf::Keyboard::Up:
      case sf::Keyboard::W:
        // up key is pressed: move our character
        sprite.setTexture(up);
        if (currentY - speed >= 0){
          sprite.move(0.f, -1 * speed);
          currentY -= speed;
        }
        else{
          setPosition(currentX, 800-(height/2));
          currentY = 800-(height/2);
        }
        break;
      case sf::Keyboard::Down:
      case sf::Keyboard::S:
        // down key is pressed: move our character
        sprite.setTexture(down);
        if(currentY + height + speed <= 800){
          sprite.move(0.f, speed);
          currentY += speed;
        }
        else{
          setPosition(currentX, 0-(height/2));
          currentY = 0-(height/2);
        }
        break;
      case sf::Keyboard::P:
        lookAtMe();
        points += 69;
        break;
      default:
        lookAtMe();
    }
  }
}

void Character::setPosition(float x, float y){
  currentX = x;
  currentY = y;

  sprite.setPosition(x, y);
}

bool Character::bumpedInto(Character& guy) {
  // check four boundaries
  if (!guy.isBumpable()) {
    return false;
  }

  float this_bottom = currentY + height - 20;
  float this_top = currentY - 20;
  float this_leftmost = currentX + 20;
  float this_rightmost = currentX + width - 20;

  float guy_bottom = guy.getY() + guy.getHeight();
  float guy_top = guy.getY();
  float guy_leftmost = guy.getX();
  float guy_rightmost = guy.getX() + guy.getWidth();

  if (this_bottom >= guy_top) {
    if (this_top <= guy_bottom) {
      if (this_leftmost <= guy_rightmost) {
        if (this_leftmost >= guy_leftmost) {
          lookAtMe();
          return true;
        }
        else if (this_rightmost >= guy_leftmost) {
          lookAtMe();
          return true;
        }
      }
    }
  }

  return false;
}

void Character::lookAtMe(){
  sprite.setTexture(neutral);
}

void Character::setSpeedandDirection(float speed, int direction){
  this->speed = speed;
  this->direction = direction;
}

void Character::strafe() {
  if (fire_texture) {
    sprite.setTexture(left);
    fire_texture = false;
  }
  else{
    sprite.setTexture(neutral);
    fire_texture = true;
  }

  if (currentX > 0 && currentX < 750) {
    sprite.move(direction * speed, 0);
    currentX += direction * speed;
  }
  else{
    direction *= -1;
    sprite.move(direction * speed, 0);
    currentX += direction * speed;
  }
}

bool Character::isInMySpaceX(int x){
  return (x >= this->getX()-(4*this->getSpeed())) && (x <= (this->getX() + this->getWidth() + (4*this->getSpeed())));
}

bool Character::isInMySpaceY(int y){
  return (y <= this->getY() + (4*this->getSpeed())) && (y >= (this->getY() + this->getHeight() + (4*this->getSpeed())));
}
