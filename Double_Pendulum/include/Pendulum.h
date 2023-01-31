#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
extern const int height;
extern const int width;

class Pendulum : public sf::Transformable, public sf::Drawable {
private:
  float x_one, y_one, x_two, y_two, mass_one, mass_two, length_one, length_two,
      theta_one, theta_two, velocity_one, velocity_two, acceleration_one,
      acceleration_two, px_two, py_two, button_one_x, button_one_y,
      button_two_x, button_two_y, gravity, radius_one, radius_two;
  mutable std::vector<sf::Vector2f> path;
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;
  void mapCoords(sf::Vector2i &mCoords);
  float map(float value, float istart, float istop, float ostart, float ostop);
  sf::Font font;

public:
  Pendulum(float one, float two);
  void update();
  void calculate();
  void setPrev();
  /* void moveSliders(sf::Vector2i); */
  void moveSliders(sf::RenderWindow &window);

  std::vector<sf::Vector2f> getPath();
};
