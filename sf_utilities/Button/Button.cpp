// Written by Nabin Khanal
// 2021 August 10

#include "Button.hpp"

Button::Button()
    : t_position(sf::Vector2f(0, 0)), t_size(sf::Vector2f(50, 30)),
      t_text_color(sf::Color::Black), t_background_color(sf::Color::White),
      t_character_size(30), t_border_width(5), t_string("Button"), once(false) {
    t_box = sf::RectangleShape(t_size);
    t_box.setPosition(t_position);
    t_box.setPosition(t_position);
    t_box.setFillColor(t_background_color);
    t_box.setOutlineThickness(t_border_width);
    t_box.setOutlineColor(t_border_color);
    t_font.loadFromFile("assets/ubuntu.ttf");
    t_text.setFont(t_font);
    t_text.setString(t_string);
    t_text.setFillColor(t_text_color);
    t_text.setCharacterSize(t_character_size);
    t_text.setPosition(t_position);
}

Button::Button(sf::Vector2f l_size, sf::Vector2f l_position, std::string l_text,
               std::string path)
    : t_position(l_position), t_size(l_size), t_text_color(sf::Color::Black),
      t_background_color(sf::Color::White), t_character_size(30),
      t_border_width(5), t_string(l_text), once(false) {
    t_box = sf::RectangleShape(t_size);
    t_box.setPosition(t_position);
    t_box.setPosition(t_position);
    t_box.setFillColor(t_background_color);
    t_box.setOutlineThickness(t_border_width);
    t_box.setOutlineColor(t_border_color);
    t_font.loadFromFile(path);
    t_text.setFont(t_font);
    t_text.setString(t_string);
    t_text.setFillColor(t_text_color);
    t_text.setCharacterSize(t_character_size);
    t_text.setPosition(t_position);
}

void Button::setPosition(sf::Vector2f position) {
    t_position = position;
    t_box.setPosition(t_position);
    t_text.setPosition(t_position);
}

void Button::setSize(sf::Vector2f size) {
    t_size = size;
    t_box.setSize(t_size);
}

void Button::setPosition(float x, float y) {
    t_position = sf::Vector2f(x, y);
    t_box.setPosition(t_position);
    t_text.setPosition(t_position);
}

void Button::setSize(float width, float height) {
    t_size = sf::Vector2f(width, height);
    t_box.setSize(t_size);
}

void Button::setCharacterSize(unsigned int character_size) {
    t_character_size = character_size;
    t_text.setCharacterSize(t_character_size);
}
void Button::setBorderColor(sf::Color color) {
    t_border_color = color;
    t_box.setOutlineColor(color);
};
void Button::setFont(std::string path) {
    t_font.loadFromFile(path);
    t_text.setFont(t_font);
}

void Button::setBorderSize(unsigned int size) {
    t_border_width = size;
    t_box.setOutlineThickness(t_border_width);
}

void Button::setTextColor(sf::Color text_color) {
    t_text_color = text_color;
    t_text.setFillColor(t_text_color);
}

void Button::setBackgroundColor(sf::Color background_color) {
    t_background_color = background_color;
    t_box.setFillColor(t_background_color);
}
void Button::setString(std::string str) {
    t_string = str;
    t_text.setString(t_string);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    t_text.setString(t_string);
    target.draw(t_box, states);
    target.draw(t_text, states);
}

void Button::listen(sf::RenderWindow &window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    if (mouse_position.x >= t_position.x &&
        mouse_position.x <= (t_position.x + t_size.x) &&
        mouse_position.y >= t_position.y &&
        mouse_position.y <= (t_position.y + t_size.y)) {
        hovered = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (!once) {
                clicked = true;
                once = true;
            } else {
                clicked = false;
            }
        } else {
            clicked = false;
            once = false;
        }
    } else {
        clicked = false;
        hovered = false;
    }
}
