// Written by Nabin Khanal
// 2021 August 10

#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Transformable, public sf::Drawable {
private:
    bool once;
    sf::RectangleShape t_box;
    mutable sf::Text t_text;
    std::string t_string;
    sf::Vector2f t_position;
    sf::Color t_text_color;
    sf::Color t_background_color;
    sf::Color t_border_color;
    unsigned int t_character_size;
    sf::Vector2f t_size;
    unsigned int t_border_width;
    sf::Font t_font;

    virtual void
    draw(sf::RenderTarget &target,
         sf::RenderStates states = sf::RenderStates::Default) const override;

public:
    bool clicked;
    bool hovered;
    Button();
    Button(sf::Vector2f l_size, sf::Vector2f l_position, std::string l_text,
           std::string path);
    Button(Button &) = delete;
    Button operator=(Button &) = delete;
    Button(Button &&) = delete;
    Button operator=(Button &&) = delete;
    void listen(sf::RenderWindow &window);
    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);
    void setSize(sf::Vector2f size);
    void setSize(float width, float height);
    void setCharacterSize(unsigned int character_size);
    void setTextColor(sf::Color text_color);
    void setBorderColor(sf::Color);
    void setBackgroundColor(sf::Color background_color);
    void setBorderSize(unsigned int size);
    void setFont(std::string path);
    void setString(std::string str);
};
