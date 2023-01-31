#pragma once
#include "Block.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
enum class Direction { left, right, up, down, none };
class Board : public sf::Transformable, public sf::Drawable {
private:
  unsigned int m_window_height, m_window_width;
  int m_block_size;

  Direction dir;

  bool keypressed;
  int keypressed_count;
  int plus, score;
  int m_elements[4][4];

  int is_game_over;
  int random_number;

private:
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;
  void MoveRight();
  void MoveLeft();
  void MoveDown();
  void MoveUp();
  void CheckOver();
  bool Check(int tmp[4][4]);
  void AddBlock();
  void CopyArray(int de[4][4], int sr[4][4]);
  int CountNullNum();
  bool add_block_once;
  bool once;

public:
  Board();
  void initialize(int window_width, int window_height);
  void processEvents(sf::Event &event);
  void processLiveEvents(sf::RenderWindow &window);
  void update();
};
