#ifndef BAAGH_H
#define BAAGH_H

#include "Baagh.h"
#include "Baakhra.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <utility>
static int width = 680;
static int height = 680;

using vf = sf::Vector2f;
using vi = sf::Vector2i;
using vert = sf::Vertex;
using color = sf::Color;
class Board : public sf::Drawable, public sf::Transformable {
  public:
	Board();
	void Update(float seconds_elapsed);
	void ProcessEvents(sf::RenderWindow &m_window);

  private:
	sf::TcpSocket client;
	std::string winner;
	int block_size;
	vf vertex_array[5][5];
	bool is_game_over;
	std::vector<Baagh> baaghs;
	std::vector<Baakhra> baakhras;
	int baakhra_count;
	int elements_array[5][5]{0};
	void mapCoords(sf::Vector2i &mcoords);
	void
	draw(sf::RenderTarget &target,
	     sf::RenderStates states = sf::RenderStates::Default) const override;
	void DrawBoard(sf::RenderTarget &target, sf::RenderStates &states) const;
	void DrawText(sf::RenderTarget &target, sf::RenderStates &states) const;
	void GameOver();
	void CheckGameOver();
	bool CanEat();
	void Network();
	void Receive();
};
#endif
