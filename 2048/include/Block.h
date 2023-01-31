#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Block : public sf::Drawable, public sf::Transformable {
private:
  sf::RectangleShape m_block;
  static sf::Color colors[12];
  sf::Font font;
  sf::Text m_text;
  int m_value, m_block_size;
  sf::Vector2f m_index, m_position;
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;

public:
  Block(int block_size, sf::Vector2f index, int value);
};
