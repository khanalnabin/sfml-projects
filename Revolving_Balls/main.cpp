#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
const int polygonCount = 9;
sf::Color COLORS[polygonCount];

int I = 0;
class Polygon {
private:
  sf::CircleShape n_gon;
  sf::Vector2u size;
  int pointCount;
  int currentPoint = 0;
  int currentPointIndex = 0;
  int radius;

public:
  Polygon(int radius, int pointCount, sf::Vector2u size)
      : n_gon(radius, pointCount), pointCount(pointCount), radius(radius),
        size(size) {
    if (!(pointCount % 2))
      n_gon.setRotation(180.0f / pointCount);
    n_gon.setOrigin(sf::Vector2f(radius, radius));
    n_gon.setPosition(size.x / 2.0f, size.y / 2.0f);
    n_gon.setOutlineThickness(2);
    n_gon.setOutlineColor(COLORS[I++]);
    n_gon.setFillColor(sf::Color::Transparent);
  }

  sf::CircleShape getPolygon() { return n_gon; }
  std::vector<sf::Vector2f> points;
  sf::Vector2f topmostPoint;

  unsigned getPointCount() { return points.size(); }

  void fillCirclePoints() {
    for (int i = 0; i < points.size(); i++) {
      for (int j = i + 1; j < points.size(); j++) {
        if (points[i].y < size.y / 2) {
          if (points[j].x < points[i].x) {
            sf::Vector2f temp = points[i];
            points[i] = points[j];
            points[j] = temp;
          }
        } else {
          if (points[j].x > points[i].x) {
            sf::Vector2f temp = points[i];
            points[i] = points[j];
            points[j] = temp;
          }
        }
      }
    }

    topmostPoint = sf::Vector2f(0, 1080);
    std::vector<sf::Vector2f> rightPoints;
    std::vector<sf::Vector2f> leftPoints;

    for (int i = 0; i < points.size(); i++) {
      if (points[i].y < topmostPoint.y) {
        topmostPoint = points[i];
      }
      topmostPoint.x = size.x / 2;
      if (points[i].x >= topmostPoint.x) {
        rightPoints.push_back(points[i]);
      } else {
        leftPoints.push_back(points[i]);
      }
    }
    for (int i = 0; i < leftPoints.size(); i++) {
      for (int j = i + 1; j < leftPoints.size(); j++) {
        if (leftPoints[j].y > leftPoints[i].y) {
          sf::Vector2f temp = leftPoints[i];
          leftPoints[i] = leftPoints[j];
          leftPoints[j] = temp;
        }
      }
    }
    for (int i = 0; i < rightPoints.size(); i++) {
      for (int j = i + 1; j < rightPoints.size(); j++) {
        if (rightPoints[j].y < rightPoints[i].y) {
          sf::Vector2f temp = rightPoints[i];
          rightPoints[i] = rightPoints[j];
          rightPoints[j] = temp;
        }
      }
    }
    points.clear();
    points.insert(points.end(), leftPoints.begin(), leftPoints.end());
    points.insert(points.end(), rightPoints.begin(), rightPoints.end());
  }
  sf::CircleShape getCircle() {
    int radius = 6;
    sf::CircleShape circle(6);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(6, 6);
    if (currentPointIndex < points.size()) {
      currentPointIndex += 8;
    } else {
      currentPointIndex = 0;
    }
    circle.setPosition(points[currentPointIndex]);
    // circle.setPosition(sf::Vector2f(960, 393));
    return circle;
  }
};

int main() {
  for (int i = 0; i < polygonCount; i++) {
    COLORS[i] =
        sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
  }
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Revolving Balls",
                          sf::Style::Default, settings);
  window.setFramerateLimit(60);
  sf::Image screen;
  window.setPosition(
      sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
  std::vector<Polygon> polygons;
  sf::Vector2u size = window.getSize();

  for (int i = 0; i < polygonCount; i++) {
    polygons.push_back(Polygon((i + 3) * 20, i + 3, size));
  }
  for (int n = 0; n < polygonCount; n++) {
    window.draw(polygons[n].getPolygon());
  }
  screen = window.capture();
  for (int i = 0; i < screen.getSize().x; i++) {
    for (int j = 0; j < screen.getSize().y; j++) {
      sf::Color color = screen.getPixel(i, j);
      if (color == COLORS[0]) {
        polygons[0].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[1]) {
        polygons[1].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[2]) {
        polygons[2].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[3]) {
        polygons[3].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[4]) {
        polygons[4].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[5]) {
        polygons[5].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[6]) {
        polygons[6].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[7]) {
        polygons[7].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[8]) {
        polygons[8].points.push_back(sf::Vector2f(i, j));
      } else if (color == COLORS[9]) {
        polygons[9].points.push_back(sf::Vector2f(i, j));
      }
    }
  }
  for (int n = 0; n < polygonCount; n++) {
    polygons[n].fillCirclePoints();
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
      }
    }
    sf::CircleShape ss(3);
    ss.setFillColor(sf::Color::White);
    int j = 0;
    window.clear(sf::Color::Black);
    for (int n = 0; n < polygonCount; n++) {
      window.draw(polygons[n].getPolygon());
      window.draw(polygons[n].getCircle());
    }

    window.display();
  }

  return 0;
}
