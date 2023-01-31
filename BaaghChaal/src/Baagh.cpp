#include "Baagh.h"
#include <SFML/System/Vector2.hpp>
Baagh::Baagh() : m_position(sf::Vector2f(0, 0)) {}
Baagh::Baagh(float x, float y) { m_position = sf::Vector2f(x, y); }
bool Baagh::completed = false;
Baagh::Baagh(sf::Vector2f position) { m_position = position; };

void Baagh::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	sf::Texture baagh_texture;

	baagh_texture.loadFromFile("assets/images/tiger_final.png");
	sf::Sprite baagh_sprite;
	baagh_sprite.setTexture(baagh_texture);
	baagh_sprite.setPosition(m_position);
	baagh_sprite.setOrigin(baagh_texture.getSize().x / 2.0f,
	                       baagh_texture.getSize().y / 2.0f);
	target.draw(baagh_sprite, states);
}

sf::Vector2f Baagh::GetPosition() { return m_position; }
void Baagh::mapCoords(sf::Vector2i &mcoords) {
	mcoords.x -= 90;
	mcoords.y -= 40;
}
void Baagh::ProcessEvents(sf::RenderWindow &window, int elements_array[5][5],
                          int block_size) {
	if (!Baagh::completed) {
		bool changed = false;
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		mapCoords(mouse_position);
		sf::Vector2i temp_position;
		int i = 0;
		if (mouse_position.x >= m_position.x - 50 &&
		    mouse_position.x <= m_position.x + 50 &&
		    mouse_position.y >= m_position.y - 50 &&
		    mouse_position.y <= m_position.y + 50) {
			while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
				mapCoords(mouse_position);
				temp_position.x = mouse_position.x;
				temp_position.y = mouse_position.y;
				changed = true;
			}
		}
		sf::Vector2i index(m_position.x / block_size,
		                   m_position.y / block_size);
		if (changed) {

			for (int rows = 0; rows < 5; rows++) {
				for (int columns = 0; columns < 5; columns++) {
					if (temp_position.x >= columns * block_size - 50 &&
					    temp_position.x <= columns * block_size + 50 &&
					    temp_position.y >= rows * block_size - 50 &&
					    temp_position.y <= rows * block_size + 50) {
						if (abs(columns - index.x) <= 1 &&
						    abs(rows - index.y) <= 1) {

							if ((index.x + index.y) % 2 == 0) {
								if (elements_array[rows][columns] == 0) {
									elements_array[rows][columns] = 2;
									elements_array[index.y][index.x] = 0;
									m_position =
									    sf::Vector2f(columns * block_size,
									                 rows * block_size);
									Baagh::completed = true;
								} else if (elements_array[rows][columns] == 1) {
									int x_diff = index.x - columns;
									int y_diff = index.y - rows;
									int new_x = columns - x_diff;
									int new_y = rows - y_diff;
									if (new_x >= 0 && new_x <= 4 &&
									    new_y <= 4 && new_y >= 0 &&
									    elements_array[new_y][new_x] == 0) {
										elements_array[rows][columns] = 0;
										elements_array[index.y][index.x] = 0;
										elements_array[new_y][new_x] = 2;
										m_position =
										    sf::Vector2f(new_x * block_size,
										                 new_y * block_size);
										Baagh::completed = true;
									}
								}
							} else {
								if (abs(columns - index.x) == 0 ||
								    abs(rows - index.y) == 0) {
									if (elements_array[rows][columns] == 0) {
										elements_array[rows][columns] = 2;
										elements_array[index.y][index.x] = 0;
										m_position =
										    sf::Vector2f(columns * block_size,
										                 rows * block_size);
										Baagh::completed = true;
									} else if (elements_array[rows][columns] ==
									           1) {
										int x_diff = index.x - columns;
										int y_diff = index.y - rows;
										int new_x = columns - x_diff;
										int new_y = rows - y_diff;
										if (new_x >= 0 && new_x <= 4 &&
										    new_y <= 4 && new_y >= 0 &&
										    elements_array[new_y][new_x] == 0) {
											elements_array[new_y][new_x] = 2;
											elements_array[rows][columns] = 0;
											elements_array[index.y][index.x] =
											    0;
											m_position = sf::Vector2f(
											    new_x * block_size,
											    new_y * block_size);
											Baagh::completed = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
