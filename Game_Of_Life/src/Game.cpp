#include "Game.h"
#include <SFML/Window/Mouse.hpp>

Game::Game() : Window(sf::VideoMode(1360, 720), "opengl-Conway's Game Of Life") {}

void Game::run(int minimum_frame_per_seconds) {
  Window.setFramerateLimit(5);
  sf::Clock clock;
  sf::Time timeSinceLastUpdate;
  sf::Time TimePerFrame = sf::seconds(1.f / minimum_frame_per_seconds);
  while (Window.isOpen()) {
    processEvents();
    timeSinceLastUpdate = clock.restart();
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      update(TimePerFrame);
    }
    update(timeSinceLastUpdate);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (Window.pollEvent(event)) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
        event.type == sf::Event::Closed) {
      Window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      start = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      start = false;
    }
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    life.fill(sf::Mouse::getPosition(Window));
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
      sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
    life.unfill(sf::Mouse::getPosition(Window));
  }
}
void Game::update(sf::Time deltaTime) {
  if (start)
    life.update(deltaTime);
}
void Game::render() {
  Window.clear(sf::Color::Black);
  Window.draw(life);
  Window.display();
}
