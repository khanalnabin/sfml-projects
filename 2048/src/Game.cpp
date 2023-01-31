#include "../include/Game.h"
#include <X11/Xlib.h>

Game::Game() {
  Display *d = XOpenDisplay(nullptr);
  Screen *s = DefaultScreenOfDisplay(d);

  unsigned int window_width = s->width;
  unsigned int window_height = s->height;

  m_game_width = window_width / 2.5f;
  m_game_height = m_game_width;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  m_window.create(sf::VideoMode(m_game_width, m_game_height), "Your Own 2048",
                  sf::Style::Default, settings);
  board.initialize(m_game_width, m_game_height);
}

void Game::run() {
  while (m_window.isOpen()) {
    ProcessEvents();
    Update();
    Render();
  }
}
void Game::Update() { board.update(); }

void Game::ProcessEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      m_window.close();
    }
    board.processEvents(event);
  }
}

void Game::Render() {
  m_window.clear(sf::Color::Black);
  m_window.draw(board);
  m_window.display();
}
