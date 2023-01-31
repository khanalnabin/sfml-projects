// Written by Nabin Khanal
// 2021 August 10

#include "Textbox.hpp"
#include <iostream>

Textbox::Textbox()
    : t_position(sf::Vector2f(0, 0)), t_size(sf::Vector2f(100, 30)),
      t_text_color(sf::Color::Black), t_background_color(sf::Color::White),
      t_character_size(30), t_has_focus(false), t_type(Type::Any), t_limit(50),
      t_border_width(0) {
    t_string = "";
    t_font.loadFromFile("assets/ubuntu.ttf");
    t_text.setFont(t_font);
    cursor_iteration_count = 0;
    t_cursor_position = 0;
    t_box.setPosition(t_position);
    t_box.setSize(t_size);
    t_box.setFillColor(t_background_color);
    t_box.setOutlineThickness(t_border_width);
    t_box.setOutlineColor(t_border_color);
    t_text.setFillColor(t_text_color);
    t_text.setCharacterSize(t_character_size);
    t_text.setPosition(t_position);
}

Textbox::Textbox(sf::Vector2f size, sf::Vector2f position, std::string path,
                 Type type)
    : t_size(size), t_position(position), t_text_color(sf::Color::Black),
      t_background_color(sf::Color::White), t_character_size(30),
      t_has_focus(false), t_type(Type::Any), t_border_width(0), t_limit(20) {
    t_string = "";
    t_font.loadFromFile(path);
    t_text.setFont(t_font);
    cursor_iteration_count = 0;
    t_cursor_position = 0;
    t_box.setPosition(t_position);
    t_box.setSize(t_size);
    t_box.setFillColor(t_background_color);
    t_box.setOutlineThickness(t_border_width);
    t_box.setOutlineColor(t_border_color);
    t_text.setFillColor(t_text_color);
    t_text.setCharacterSize(t_character_size);
    t_text.setPosition(t_position);
}

unsigned int Textbox::getCharacterSize() const { return t_character_size; }

sf::Vector2f Textbox::getPosition() const { return t_position; }

sf::Vector2f Textbox::getSize() const { return t_size; }

std::string Textbox::getString() const { return t_string; }

unsigned int Textbox::getStringLength() const { return t_string.length(); }
void Textbox::setType(Type type) { t_type = type; }

void Textbox::setFocus(bool focus) { t_has_focus = focus; }

void Textbox::setPosition(sf::Vector2f position) {
    t_position = position;
    t_box.setPosition(t_position);
    t_text.setPosition(t_position);
}

void Textbox::setSize(sf::Vector2f size) {
    t_size = size;
    t_box.setSize(t_size);
}

void Textbox::setPosition(float x, float y) {
    t_position = sf::Vector2f(x, y);
    t_box.setPosition(t_position);
    t_text.setPosition(t_position);
}

void Textbox::setSize(float width, float height) {
    t_size = sf::Vector2f(width, height);
    t_box.setSize(t_size);
}

void Textbox::setCharacterSize(unsigned int character_size) {
    t_character_size = character_size;
    t_text.setCharacterSize(t_character_size);
}
void Textbox::setBorderColor(sf::Color color) {
    t_border_color = color;
    t_box.setOutlineColor(color);
};
void Textbox::setFont(std::string path) {
    t_font.loadFromFile(path);
    t_text.setFont(t_font);
}

void Textbox::setLimit(unsigned int limit) { t_limit = limit; }

void Textbox::setBorderSize(unsigned int size) {
    t_border_width = size;
    t_box.setOutlineThickness(t_border_width);
}

void Textbox::setTextColor(sf::Color text_color) {
    t_text_color = text_color;
    t_text.setFillColor(t_text_color);
}

void Textbox::setBackgroundColor(sf::Color background_color) {
    t_background_color = background_color;
    t_box.setFillColor(t_background_color);
}
void Textbox::setString(std::string str){
  t_string = str;
  t_text.setString(t_string);
  t_cursor_position = t_string.length();
  t_text.setString(str);
}

void Textbox::listenForClick(sf::RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        if (mouse_position.x >= t_position.x &&
            mouse_position.x <= (t_position.x + t_size.x) &&
            mouse_position.y >= t_position.y &&
            mouse_position.y <= (t_position.y + t_size.y)) {
            t_has_focus = true;
        } else {
            t_has_focus = false;
        }
    }
}

void Textbox::listenForText(sf::Event &event) {
  if(event.key.code == sf::Keyboard::Escape && t_has_focus){
    t_has_focus = false;
  }
    if (t_has_focus && t_string.length() <= t_limit) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                if (t_cursor_position > 0) {
                    t_cursor_position--;
                }
            } else if (event.key.code == sf::Keyboard::Right) {
                if (t_cursor_position < t_string.length()) {
                    t_cursor_position++;
                }
            }
        }
        if (event.type == sf::Event::TextEntered) {
            unsigned int code = event.text.unicode;
            if ((code > 64 && code < 91) || (code > 96 && code < 123)) {
                if (t_type == Type::Letter || t_type == Type::AlphaNumeric ||
                    t_type == Type::Email || t_type == Type::Any) {
                    t_string.insert(t_cursor_position, 1, char(code));
                    t_cursor_position++;
                }
            } else if (code > 47 && code < 58) {
                if (t_type == Type::Number || t_type == Type::AlphaNumeric ||
                    t_type == Type::Any || t_type == Type::Email ||
                    t_type == Type::IP) {
                    t_string.insert(t_cursor_position, 1, char(code));
                    t_cursor_position++;
                }
            } else if (code == 190) {
                if (t_type == Type::IP || t_type == Type::Email ||
                    t_type == Type::Any) {
                    t_string.insert(t_cursor_position, 1, char(code));
                    t_cursor_position++;
                }
            } else if (code == 95 || code == 64) {
                if (t_type == Type::Email || t_type == Type::Any) {
                    t_string.insert(t_cursor_position, 1, char(code));
                    t_cursor_position++;
                }

            } else if (code == 46) {
                if (t_type == Type::Email || t_type == Type::IP ||
                    t_type == Type::Any) {
                    t_string.insert(t_cursor_position, 1, char(code));
                    t_cursor_position++;
                }
            } else if (code == 32) {
                if (t_type == Type::Letter || t_type == Type::AlphaNumeric ||
                    t_type == Type::Any) {
                    t_string.insert(t_cursor_position, 1, char(code));
                    t_cursor_position++;
                }
            } else if (code == 8) {
                if (t_string.length() > 0 && t_cursor_position > 0) {
                    t_string.erase(t_cursor_position - 1, sizeof(char));
                    t_cursor_position--;
                }

            } else if (code == 127) {
                if (t_string.length() - t_cursor_position) {
                    t_string.erase(t_cursor_position, sizeof(char));
                }
            } else if (code == 13) // nothing for enter or carriage return
                ;
            else {
                if (t_type == Type::Any) {
                    t_string.insert(t_cursor_position, 1, char(code));
                    t_cursor_position++;
                }
            }
        }
    }
}

void Textbox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    std::string tempstring{""};

    if (t_has_focus && ((cursor_iteration_count / 1000) % 2 == 0)) {
        tempstring += t_string.substr(0, t_cursor_position) + "|";
        if (t_cursor_position != t_string.length())
            tempstring += t_string.substr(t_cursor_position);
    } else {
        tempstring = t_string;
    }
    t_text.setString(tempstring);
    target.draw(t_box, states);
    target.draw(t_text, states);
    cursor_iteration_count++;
}
