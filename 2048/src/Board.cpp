#include "../include/Board.h"
Board::Board() {}
void Board::initialize(int window_width, int window_height) {
    m_window_width = window_width;
    m_window_height = window_height;
    m_block_size = m_window_width / 6.0f;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_elements[i][j] = 0;
        }
    }

    m_elements[0][0] = 2;
    m_elements[0][2] = 2;

    score = 0;
    keypressed_count = 0;
    dir = Direction::none;
    keypressed = false;
    once = false;
    add_block_once = false;
    is_game_over = false;
}

void Board::processEvents(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            dir = Direction::up;
            keypressed = true;
            break;
        case sf::Keyboard::Down:
            dir = Direction::down;
            keypressed = true;
            break;
        case sf::Keyboard::Left:
            dir = Direction::left;
            keypressed = true;
            break;
        case sf::Keyboard::Right:
            dir = Direction::right;
            keypressed = true;
            break;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
            keypressed = false;
            once = false;
            add_block_once = false;
            dir = Direction::none;
            break;
        }
    }
}

void Board::update() {
    if (is_game_over != 1) {
        if (keypressed) {
            if (dir == Direction::down) {
                if (!once) {
                    MoveDown();
                }
            } else if (dir == Direction::up) {
                if (!once)
                    MoveUp();
            } else if (dir == Direction::left) {
                if (!once)
                    MoveLeft();
            } else if (dir == Direction::right) {
                if (!once)
                    MoveRight();
            }
        }
    }
}
void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::sleep(sf::microseconds(10));
    states.transform *= getTransform();
    states.transform.translate(sf::Vector2f(100, 100));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m_elements[i][j]) {
                Block b(m_block_size, sf::Vector2f(i, j), m_elements[i][j]);
                target.draw(b, states);
            }
        }
    }
}
void Board::MoveLeft() {
    bool changed = false;
    int new_elements[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_elements[i][j] = m_elements[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int k = 0, j = 1; j < 4; j++) {
            if (m_elements[i][j] > 0) {
                if (m_elements[i][k] == m_elements[i][j]) {
                    new_elements[i][k++] *= 2;
                    score += m_elements[i][k - 1];
                    new_elements[i][j] = 0;
                    changed = true;
                } else if (m_elements[i][k] == 0) {
                    new_elements[i][k] = m_elements[i][j];
                    new_elements[i][j] = 0;
                    changed = true;
                } else {
                    new_elements[i][++k] = m_elements[i][j];
                    if (k != j) {
                        new_elements[i][j] = 0;
                        changed = true;
                    }
                }
            }
        }
    }
    if (changed) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_elements[i][j] = new_elements[i][j];
            }
        }
        AddBlock();
    }
    once = true;
}

void Board::MoveRight() {
    int new_elements[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_elements[i][j] = m_elements[i][j];
        }
    }
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        for (int k = 3, j = 2; j >= 0; j--) {
            if (m_elements[i][j] > 0) {
                if (m_elements[i][k] == m_elements[i][j]) {
                    new_elements[i][k--] *= 2;
                    score += m_elements[i][k + 1];
                    new_elements[i][j] = 0;
                    changed = true;
                } else if (m_elements[i][k] == 0) {
                    new_elements[i][k] = m_elements[i][j];
                    new_elements[i][j] = 0;
                    changed = true;
                } else {
                    new_elements[i][--k] = m_elements[i][j];
                    if (k != j) {
                        new_elements[i][j] = 0;
                        changed = true;
                    }
                }
            }
        }
    }
    if (changed) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_elements[i][j] = new_elements[i][j];
            }
        }
        AddBlock();
    }
    once = true;
}

void Board::MoveUp() {
    int new_elements[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_elements[i][j] = m_elements[i][j];
        }
    }
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        for (int k = 0, j = 1; j < 4; j++) {
            if (m_elements[j][i] > 0) {
                if (m_elements[j][i] == m_elements[k][i]) {
                    new_elements[k++][i] *= 2;
                    score += m_elements[k - 1][i];
                    new_elements[j][i] = 0;
                    changed = true;
                } else if (m_elements[k][i] == 0) {
                    new_elements[k][i] = m_elements[j][i];
                    new_elements[j][i] = 0;
                    changed = true;
                } else {
                    m_elements[++k][i] = m_elements[j][i];
                    if (k != j) {
                        new_elements[j][i] = 0;
                        changed = true;
                    }
                }
            }
        }
    }
    if (changed) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_elements[i][j] = new_elements[i][j];
            }
        }
        AddBlock();
    }
    once = true;
}

void Board::MoveDown() {
    int new_elements[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_elements[i][j] = m_elements[i][j];
        }
    }
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        for (int k = 3, j = 2; j >= 0; j--) {
            if (m_elements[j][i] > 0) {
                if (m_elements[j][i] == m_elements[k][i]) {
                    new_elements[k--][i] *= 2;
                    score += m_elements[k + 1][i];
                    new_elements[j][i] = 0;
                    changed = true;
                } else if (m_elements[k][i] == 0) {
                    new_elements[k][i] = m_elements[j][i];
                    new_elements[j][i] = 0;
                    changed = true;
                } else {
                    m_elements[--k][i] = m_elements[j][i];
                    if (k != j) {
                        new_elements[j][i] = 0;
                        changed = true;
                    }
                }
            }
        }
    }
    if (changed) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_elements[i][j] = new_elements[i][j];
            }
        }
        AddBlock();
    }
    once = true;
}

void Board::AddBlock() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int n = rand() % CountNullNum();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (0 == n) {
                m_elements[i][j] = 2;
                goto a;
            }
            if (0 == m_elements[i][j]) {
                n--;
            }
        }
    }
a:;
}
void Board::CheckOver() {
    int n1 = 0, n2 = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (m_elements[i][j] != m_elements[i][j + 1]) {
                n1++;
            }
            if (m_elements[i][j] >= 2048) {
                is_game_over = 2;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (m_elements[j][i] != m_elements[j + 1][i]) {
                n2++;
            }
        }
    }
    if (n1 == 12 && n2 == 12) {
        is_game_over = 1;
    }
}

int Board::CountNullNum() {
    int n = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (0 == m_elements[i][j])
                n++;
        }
    }

    return n;
}
