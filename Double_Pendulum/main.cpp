#include "Pendulum.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

const int width = 600;
const int height = 600;
int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "opengl-Double Pendulum");
    window.setFramerateLimit(60);
    bool start = false;
    Pendulum pen(91, 45);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
                event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash))
            start = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            start = false;
        if (start) {
            pen.update();
        }
        // pen.moveSliders(window);
        window.clear(sf::Color::Black);
        window.draw(pen);
        window.display();
    }
}
