#pragma once
#include "Board.h"
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow m_window;
    void Update();
    void ProcessEvents();
    void Render();
    unsigned int m_game_width, m_game_height;
    unsigned int m_window_width, m_window_height;
    Board board;

public:
    Game();
    void run();
};
