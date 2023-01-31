#include "Pendulum.h"
#include <cmath>
#include <string>
Pendulum::Pendulum(float a, float b) {
  length_one = 200.0f;
  length_two = 200.0f;

  mass_one = 10.0f;
  mass_two = 10.0f;

  theta_one = a;
  theta_two = b;

  velocity_one = 0.0f;
  velocity_two = 0.0f;

  acceleration_one = 0.0f;
  acceleration_two = 0.0f;

  radius_one = map(mass_one, 10, 100, 5, 8);
  radius_two = map(mass_two, 10, 100, 5, 8);

  x_one = length_one * sin(theta_one);
  y_one = length_one * cos(theta_one);

  x_two = length_two * sin(theta_two) + x_one;
  y_two = length_two * cos(theta_two) + y_one;

  button_one_x = -100;
  button_one_y = 600;

  button_two_x = -100;
  button_two_y = 700;
  gravity = 1.0f;

  font.loadFromFile("arial.ttf");

  path.push_back(sf::Vector2f(x_two, y_two));
}

void Pendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.transform.translate(sf::Vector2f(width / 2.0f, 220));

  sf::VertexArray line_one(sf::Lines, 2);
  line_one[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::White);
  line_one[1] = sf::Vertex(sf::Vector2f(x_one, y_one), sf::Color::White);

  sf::VertexArray line_two(sf::Lines, 2);
  line_two[0] = sf::Vertex(sf::Vector2f(x_one, y_one), sf::Color::White);
  line_two[1] = sf::Vertex(sf::Vector2f(x_two, y_two), sf::Color::White);

  sf::CircleShape circle_one(radius_one, 20);
  circle_one.setFillColor(sf::Color::Red);
  circle_one.setPosition(sf::Vector2f(x_one, y_one));
  circle_one.setOrigin(radius_one, radius_one);

  sf::CircleShape circle_two(radius_two, 20);
  circle_two.setFillColor(sf::Color::Red);
  circle_two.setPosition(sf::Vector2f(x_two, y_two));
  circle_two.setOrigin(radius_two, radius_two);

  sf::Vector2f lastp = path[0];
  for (auto p : path) {
    sf::Vertex line[] = {sf::Vertex(lastp, sf::Color::White),
                         sf::Vertex(p, sf::Color::White)};
    target.draw(line, 2, sf::Lines, states);
    lastp = p;
  }

  sf::CircleShape center(5, 20);
  center.setPosition(0, 0);
  center.setOrigin(5, 5);
  center.setFillColor(sf::Color::Blue);

  sf::RectangleShape back_one(sf::Vector2f(200, 10));
  back_one.setFillColor(sf::Color::Magenta);
  back_one.setPosition(-100, 600);

  sf::CircleShape button_one(10, 20);
  button_one.setOrigin(10, 10);
  button_one.setPosition(button_one_x, back_one.getPosition().y + 5);
  button_one.setFillColor(sf::Color::White);

  sf::RectangleShape back_two(sf::Vector2f(200, 10));
  back_two.setFillColor(sf::Color::Magenta);
  back_two.setPosition(-100, 700);

  sf::CircleShape button_two(10, 20);
  button_two.setOrigin(10, 10);
  button_two.setPosition(button_two_x, back_two.getPosition().y + 5);
  button_two.setFillColor(sf::Color::White);

  sf::Text grav;
  grav.setFont(font);
  grav.setFillColor(sf::Color::White);
  grav.setCharacterSize(20);

  grav.setString("Mass One: " + std::to_string(mass_one));
  grav.setPosition(-100, back_one.getPosition().y + 20);
  target.draw(grav, states);

  grav.setString("Mass Two: " + std::to_string(mass_two));
  grav.setPosition(-100, back_two.getPosition().y + 20);
  target.draw(grav, states);

  grav.setString("Gravity: " + std::to_string(gravity));
  grav.setPosition(-width / 2.0f, 400);
  target.draw(grav, states);

  grav.setString("Velocity One: " + std::to_string(velocity_one));
  grav.setPosition(-width / 2.0f, 440);
  target.draw(grav, states);

  grav.setString("Velocity two: " + std::to_string(velocity_two));
  grav.setPosition(-width / 2.0f, 480);
  target.draw(grav, states);

  grav.setString("Acceleration One: " + std::to_string(acceleration_one));
  grav.setPosition(-width / 2.0f, 520);
  target.draw(grav, states);

  grav.setString("Acceleration two: " + std::to_string(acceleration_two));
  grav.setPosition(-width / 2.0f, 560);
  target.draw(grav, states);
  grav.setString("Length One: " + std::to_string(length_one));
  grav.setPosition(-width / 2.0f, 600);
  target.draw(grav, states);

  grav.setString("Length Two: " + std::to_string(length_two));
  grav.setPosition(-width / 2.0f, 640);
  target.draw(grav, states);

  grav.setString("Theta One " + std::to_string(theta_one * 180 / M_PI));
  grav.setPosition(-width / 2.0f, 680);
  target.draw(grav, states);

  grav.setString("Theta Two " + std::to_string(theta_two * 180 / M_PI));
  grav.setPosition(-width / 2.0f, 720);
  target.draw(grav, states);

  target.draw(line_one, states);
  target.draw(line_two, states);
  target.draw(center, states);
  target.draw(back_one, states);
  target.draw(back_two, states);
  target.draw(button_one, states);
  target.draw(button_two, states);
  target.draw(circle_one, states);
  target.draw(circle_two, states);
}

void Pendulum::update() {
  calculate();
  velocity_one += acceleration_one;
  velocity_two += acceleration_two;

  theta_one += velocity_one;
  theta_two += velocity_two;

  x_one = length_one * sin(theta_one);
  y_one = length_one * cos(theta_one);

  x_two = length_two * sin(theta_two) + x_one;
  y_two = length_two * cos(theta_two) + y_one;

  path.push_back(sf::Vector2f(x_two, y_two));
  if(path.size() > 200)
      path.erase(path.begin());

}

void Pendulum::calculate() {
  float num =
      -gravity * (2 * mass_one + mass_two) * sin(theta_one) -
      mass_two * gravity * sin(theta_one - 2 * theta_two) -
      2 * sin(theta_one - theta_two) * mass_two *
          (pow(velocity_two, 2) * length_two +
           pow(velocity_one, 2) * length_one * cos(theta_one - theta_two));
  float den = length_one * (2 * mass_one + mass_two -
                            mass_two * cos(2 * theta_one - 2 * theta_two));
  acceleration_one = num / den;

  num = 2 * sin(theta_one - theta_two) *
        (pow(velocity_one, 2) * length_one * (mass_one + mass_two) +
         gravity * (mass_one + mass_two) * cos(theta_one) +
         pow(velocity_two, 2) * length_two * mass_two *
             cos(theta_one - theta_two));
  den = length_two * (2 * mass_one + mass_two -
                      mass_two * cos(2 * theta_one - 2 * theta_two));

  acceleration_two = num / den;
}

void Pendulum::setPrev() {
  px_two = x_two;
  py_two = y_two;
}

std::vector<sf::Vector2f> Pendulum::getPath() { return path; }

void Pendulum::mapCoords(sf::Vector2i &mcoords) {
  mcoords.x -= width / 2.0f;
  mcoords.y -= 220;
}
void Pendulum::moveSliders(sf::RenderWindow &window) {
  sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
  mapCoords(mousePosition);
  sf::Vector2f center{0, 0};
  bool changed = false;

  if (mousePosition.x <= x_one + 5 && mousePosition.x >= x_one - 5 &&
      mousePosition.y <= y_one + 5 && mousePosition.y >= y_one - 5) {
    while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
      mapCoords(mousePosition);
      x_one = mousePosition.x;
      y_one = mousePosition.y;

      changed = true;
    }
  } else if (mousePosition.x <= x_two + 5 && mousePosition.x >= x_two - 5 &&
             mousePosition.y <= y_two + 5 && mousePosition.y >= y_two - 5) {
    while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
      mapCoords(mousePosition);
      x_two = mousePosition.x;
      y_two = mousePosition.y;

      changed = true;
    }
  } else if (mousePosition.x <= button_one_x + 10 &&
             mousePosition.x >= button_one_x - 10 &&
             mousePosition.y <= button_one_y + 10 &&
             mousePosition.y >= button_one_y - 10) {
    while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
      mapCoords(mousePosition);
      button_one_x = mousePosition.x;
      if (button_one_x > 100)
        button_one_x = 100;
      else if (button_one_x < -100)
        button_one_x = -100;

      mass_one = map(button_one_x, -100, 100, 10, 100);
      changed = true;
    }
  } else if (mousePosition.x <= button_two_x + 10 &&
             mousePosition.x >= button_two_x - 10 &&
             mousePosition.y <= button_two_y + 10 &&
             mousePosition.y >= button_two_y - 10) {
    while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
      mapCoords(mousePosition);
      button_two_x = mousePosition.x;
      if (button_two_x > 100)
        button_two_x = 100;
      else if (button_two_x < -100)
        button_two_x = -100;

      mass_two = map(button_two_x, -100, 100, 10, 100);
      changed = true;
    }
  }

  if (changed) {
    length_one = sqrt(pow((x_one - center.x), 2) + pow((y_one - center.y), 2));
    length_two = sqrt(pow((x_two - x_one), 2) + pow((y_two - y_one), 2));

    theta_one = asin(x_one / length_one);
    theta_two = asin((x_two - x_one) / length_two);

    velocity_one = 0.0f;
    velocity_two = 0.0f;

    acceleration_one = 0.0f;
    acceleration_two = 0.0f;
    radius_one = map(mass_one, 10, 100, 5, 8);
    radius_two = map(mass_two, 10, 100, 5, 8);
    path.clear();
    path[0] = sf::Vector2f(x_two, y_two);
  }

  changed = false;
}
float Pendulum::map(float value, float istart, float istop, float ostart,
                    float ostop) {
  return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
