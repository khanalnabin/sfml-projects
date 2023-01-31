#pragma once
#include "Graphics.hpp"
class Application{
public:
  Application(const Application &) = delete;
  Application &operator=(const Application &) = delete;
  Application();
  void run();

private:
  void processEvents();
  void update();
  void render();
  sf::RenderWindow window;
  Graphics graphics;
};
