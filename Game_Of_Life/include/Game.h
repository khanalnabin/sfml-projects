#ifndef BLUEPRINTS_GAME_H
#define BLUEPRINTS_GAME_H
#include "Life.h"
#include <SFML/Graphics.hpp>
class Game {
public:
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  Game();
  void run(int);

private:
  void processEvents();
  void update(sf::Time);
  void render();
  sf::RenderWindow Window;
  Life life;
  bool start = false;
};
#endif
