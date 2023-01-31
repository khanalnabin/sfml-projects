#include "Game.h"
Game::Game()
    : m_window(sf::VideoMode(1320, 768), "Baagh Chaal",
               sf::Style::Close | sf::Style::Titlebar) {
	m_window.setPosition(sf::Vector2i(0, 0));
}

void Game::Run() {
	sf::Clock clock;
	sf::Time time;

	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
			    event.type == sf::Event::Closed)
				m_window.close();
		}
		time = clock.restart();
		Game::ProcessEvents();
		Update(time);
		Render();
	}
}

void Game::ProcessEvents() { board.ProcessEvents(m_window); }

void Game::Update(
    sf::Time delta_time) { /*board.Update(delta_time.asSeconds());*/
}

void Game::Render() {
	m_window.clear(sf::Color::Black);

	m_window.draw(board);
	m_window.display();
}
