#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

const int count = 213;
const int width = 9;

void sort(int *arr, int c) {
  int min = c;
  for (int i = c + 1; i < count; i++) {
    if (arr[i] < arr[min])
      min = i;
  }
  std::swap(arr[c], arr[min]);
}
int main() {
  srand(time(0));
  sf::RenderWindow window(sf::VideoMode(count * width, 1080), "Selection Sort");
  int arr[count];
  for (int i = 0; i < count; i++)
    arr[i] = i;
  std::random_shuffle(std::begin(arr), std::end(arr));
  sf::Color colors[count];
  for (int i = 0; i < count; i++) {
    colors[i] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
  }
  bool start = false;
  int first = 0;
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

    if (start)
      if (first >= 0 && first < count - 1) {
        sort(arr, first);
        first++;
      }
    window.display();
  }
}
