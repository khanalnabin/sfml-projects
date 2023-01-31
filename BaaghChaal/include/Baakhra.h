#pragma once
#include <SFML/Graphics.hpp>
class Baakhra : public sf::Drawable, public sf::Transformable {
private:
  sf::Vector2f m_position;
  int count;
  void mapCoords(sf::Vector2i &mcoords);
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;

public:
  Baakhra();
  Baakhra(float x, float y);
  Baakhra(sf::Vector2f position);
  static bool completed;
  /* static int eaten_baakhras; */
  sf::Vector2f GetPosition() const;

  void Update();
  void ProcessEvents(sf::RenderWindow &window, int elements_array[5][5],
                     int block_size);
};
