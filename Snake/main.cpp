//
// Created by nabin on 5/17/21.
//
#include "Snake.h"
#include <SFML/Graphics.hpp>


int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 800), "opengl-Snake Game", sf::Style::Resize, settings);
    window.setFramerateLimit(20);
    Snake snake(16);
    int prevScore = snake.GetScore();
    int prevLives = snake.GetLives();
    World world(window.getSize());
    Textbox text;
    Textbox textbox;
    bool checkEntered = false;

    text.Setup(5, 14, 100, sf::Vector2f(window.getSize().x - 100, 0));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                && snake.GetDirection() != Direction::Down) {
                snake.SetDirection(Direction::Up);
            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                       && snake.GetDirection() != Direction::Up) {
                snake.SetDirection(Direction::Down);
            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                       && snake.GetDirection() != Direction::Right) {
                snake.SetDirection(Direction::Left);
            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                       && snake.GetDirection() != Direction::Left) {
                snake.SetDirection(Direction::Right);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                checkEntered = true;
            }
        }
        window.clear(sf::Color::Black);
        snake.Tick();
        world.Update(snake);
        if (snake.HasLost()) {
            textbox.Setup(5, 14, 100, sf::Vector2f(640 - 300, 240));
            textbox.Add("Game over", 4);
            textbox.Add("Score:" + std::to_string(snake.GetScore()), 4);
            textbox.Add("please press enter to play again", 4);
            textbox.Render(window);
            if (checkEntered) {
                snake.Reset();
                checkEntered = false;
            }
        }
        if (!checkEntered && !snake.HasLost()) {
            text.Add("Score: " + std::to_string(snake.GetScore()), 3);
            text.Add("Lives: " + std::to_string(snake.GetLives()), 3);

            world.Render(window);
            snake.Render(window);
            text.Render(window);
        }

        window.display();
    }

}

