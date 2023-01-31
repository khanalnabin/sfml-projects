#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

void sort(int *arr, int c) {
	int j = c;
	int v = arr[c];
	while (arr[j - 1] > v && j > 0) {
		arr[j] = arr[j - 1];
		j--;
	}
	arr[j] = v;
}

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(1320, 760), "Selection Sort");
	const int count = 200;
	const int width = window.getSize().x / count;
	window.setPosition({0, 0});
	window.setFramerateLimit(20);
	int arr[count];
	for (int i = 0; i < count; i++)
		arr[i] = i;
	std::random_shuffle(std::begin(arr), std::end(arr));
	sf::Color colors[count];
	for (int i = 0; i < count; i++) {
		colors[i] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	}
	bool start = false;
	int first = 1;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (!start)
					start = 1;
				else {
					std::random_shuffle(std::begin(arr), std::end(arr));
					first = 1;
				}
			}
		}
		window.clear(sf::Color::Black);
		for (int i = 0; i < count; i++) {
			sf::RectangleShape rect(sf::Vector2f(width, arr[i]));
			rect.setOrigin(0, rect.getSize().y);
			rect.setPosition(sf::Vector2f(i * width, window.getSize().y));
			rect.setFillColor(colors[i]);
			rect.setOutlineColor(sf::Color::Black);
			rect.setOutlineThickness(1);
			window.draw(rect);
		}

		if (start)
			if (first >= 0 && first < count) {
				sort(arr, first);
				first++;
			}
		window.display();
	}
}
