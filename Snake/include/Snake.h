//
// Created by Nabin on 5/17/21.
//

#ifndef SFML_SNAKE_SNAKE_H
#define SFML_SNAKE_SNAKE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct SnakeSegment {
  SnakeSegment(int x, int y) : position(x, y) {}

  sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;
using MessageContainer = std::vector<std::string>;

enum Direction { None, Up, Down, Left, Right };

class Snake {
private:
  void CheckCollision(); // Checking for collisions

  SnakeContainer snakeBody;    // Segment Vector
  int size;                    // Size of the graphics
  Direction dir;               // Current direction
  int speed;                   // Speed of Snake
  int lives;                   // Lives
  int score;                   // Score
  bool lost;                   // Losing State
  sf::RectangleShape bodyRect; // Shape used for rendering
public:
  Snake(int blockSize);

  // Helper Methods
  void SetDirection(Direction direction);

  Direction GetDirection();

  int GetSpeed();

  sf::Vector2i GetPosition();

  int GetLives();

  int GetScore();

  void IncreaseScore();

  bool HasLost();

  void Lose(); // Handle Losing

  void ToggleLost();

  void Extend(); // Grow the snake

  void Reset(); // Reset to starting position

  void Move(); // Movement method

  void Tick(); // Update method

  void Cut(int segments); // method for cutting snake

  void Render(sf::RenderWindow &window);
};

class Textbox {
private:
  MessageContainer messages;
  int numVisible;
  sf::RectangleShape backdrop;
  sf::Font font;
  sf::Text content;

public:
  Textbox();

  Textbox(int visible, int charSize, int width, sf::Vector2f screenPos);

  ~Textbox();

  void Setup(int visible, int charsize, int width, sf::Vector2f screenPos);

  void Add(std::string message, int size);

  void Clear();

  void Render(sf::RenderWindow &wind);
};

class World {
private:
  sf::Vector2u windowSize;
  sf::Vector2i item;
  int blockSize;
  sf::CircleShape appleShape;
  sf::RectangleShape bounds[4];

public:
  World(sf::Vector2u windSize);

  ~World();

  int GetBlockSize();

  void RespawnApple();

  void Update(Snake &player);

  void Render(sf::RenderWindow &window);
};
#endif // SFML_SNAKE_SNAKE_H
