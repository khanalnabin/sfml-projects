#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
class Baagh : public sf::Drawable, public sf::Transformable {
private:
  sf::Vector2f m_position;
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;
  void mapCoords(sf::Vector2i &mcoords);

public:
  Baagh();
  Baagh(float x, float y);
  Baagh(sf::Vector2f position);
  static bool completed;
  sf::Vector2f GetPosition();
  void ProcessEvents(sf::RenderWindow &window, int elements_array[5][5],
                     int block_size);
};
