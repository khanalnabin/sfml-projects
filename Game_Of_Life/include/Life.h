#ifndef LIFE_H
#define LIFE_H
#include <SFML/Graphics.hpp>
const int height = 1080;
const int width = 1920;

const int block_size = 15;
const int rows = height / block_size;
const int columns = width / block_size;

class Life : public sf::Transformable, public sf::Drawable {
private:
  int grid[rows][columns]{0};
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;
  int check_lives(int r, int c);

public:
  Life();
  void update(sf::Time dt);
  void fill(sf::Vector2i coords);
  void unfill(sf::Vector2i coords);
  void reset();
};

#endif
