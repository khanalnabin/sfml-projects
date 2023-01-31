#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
const int count = 213;

void sort(int *arr, int i) {
	if (arr[i] > arr[i + 1]) {
		std::swap(arr[i], arr[i + 1]);
	}
}
void bubbleSort(int *arr) {
	static int first = count - 1, second = 0;

	if (first >= 0) {
		if (second < first) {
			sort(arr, second);
			second++;
		} else {
			second = 0;
			first--;
		}
	}
}

int main() {
	int width = 9;
	sf::RenderWindow window(sf::VideoMode(count * width, 1080), "Bubble Sort",
	                        sf::Style::Default);
	int arr[count];
	for (int i = 0; i < count; i++)
		arr[i] = i;
	std::random_shuffle(std::begin(arr), std::end(arr));
	bool start = false;
	sf::Time time = sf::seconds(5);
	sf::Color colors[count];
	for (int i = 0; i < count; i++) {
		colors[i] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				start = 1;
			}
		}
		window.clear(sf::Color::Black);
		for (int i = 0; i < count; i++) {
			sf::RectangleShape rect(sf::Vector2f(width, arr[i] * 4));
			rect.setOrigin(0, rect.getSize().y);
			rect.setPosition(sf::Vector2f(i * width, window.getSize().y));
			rect.setFillColor(colors[i]);
			rect.setOutlineColor(sf::Color::Black);
			rect.setOutlineThickness(1);
			window.draw(rect);
		}

		if (start) {
			bubbleSort(arr);
		}
		window.display();
	}
}
