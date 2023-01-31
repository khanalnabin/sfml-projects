#include "Board.h"
#include <string>

int count = 0;
Board::Board() {
	block_size = width / 4;
	baakhra_count = 0;
	for (int rows = 0; rows < 5; rows++) {
		for (int columns = 0; columns < 5; columns++) {
			vertex_array[rows][columns] =
			    vf(rows * block_size, columns * block_size);
		}
	}
	elements_array[0][0] = elements_array[4][4] = elements_array[0][4] =
	    elements_array[4][0] = 2;
	for (int rows = 0; rows < 5; rows++) {
		for (int columns = 0; columns < 5; columns++) {
			if (elements_array[rows][columns] == 2)
				baaghs.push_back(
				    Baagh(columns * block_size, rows * block_size));
		}
	}
	is_game_over = false;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.transform.translate(vf(90, 40));

	DrawBoard(target, states);
	sf::RenderStates new_state;
	new_state.transform *= getTransform();
	new_state.transform.translate(sf::Vector2f(800, 60));

	DrawText(target, new_state);

	for (auto &baagh : baaghs)
		target.draw(baagh, states);

	for (auto &baakhra : baakhras) {
		sf::Vector2f pos = baakhra.GetPosition();
		if (elements_array[(int)(pos.y / block_size)]
		                  [(int)(pos.x / block_size)] == 1)
			target.draw(baakhra, states);
	}
}
void Board::mapCoords(sf::Vector2i &mcoords) {
	mcoords.x -= 90;
	mcoords.y -= 40;
}
void Board::ProcessEvents(sf::RenderWindow &m_window) {
	if (!is_game_over) {
		if (count % 2) {
			Baagh::completed = false;
			for (auto &baagh : baaghs)
				if (!Baagh::completed)
					baagh.ProcessEvents(m_window, elements_array, block_size);
			if (Baagh::completed)
				count++;
		} else {
			Baakhra::completed = false;
			if (baakhras.size() < 20) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					sf::Vector2i mouse_position =
					    sf::Mouse::getPosition(m_window);
					mapCoords(mouse_position);
					for (int rows = 0; rows < 5; rows++) {
						for (int columns = 0; columns < 5; columns++) {
							if (abs(mouse_position.x - columns * block_size) <=
							        50 &&
							    abs(mouse_position.y - rows * block_size) <=
							        50) {
								if (elements_array[rows][columns] == 0) {
									baakhras.push_back(
									    Baakhra(columns * block_size,
									            rows * block_size));
									elements_array[rows][columns] = 1;
									count++;
									Baakhra::completed = true;
								}
							}
						}
					}
				}

			} else {
				Baakhra::completed = false;
				for (auto &baakhra : baakhras)
					if (!Baakhra::completed)
						baakhra.ProcessEvents(m_window, elements_array,
						                      block_size);
				if (Baakhra::completed)
					count++;
			}
		}

		sf::Packet packet;
	}
	GameOver();
}
void Board::GameOver() {
	int bakhra_cnt = 0, trapped_baaghs = 0;
	bool can_eat = false;
	for (int rows = 0; rows < 5; rows++) {
		for (int columns = 0; columns < 5; columns++) {
			if (elements_array[rows][columns] == 1) {
				bakhra_cnt++;
			} else if (elements_array[rows][columns] == 2) {
				if ((rows + columns) % 2 == 0) {
					int cnt = 0, b_cnt = 0;
					for (int i = -1; i < 2; i++) {
						for (int j = -1; j < 2; j++) {
							if ((rows + i) >= 0 && (columns + j) >= 0 &&
							    (rows + i) <= 4 && (columns + j) <= 4) {
								if ((abs(i) + abs(j)) > 0) {
									cnt++;
									if (elements_array[rows + i][columns + j] >=
									    1) {
										b_cnt++;
									}
									if ((rows + 2 * i) >= 0 &&
									    (columns + 2 * j) >= 0 &&
									    (rows + 2 * i) <= 4 &&
									    (columns + 2 * j) <= 4) {
										if (elements_array[rows + 2 * i]
										                  [columns + 2 * j] ==
										    0)
											can_eat = true;
									}
								}
							}
						}
					}
					if (b_cnt == cnt && b_cnt != 0) {
						trapped_baaghs++;
					}
				} else {
					int cnt = 0, b_cnt = 0;
					for (int i = -1; i < 2; i++) {
						for (int j = -1; j < 2; j++) {
							if (rows + i >= 0 && columns + j >= 0 &&
							    rows + i <= 4 && columns + i <= 4) {
								if (abs(i) + abs(j) == 1) {
									cnt++;
									if (elements_array[rows + i][columns + j] >=
									    1)
										b_cnt++;
									if ((rows + 2 * i) >= 0 &&
									    (columns + 2 * j) >= 0 &&
									    (rows + 2 * i) <= 4 &&
									    (columns + 2 * j) <= 4) {
										if (elements_array[rows + 2 * i]
										                  [columns + 2 * j] ==
										    0)
											can_eat = true;
									}
								}
							}
						}
					}
					if (b_cnt == cnt && b_cnt != 0) {
						trapped_baaghs++;
					}
				}
			}
		}
	}
	baakhra_count = bakhra_cnt;
	if (trapped_baaghs == 4 && !can_eat) {
		is_game_over = true;
		winner = "baakhra";
	} else if ((baakhras.size() - bakhra_cnt) > 4) {
		is_game_over = true;
		winner = "baagh";
	}
}

void Board::DrawText(sf::RenderTarget &target, sf::RenderStates &states) const {
	sf::Text turn;
	sf::Font font;
	font.loadFromFile("assets/fonts/arial.ttf");
	std::string str = count % 2 == 0 ? "Baakhra" : "Baagh";
	turn.setFont(font);
	turn.setString(str + " ko palo.");
	turn.setPosition(100, 0);
	turn.setCharacterSize(40);
	turn.setFillColor(sf::Color::White);
	target.draw(turn, states);

	sf::Text remaining_baakhras;
	remaining_baakhras.setFont(font);
	remaining_baakhras.setString(
	    std::to_string(baakhra_count) + " Baacheka.\n" +
	    std::to_string(baakhras.size()) + " Prayog vayeka.\n" +
	    std::to_string(baakhras.size() - baakhra_count) + " Mareka.\n");
	remaining_baakhras.setPosition(100, 40);
	remaining_baakhras.setFillColor(sf::Color::White);
	target.draw(remaining_baakhras, states);

	if (is_game_over) {
		sf::Text game_over;
		game_over.setFont(font);
		game_over.setCharacterSize(60);
		std::string str;
		if ((baakhras.size() - baakhra_count) > 4)
			str = "La Badhai chha \nBaagh.";
		else {
			str = "La Badhai chha \nBaakhra";
		}
		game_over.setString(str);
		game_over.setFillColor(sf::Color::White);
		game_over.setPosition(100, 200);
		target.draw(game_over, states);
	}
}

void Board::DrawBoard(sf::RenderTarget &target,
                      sf::RenderStates &states) const {
	for (int i = 0; i < 5; i++) {
		vert line_ver[]{vert(vertex_array[0][i], color::White),
		                vert(vertex_array[4][i], color::White)};
		vert line_hor[]{vert(vertex_array[i][0], color::White),
		                vert(vertex_array[i][4], color::White)};
		target.draw(line_ver, 2, sf::Lines, states);
		target.draw(line_hor, 2, sf::Lines, states);
	}
	vert line_diag[]{vert(vertex_array[0][0], color::White),
	                 vert(vertex_array[4][4], color::White)};
	target.draw(line_diag, 2, sf::Lines, states);

	vert line_rev_diag[]{vert(vertex_array[0][4], sf::Color::White),
	                     vert(vertex_array[4][0], color::White)};
	target.draw(line_rev_diag, 2, sf::Lines, states);

	vert ang_one[]{vert(vertex_array[0][2], sf::Color::White),
	               vert(vertex_array[2][0], color::White)};
	target.draw(ang_one, 2, sf::Lines, states);

	vert ang_two[]{vert(vertex_array[4][2], sf::Color::White),
	               vert(vertex_array[2][0], color::White)};
	target.draw(ang_two, 2, sf::Lines, states);

	vert ang_three[]{vert(vertex_array[4][2], sf::Color::White),
	                 vert(vertex_array[2][4], color::White)};
	target.draw(ang_three, 2, sf::Lines, states);

	vert ang_four[]{vert(vertex_array[2][4], sf::Color::White),
	                vert(vertex_array[0][2], color::White)};
	target.draw(ang_four, 2, sf::Lines, states);
}
