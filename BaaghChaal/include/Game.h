#pragma once
#include "Board.h"
#include <SFML/Graphics.hpp>

class Game {
public:
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  Game();
  void Run();

private:
  void ProcessEvents();
  void Update(sf::Time);
  void Render();
  sf::RenderWindow m_window;
  Board board;
};
