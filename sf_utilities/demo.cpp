#include "Button/Button.hpp"
#include "Textbox/Textbox.hpp"
#include <SFML/Graphics.hpp>
int main() {
    int count = 0;
    sf::RenderWindow window({500, 500}, "Textbox Check");
    Textbox tb(sf::Vector2f(200, 50), sf::Vector2f(200, 30),
               "assets/ubuntu.ttf");
    Button b(sf::Vector2f(100, 100), sf::Vector2f(400, 100), "Button",
             "assets/ubuntu.ttf");
    b.setString("New button");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            tb.listenForText(event);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        tb.listenForClick(window);
        b.listen(window);
        window.clear(sf::Color::Black);
        if (b.clicked) {
            std::cout << count++ << std::endl;
        }
        if (b.hovered) {
            std::cout << "Hovered" << std::endl;
        }
        window.draw(tb);
        window.draw(b);
        window.display();
    }
    return 0;
}
