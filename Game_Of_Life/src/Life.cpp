#include "Life.h"
#include <SFML/System/Vector2.hpp>
#include <cstring>
#include <iostream>
Life::Life() {}

void Life::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (int r = 0; r < height; r += block_size) {
    sf::VertexArray vert(sf::Lines, 2);
    vert[0] = sf::Vertex(sf::Vector2f(0, r));
    vert[0].color = sf::Color(100, 100, 100);
    vert[1] = sf::Vertex(sf::Vector2f(width, r));
    vert[1].color = sf::Color(100, 100, 100);
    target.draw(vert, states);
  }
  for (int c = 0; c < columns; c++) {
    sf::VertexArray vert(sf::Lines, 2);
    vert[0].position = sf::Vector2f(c * block_size, 0);
    vert[0].color = sf::Color(100, 100, 100);
    vert[1].position = sf::Vector2f(c * block_size, height);
    vert[1].color = sf::Color(100, 100, 100);
    target.draw(vert, states);
  }
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < columns; x++) {
      if (grid[y][x]) {
        sf::RectangleShape rect(sf::Vector2f(block_size, block_size));
        rect.setOutlineThickness(1.0f);
        rect.setOutlineColor(sf::Color::Black);
        rect.setPosition(x * block_size, y * block_size);
        target.draw(rect, states);
      }
    }
  }
}

void Life::fill(sf::Vector2i coords) {
  int x = coords.x / block_size;
  int y = coords.y / block_size;
  grid[y][x] = 1;
}
void Life::unfill(sf::Vector2i coords) {
  int x = coords.x / block_size;
  int y = coords.y / block_size;
  grid[y][x] = 0;
}

void Life::update(sf::Time dt) {
  int newGrid[rows][columns];
  std::memcpy(newGrid, grid, rows * columns * sizeof(int));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int lives = check_lives(i, j);
      if (lives == 3)
        newGrid[i][j] = 1;
      else if (lives > 3 || lives < 2)
        newGrid[i][j] = 0;
    }
  }
  std::memcpy(grid, newGrid, rows * columns * sizeof(int));
}

int Life::check_lives(int r, int c) {
  /* return random() % 2 + 3; */
  int lives = 0;
  /* if (r - 1 > 0 && grid[r - 1][c] == 1) */
  /*   lives++; */
  /* if ((r - 1 > 0 && c - 1 > 0) && grid[r - 1][c - 1] == 1) */
  /*   lives++; */
  /* if (c - 1 > 0 && grid[r][c - 1] == 1) */
  /*   lives++; */
  /* if ((c - 1 > 0 && r + 1 < rows) && grid[r + 1][c - 1] == 1) */
  /*   lives++; */
  /* if (r + 1 < rows && grid[r + 1][c] == 1) */
  /*   lives++; */
  /* if ((r + 1 < rows && c + 1 < columns) && grid[r + 1][c + 1] == 1) */
  /*   lives++; */
  /* if (c + 1 < rows && grid[r][c + 1] == 1) */
  /*   lives++; */
  /* if ((r - 1 > 0 && c + 1 < columns) && grid[r - 1][c + 1] == 1) */
  /*   lives++; */

  if (grid[r - 1][c] == 1)
    lives++;
  if (grid[r - 1][c - 1] == 1)
    lives++;
  if (grid[r][c - 1] == 1)
    lives++;
  if (grid[r + 1][c - 1] == 1)
    lives++;
  if (grid[r + 1][c] == 1)
    lives++;
  if (grid[r + 1][c + 1] == 1)
    lives++;
  if (grid[r][c + 1] == 1)
    lives++;
  if (grid[r - 1][c + 1] == 1)
    lives++;

  return lives;
}
