#include "Snake.h"

// sets the size of a single block of snake
// and calls the reset method
Snake::Snake(int blockSize) {
  size = blockSize;
  bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
  Reset();
}

// Reset method first clears the vector giving rise to a new snake and then adds
// three blocks in the body of the snake , the snake body is composed of snake
// segment which is the struct element having position as  data member
void Snake::Reset() {
  snakeBody.clear();
  snakeBody.push_back(SnakeSegment(5, 7));
  snakeBody.push_back(SnakeSegment(5, 6));
  snakeBody.push_back(SnakeSegment(5, 5));
  SetDirection(Direction::None);
  speed = 5;
  lives = 3;
  score = 0;
  lost = false;
}

void Snake::SetDirection(Direction direction) { dir = direction; }

Direction Snake::GetDirection() {
  if (snakeBody.size() <= 0)
    return Direction::None;
  SnakeSegment &head = snakeBody[0];
  SnakeSegment &neck = snakeBody[1];

  if (head.position.x == neck.position.x) {
    return head.position.y > neck.position.y ? Direction::Down : Direction::Up;
  }
  if (head.position.y == neck.position.y) {
    return head.position.x > neck.position.x ? Direction::Right
                                             : Direction::Left;
  }
  else
      return Direction::None;
}

int Snake::GetSpeed() { return speed; }

sf::Vector2i Snake::GetPosition() {
  return !snakeBody.empty() ? snakeBody.front().position : sf::Vector2i(1, 1);
}

int Snake::GetLives() { return lives; }

int Snake::GetScore() { return score; }

void Snake::IncreaseScore() { score += 10; }

bool Snake::HasLost() { return lost; }

void Snake::Lose() { lost = true; }

void Snake::ToggleLost() { lost = !lost; }

void Snake::Tick() {
  if (snakeBody.empty())
    return;
  if (dir == Direction::None)
    return;
  Move();
  CheckCollision();
}

void Snake::Move() {
  for (int i = snakeBody.size() - 1; i > 0; i--) {
    snakeBody[i].position = snakeBody[i - 1].position;
  }
  if (dir == Direction::Left) {
    --snakeBody[0].position.x;
  }
  if (dir == Direction::Right) {
    ++snakeBody[0].position.x;
  }
  if (dir == Direction::Up) {
    --snakeBody[0].position.y;
  }
  if (dir == Direction::Down) {
    ++snakeBody[0].position.y;
  }
}

void Snake::CheckCollision() {
  if (snakeBody.size() < 5)
    return;
  SnakeSegment &head = snakeBody.front();
  for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr) {
    if (itr->position == head.position) {
      int segments = snakeBody.end() - itr;
      Cut(segments);
      break;
    }
  }
}

void Snake::Cut(int segments) {
  for (int i = 0; i < segments; ++i) {
    snakeBody.pop_back();
  }
  --lives;
  if (!lives) {
    Lose();

    return;
  }
}

void Snake::Render(sf::RenderWindow &window) {
  if (snakeBody.empty())
    return;
  auto head = snakeBody.front();
  bodyRect.setFillColor(sf::Color::Yellow);
  bodyRect.setPosition(head.position.x * size, head.position.y * size);
  window.draw(bodyRect);
  bodyRect.setFillColor(sf::Color::Green);
  for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr) {
    bodyRect.setPosition(itr->position.x * size, itr->position.y * size);
    window.draw(bodyRect);
  }
}


World::World(sf::Vector2u windSize) : windowSize(windSize), blockSize(16) {
  RespawnApple();
  appleShape.setFillColor(sf::Color::Magenta);
  appleShape.setRadius(blockSize / 2);

  for (int i = 0; i < 4; i++) {
    bounds[i].setFillColor(sf::Color(150, 0, 0));
    if (!((i + 1) % 2))
      bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
    else
      bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));
    if (i < 2)
      bounds[i].setPosition(0, 0);
    else {
      bounds[i].setOrigin(bounds[i].getSize());
      bounds[i].setPosition(sf::Vector2f(windSize));
    }
  }
}

World::~World() {}

void World::RespawnApple() {
  int maxX = (windowSize.x / blockSize) - 2;
  int maxY = (windowSize.y / blockSize) - 2;
  item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
  appleShape.setPosition(item.x * blockSize, item.y * blockSize);
}

void World::Update(Snake &player) {
  if (player.GetPosition() == item) {
    player.Extend();
    player.IncreaseScore();
    RespawnApple();
  }
  int gridSize_x = windowSize.x / blockSize;
  int gridSize_y = windowSize.y / blockSize;
  if (player.GetPosition().x < 1 || player.GetPosition().y < 1 ||
      player.GetPosition().x >= gridSize_x - 1 ||
      player.GetPosition().y >= gridSize_y - 1) {
    player.Lose();
  }
}

void World::Render(sf::RenderWindow &window) {
  for (int i = 0; i < 4; ++i) {
    window.draw(bounds[i]);
  }
  window.draw(appleShape);
}

int World::GetBlockSize() { return blockSize; }

void Snake::Extend() {
  if (snakeBody.empty())
    return;
  SnakeSegment &tail_head = snakeBody[snakeBody.size() - 1];
  if (snakeBody.size() > 1) {
    SnakeSegment &tail_bone = snakeBody[snakeBody.size() - 2];

    if (tail_head.position.x == tail_bone.position.x) {
      if (tail_head.position.y > tail_bone.position.y) {
        snakeBody.push_back(
            SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
      } else {
        snakeBody.push_back(
            SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
      }
    } else if (tail_head.position.y == tail_bone.position.y) {
      if (tail_head.position.x > tail_bone.position.x) {
        snakeBody.push_back(
            SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
      } else {
        snakeBody.push_back(
            SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
      }
    }
  } else {
    if (dir == Direction::Up) {
      snakeBody.push_back(
          SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
    } else if (dir == Direction::Down) {
      snakeBody.push_back(
          SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
    } else if (dir == Direction::Right) {
      snakeBody.push_back(
          SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
    } else if (dir == Direction::Left) {
      snakeBody.push_back(
          SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
    }
  }
}


Textbox::Textbox() { Setup(5, 9, 200, sf::Vector2f(0, 0)); }

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos) {
  Setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox() { Clear(); };

void Textbox::Setup(int visible, int charsize, int width,
                    sf::Vector2f screenPos) {
  numVisible = visible;
  sf::Vector2f offset(2.0f, 2.0f);
  font.loadFromFile("arial.ttf");
  content.setFont(font);
  content.setString("");
  content.setCharacterSize(charsize);
  content.setColor(sf::Color::White);
  content.setPosition(screenPos + offset);
  backdrop.setSize(sf::Vector2f(width, 40));
  backdrop.setFillColor(sf::Color::Transparent);
  backdrop.setPosition(screenPos);
}

void Textbox::Add(std::string message, int size) {
  messages.push_back(message);
  if (messages.size() < size)
    return;
  messages.erase(messages.begin());
}

void Textbox::Clear() { messages.clear(); }

void Textbox::Render(sf::RenderWindow &window) {
  std::string m_content;
  for (auto &iter : messages) {
    m_content.append(iter + "\n");
    if (!m_content.empty()) {
      content.setString(m_content);
      window.draw(backdrop);
      window.draw(content);
    }
  }
}
