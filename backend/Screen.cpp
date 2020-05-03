#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Screen.h"
int Screen::Run(sf::RenderWindow& window, Game& game, int type){

  if (!game.isMusicPlaying("start")) {
    game.playMusic("start");
  }
  if(type == 0){
    sf::Font font;
    if ( !font.loadFromFile("resources/fonts/Baskerville.ttc")) {
      std::cout << "error loading font" << '\n';
      return -1; // exit game
    }
    sf::Text start_text;
    start_text.setFont(font);
    start_text.setCharacterSize(55);
    start_text.setFillColor(sf::Color::White);
    start_text.setPosition(15, 150 + 225);
    start_text.setString("Select Mode: \n[\t1) Easy\t\t]\t69 points\n \t2) Medium\t\n \t3) Hard\t");

    sf::Text pressenter;
    pressenter.setFont(font);
    pressenter.setCharacterSize(30);
    pressenter.setFillColor(sf::Color::White);
    pressenter.setPosition(80, 415 + 225);
    pressenter.setString("Press [enter] to start");

    sf::Text credits;
    credits.setFont(font);
    credits.setCharacterSize(20);
    credits.setFillColor(sf::Color::White);
    credits.setPosition(30, 100);
    credits.setString("a game by reese porter");

    sf::Sprite start_screen;
    SpriteManager::LoadSprite("start", "screen");
    start_screen = SpriteManager::GetSprite("start", "screen");
    start_screen.setTextureRect(sf::IntRect(0, 0, TextureManager::GetTexture("start", "screen").getSize().x, TextureManager::GetTexture("start", "screen").getSize().y));
    start_screen.setPosition(0, 0);

    sf::Sprite rigo = SpriteManager::GetSprite("rigoberta", "neutral");
    rigo.setPosition(400-(TextureManager::GetTexture("rigoberta", "neutral").getSize().x)+35, 150);

    while(window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
          return -1; // exit game
        }
        if (event.type == sf::Event::KeyPressed) {
          if(event.key.code == sf::Keyboard::Num1){
            game.setPointsToWin(69);
            start_text.setString("Select Mode: \n[\t1) Easy\t\t]\t69 points\n \t2) Medium\t\n \t3) Hard\t");
          }else if(event.key.code == sf::Keyboard::Num2){
            game.setPointsToWin(100);
            start_text.setString("Select Mode: \n \t1) Easy\t\n[\t2) Medium\t]\t100 points\n \t3) Hard\t");
          }else if(event.key.code == sf::Keyboard::Num3){
            game.setPointsToWin(420);
            start_text.setString("Select Mode: \n \t1) Easy\t\n \t2) Medium\t\n[\t3) Hard\t\t]\t420 points");
          }else if (event.key.code == sf::Keyboard::Enter) {
            return 1; // move to game loop
          }
        }
      }
      window.clear();
      window.draw(start_screen);
      window.draw(credits);
      window.draw(rigo);
      window.draw(start_text);
      window.draw(pressenter);
      window.display();
    }
    return 1; // move to game loop
  }
  else if(type == 1){
    game.stopMusic("start");
    return game.mainLoop(window);
  }
  // shouldn't ever get here
  return -1;
}
