#include "Application.hpp"
const int width = 1800;
const int height = 1000;
Application::Application()
    : window(sf::VideoMode(width, height), "opengl-Student Record Management System") {
      window.setFramerateLimit(30);
    }

void Application::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        graphics.processEvents(event);
    }
    graphics.processRealEvents(window);
}
void Application::update() { graphics.update(); }

void Application::render() {
    window.clear(sf::Color::Black);
    window.draw(graphics);
    window.display();
}
