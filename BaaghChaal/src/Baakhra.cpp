#include "Baakhra.h"
Baakhra::Baakhra() : m_position(sf::Vector2f(0, 0)) {}
Baakhra::Baakhra(float x, float y) { m_position = sf::Vector2f(x, y); }

Baakhra::Baakhra(sf::Vector2f position) { m_position = position; };
bool Baakhra::completed = false;

void Baakhra::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  sf::Texture baakhra_texture;

  baakhra_texture.loadFromFile("assets/images/goat_final.png");
  sf::Sprite baakhra_sprite;
  baakhra_sprite.setTexture(baakhra_texture);
  baakhra_sprite.setPosition(m_position);
  baakhra_sprite.setOrigin(baakhra_texture.getSize().x / 2.0f,
                           baakhra_texture.getSize().y / 2.0f);
  target.draw(baakhra_sprite, states);
}

sf::Vector2f Baakhra::GetPosition() const { return m_position; }

void Baakhra::mapCoords(sf::Vector2i &mcoords) {
  mcoords.x -= 90;
  mcoords.y -= 60;
}
void Baakhra::ProcessEvents(sf::RenderWindow &window, int (*elements_array)[5],
                            int block_size) {
  if (!Baakhra::completed) {
    bool changed = false;
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    mapCoords(mouse_position);
    sf::Vector2i temp_position;
    int i = 0;
    if (mouse_position.x >= m_position.x - 50 &&
        mouse_position.x <= m_position.x + 50 &&
        mouse_position.y >= m_position.y - 50 &&
        mouse_position.y <= m_position.y + 50) {
      while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        mapCoords(mouse_position);
        temp_position.x = mouse_position.x;
        temp_position.y = mouse_position.y;
        changed = true;
      }
    }
    sf::Vector2i index(m_position.x / block_size, m_position.y / block_size);
    if (changed) {

      for (int rows = 0; rows < 5; rows++) {
        for (int columns = 0; columns < 5; columns++) {
          if (temp_position.x >= columns * block_size - 50 &&
              temp_position.x <= columns * block_size + 50 &&
              temp_position.y >= rows * block_size - 50 &&
              temp_position.y <= rows * block_size + 50) {
            if (abs(columns - index.x) <= 1 && abs(rows - index.y) <= 1) {
              if ((index.x + index.y) % 2 == 0) {
                if (elements_array[rows][columns] == 0) {
                  elements_array[rows][columns] = 1;
                  elements_array[index.y][index.x] = 0;
                  m_position =
                      sf::Vector2f(columns * block_size, rows * block_size);
                  Baakhra::completed = true;
                }
              } else {
                if (abs(columns - index.x) == 0 || abs(rows - index.y) == 0) {
                  if (elements_array[rows][columns] == 0) {
                    elements_array[rows][columns] = 1;
                    elements_array[index.y][index.x] = 0;
                    m_position =
                        sf::Vector2f(columns * block_size, rows * block_size);
                    Baakhra::completed = true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
