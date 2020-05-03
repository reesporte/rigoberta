#include "Game.h"
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
Character* makeFireball(Character& rigo){
  /*
  generate fireball character
  */
  int x = 0;
  if (rigo.getX() < 400) {
    x = 749;
  }
  else{
    x = 0;
  }
  /* seed random number generator */
  srand(time(NULL));
  Character* fire = new Character("fire");
  int y = rand() % 750;
  fire->setPosition(x, y);
  fire->setSpeedandDirection(10, -1);

  return fire;
}
Game::Game(){
  /*
  init game function
  */
  SpriteManager::LoadAllSprites();

  rigoberta = Character("rigoberta");
  rigoberta.setPosition(200, 200);

  smiley = Character("poopie");
  smiley.setPosition(400-32, 400-32);
  smiley.setSize(64);

  fireball_counter = 1;
  frames_since_point = 0;
  fireball_timer = 0;
  points_to_win = 69;
  game_over = false;
  winner = false;
}
void Game::setPointsToWin(int value){
  this->points_to_win = value;
}
void Game::deleteFireball() {
  /*
  remove a fireball from vector of fireballs
  */
  Character* last = fireballs.back();
  fireballs.pop_back();
  last->setIsVisible(false);
  if (fireball_counter > 1) {
    fireball_counter -= 1;
  }
  delete last;
}
void Game::didRigobertaGetAPoint(){
  /*
  handle rigoberta's point getting
  */

  /* if she didn't bump into smiley, return */
  if (!rigoberta.bumpedInto(smiley)) {
    return;
  }

  /* runs if rigoberta runs into smiley */
  rigoberta.lookAtMe();
  rigoberta.incrementPoints(1 * fireball_counter);
  rigoberta.incrementSpeed(0.024f);

  /* calculate new position of smiley */
  int x = rand() % 750;
  int y = rand() % 750;
  /* ensures smiley isn't gonna appear too close to rigoberta */
  while (rigoberta.isInMySpaceX(x)) {
    x = rand() % 750;
  }
  while (rigoberta.isInMySpaceY(y)) {
    y = rand() % 750;
  }

  /* hide smiley and move him away */
  smiley.setIsVisible(false);
  smiley.setPosition(x, y);
  smiley.setIsBumpable(false);
  setDisplayNiceJob(true);

  /* points messages */
  if (rigoberta.getPoints() == 69) {
    setText("nicejob", "Nice");
  } else{
    setText("nicejob", "nice job! x" + to_string(fireball_counter));
  }

  setText("pointsToWin", "points to win: " + to_string(points_to_win - rigoberta.getPoints()));

  /* winScreen sound effect */
  if (!isSoundEffectPlaying("good")) {
    playSoundEffect("good");
  }

  /* create a new fireball and increment the speed of the old ones */
  fireballs.push_back(makeFireball(rigoberta));
  for (size_t i = 0; i < fireballs.size(); i++) {
    fireballs[i]->incrementSpeed(2.5f);
  }
  fireball_counter += 1;
}
void Game::didRigobertaLoseAPoint(){
  /*
  handle rigoberta's points
  */
  for (size_t i = 0; i < fireballs.size(); i++) {
    if (rigoberta.bumpedInto(*fireballs[i])) {
      setDisplayNiceJob(true);
      setText("nicejob", "OH NO!");
      rigoberta.lookAtMe();
      rigoberta.decrementLives(1);
      if (!isSoundEffectPlaying("bad")) {
        playSoundEffect("bad");
      }
      fireballs[i]->setIsVisible(false);
      fireballs[i]->setIsBumpable(false);
      if (fireball_counter > 1) {
        fireball_counter -= 1;
      }

    }
    if (i == 0) {
      fireball_timer++;
    }
  }
}
void Game::checkGameOver(){
  /* if rigoberta ran out of lives or got enough points to win */
  if (rigoberta.getLives() <= 0 || rigoberta.getPoints() >= points_to_win) {
    /* our game is over */
    game_over = true;
    /* if she got enough points to win */
    if (rigoberta.getPoints() >= points_to_win) {
      winner = true;
    }else{
      winner = false;
    }
    /* make her look at you */
    rigoberta.lookAtMe();
    /* remove fireball pointers */
    int size = fireballs.size();
    for (size_t i = 0; i < size; i++) {
      deleteFireball();
    }
    setDisplayNiceJob(false);
    frames_since_point = 0;
    stopMusic("background");
  }
}
void Game::drawUpdates(sf::RenderWindow& window){
  if (smiley.isVisible()) {
    window.draw(smiley.getSprite());
  }
  if (rigoberta.isVisible()) {
    window.draw(rigoberta.getSprite());
  }
  for (size_t i = 0; i < fireballs.size(); i++) {
    if (fireballs[i]->isVisible()) {
      fireballs[i]->strafe();
      window.draw(fireballs[i]->getSprite());
    }
  }
}
void Game::restartGame(){
  game_over = false;
  rigoberta.decrementLives(rigoberta.getLives());
  rigoberta.decrementLives(-3);
  rigoberta.incrementPoints(-1 * rigoberta.getPoints());
  setText("help", "[W A S D]: move\n[R]: restart\n[esc]: back to menu");
  stopMusic("background");
  if (winner) {
    stopMusic("win");
  }
  else{
    stopMusic("loser");
  }
  smiley.setIsVisible(true);
  smiley.setIsBumpable(true);
  fireball_timer = 0;
  frames_since_point = 0;
  int size = fireballs.size();
  for (size_t i = 0; i < size; i++) {
    deleteFireball();
  }
}
/*
      M U S I C
*/
void Game::setUpMusic() {
  /*
  loads background music, loser music, and winner music
  */
  if ( !background.openFromFile("resources/sounds/music.wav") ) {
    return;
  }
  background.setVolume(50);
  background.setLoop(true);

  if ( !loser.openFromFile("resources/sounds/loser.wav") ) {
    return;
  }
  loser.setVolume(50);
  loser.setLoop(true);

  if ( !win.openFromFile("resources/sounds/start.wav") ) {
    return;
  }
  win.setVolume(50);
  win.setLoop(true);

  if ( !start.openFromFile("resources/sounds/winner.wav") ) {
    return;
  }
  start.setVolume(50);
  start.setLoop(true);
  start.play();
}
bool Game::isMusicPlaying(string type) {
  if (type == "background") {
    return (background.getStatus() == sf::Music::Playing);
  }
  else if (type == "loser") {
    return (loser.getStatus() == sf::Music::Playing);
  }
  else if (type == "win") {
    return (win.getStatus() == sf::Music::Playing);
  }
  else if (type == "start") {
    return (start.getStatus() == sf::Music::Playing);
  }
  else{
    return false;
  }
}
void Game::playMusic(string type){
  if (type == "background") {
    background.play();
  }
  else if (type == "loser") {
    loser.play();
  }
  else if (type == "win") {
    win.play();
  }
  else if (type == "start") {
    start.play();
  }
}
void Game::stopMusic(string type){
  if (type == "background") {
    background.stop();
  }
  else if (type == "loser") {
    loser.stop();
  }
  else if (type == "win") {
    win.stop();
  }
  else if (type == "start") {
    start.stop();
  }
}
/*
    S O U N D    E F F E C T S
*/
void Game::setUpSoundEffects() {
  /*
  loads sound effects
  */
  if ( !goodbuffer.loadFromFile("resources/sounds/oof.wav") ) {
    std::cout << "oof soundfile not loaded" << '\n';
    return;
  }
  good.setBuffer(goodbuffer);
  good.setVolume(20);

  if ( !badbuffer.loadFromFile("resources/sounds/bad.wav") ) {
    std::cout << "loseScreen soundfile not loaded" << '\n';
    return;
  }
  bad.setBuffer(badbuffer);
  bad.setVolume(20);

}
bool Game::isSoundEffectPlaying(string type) {
  if (type == "good") {
    return (good.getStatus() == sf::Music::Playing);
  }
  else if (type == "bad") {
    return (bad.getStatus() == sf::Music::Playing);
  }
  else{
    return false;
  }
}
void Game::playSoundEffect(string type){
  if (type == "good") {
    good.play();
  }
  else if (type == "bad") {
    bad.play();
  }
}
/*
      T E X T
*/
bool Game::displayNiceJob(){
  /*
  returns whether or not the NiceJob msg should be displayed
  */
  return display_NiceJob;
}
void Game::setDisplayNiceJob(bool value){
  display_NiceJob = value;
}
void Game::setUpText(){
  /* load in font */
  if ( !font.loadFromFile("resources/fonts/Baskerville.ttc")) {
    std::cout << "error loading font" << '\n';
    return;
  }
  /* points to win */
  pointsToWin.setFont(font);
  pointsToWin.setCharacterSize(30);
  pointsToWin.setFillColor(sf::Color::White);
  pointsToWin.setPosition(500, 0);
  pointsToWin.setString("points to win: " + to_string(points_to_win));
  /* lives text */
  lives.setFont(font);
  lives.setCharacterSize(30);
  lives.setFillColor(sf::Color::White);
  lives.setPosition(15, 0);
  lives.setString("lives: 3");
  /* points text */
  points.setFont(font);
  points.setCharacterSize(50);
  points.setFillColor(sf::Color::White);
  points.setPosition(15, 25);
  /* nicejob text */
  nicejob.setFont(font);
  nicejob.setCharacterSize(69);
  nicejob.setFillColor(sf::Color::White);
  nicejob.setPosition(230, 75);
  /* help text */
  help.setFont(font);
  help.setCharacterSize(20);
  help.setFillColor(sf::Color::White);
  help.setPosition(625, 800-78);
  help.setString("[W A S D]: move\n[R]: restart\n[esc]: back to menu");

}
void Game::setText(string type, string text) {
  if (type == "nicejob") {
    nicejob.setString(text);
  }
  else if (type == "points") {
    points.setString(text);
  }
  else if (type == "pointsToWin") {
    pointsToWin.setString(text);
  }
  else if (type == "lives") {
    lives.setString(text);
  }
  else if (type == "help") {
    help.setString(text);
  }
}
void Game::drawText(sf::RenderWindow &window) {
  if (display_NiceJob) {
    window.draw(nicejob);
  }
  window.draw(points);
  window.draw(help);
  if (!game_over) {
    window.draw(pointsToWin);
  }
  window.draw(lives);
}
/*
/////////////////////////////////////
        M A I N     L O O P
/////////////////////////////////////
*/
int Game::mainLoop(sf::RenderWindow& window){
  while(window.isOpen()){
    if (!game_over) {
      /* if the music isn't already playing, play it */
      if (!isMusicPlaying("background")) {
        playMusic("background");
      }
      checkGameOver();
      /* check if points are added */
      setText("points", "points: " + to_string(rigoberta.getPoints()));
      setText("pointsToWin", "points to win: " + to_string(points_to_win - rigoberta.getPoints()));
      /* check if lives have changed */
      setText("lives", "lives: " + to_string(rigoberta.getLives()));
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed){
              window.close();
              return -1; // exit game
          }
          if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            restartGame();
          }
          if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
              restartGame();
              setPointsToWin(69);
              return 0; // return to menu
          }
          rigoberta.movement(event); // handle movement here
      }
      /* collision check! */
      didRigobertaGetAPoint();
      didRigobertaLoseAPoint();

      window.clear();
      /* draw updates */
      drawUpdates(window);

      if (fireball_timer == 150) {
        /* every 150 frames (~10 seconds), remove a fireball */
        deleteFireball();
        fireball_timer = 0;
      }
      /* if you did a nice job */
      if (displayNiceJob()) {
        frames_since_point++;
      }

      /* points, lives, help message */
      drawText(window);

      if (frames_since_point == 30) {
        setDisplayNiceJob(false);
        smiley.setIsVisible(true);
        smiley.setIsBumpable(true);

        frames_since_point = 0;
      }
      window.display();
    }

    /* if the game is over */
    else{
      /* update points and help msg*/
      setText("points", "points: " + to_string(rigoberta.getPoints()));
      /* if the music isn't already playing, play it */
      if (winner){
        if (!isMusicPlaying("win")) {
          playMusic("win");
        }
      }
      else{
        if (!isMusicPlaying("loser")) {
          playMusic("loser");
        }
      }
      /* create win/loss screen background sprite */
      if (winner) {
        SpriteManager::LoadSprite("winner", "screen");
        winScreen = SpriteManager::GetSprite("winner", "screen");
        winScreen.setTextureRect(sf::IntRect(0, 0, TextureManager::GetTexture("winner", "screen").getSize().x, TextureManager::GetTexture("winner", "screen").getSize().y));
        winScreen.setPosition(0, 70);
      }else{
        SpriteManager::LoadSprite("loser", "screen");
        loseScreen = SpriteManager::GetSprite("loser", "screen");
        loseScreen.setTextureRect(sf::IntRect(0, 0, TextureManager::GetTexture("loser", "screen").getSize().x, TextureManager::GetTexture("loser", "screen").getSize().y));
      }

      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed){
              window.close();
              return -1; // exit
          }
          if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
              restartGame();
          if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
              restartGame();
              setPointsToWin(69);
              return 0; // return to menu
          }
          rigoberta.movement(event); /* let rigoberta move around in the loser/winner screen */
      }

      window.clear();
      if (winner) {
        window.draw(winScreen);
      }else{
        window.draw(loseScreen);
      }
      window.draw(rigoberta.getSprite());
      drawText(window);
      window.display();
    }
  }
  return -1; // exit game loop
}
